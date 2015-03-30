#include "ConnectServer.h"
#include "Logger.h"

static void echo_alloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
	Session *session = (Session *)handle->data;
	if (buf->base == nullptr)
		session->setBuffer(buf, suggested_size);
}

static void close_cb(uv_handle_t* handle)
{
	return ;
}

static void read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
	if (nread > 0)
	{
		Session *session = (Session *)stream->data;
		session->append(buf->base, nread);
	}
	else if (nread < 0)
	{
		Session *session = (Session *)stream->data;
		delete session;
		uv_read_stop(stream);
		uv_close((uv_handle_t*)stream, close_cb);
	}
	else if (nread == 0)
	{
		uv_read_start(stream, echo_alloc, read_cb);
	}
}

static void connection_cb(uv_connect_t* req, int status)
{
	ConnectServer *curr = (ConnectServer *)req->data;
	delete req;

	uv_tcp_t &uvTcp = curr->uvTcp();

	int ret = uv_read_start((uv_stream_t *)&uvTcp, echo_alloc, read_cb);
    if (ret)
	{
        LOG(ERROR) << "ConnectServer Start Read error:" <<  uv_strerror(ret);
        exit(-1);
    }

	LOG(INFO) << "ConnectServer Start Success";
}

ConnectServer::ConnectServer(Scheduler &scheduler)
	:m_scheduler(scheduler)
	,m_session(m_uvTcp, m_msgMap)
{
	m_uvTcp.data = this;
}

ConnectServer::~ConnectServer(void)
{
}

MessageMap &ConnectServer::msgMap()
{
	return m_msgMap;
}

Scheduler &ConnectServer::scheduler()
{
	return m_scheduler;
}

uv_tcp_t &ConnectServer::uvTcp()
{
	return m_uvTcp;
}

void ConnectServer::start(const std::string &ip, int port)
{
	struct sockaddr_in addr;
	uv_ip4_addr(ip.c_str(), port, &addr);

	int ret = 0;

	ret = uv_tcp_init(m_scheduler.instance(), &m_uvTcp);
	if (ret)
	{
		LOG(ERROR) << "ConnectServer Init error :" << uv_strerror(ret);
		exit(-1);
	}

	uv_connect_t *connect = new uv_connect_t;
	connect->data = this;

	ret = uv_tcp_connect(connect, &m_uvTcp, (struct sockaddr *)&addr, connection_cb);
	if (ret)
	{
		LOG(ERROR) << "ConnectServer Connect error " << uv_strerror(ret);
		exit(-1);
	}
}
