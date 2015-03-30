#include <string.h>  
#include "AcceptServer.h"
#include "Session.h"
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

static void on_new_connection(uv_stream_t *server, int status)
{
	int ret = 0;

	AcceptServer *curr = (AcceptServer *)server->data;
	uv_loop_t *loop = (curr->scheduler()).instance();

	uv_tcp_t *client = new uv_tcp_t;
	uv_stream_t *clientStream = (uv_stream_t *)client;

	ret = uv_tcp_init(loop, client);
	ret = uv_accept(server, clientStream);
    if (ret)
	{
        LOG(ERROR) << "AcceptServer Accept error: " << uv_strerror(ret);
        exit(-1);
    }

	ret = uv_read_start(clientStream, echo_alloc, read_cb);
    if (ret)
	{
        LOG(ERROR) << "AcceptServer Start Read error: " << uv_strerror(ret);
        exit(-1);
    }

	Session *session = new Session(*client, curr->msgMap());
}

AcceptServer::AcceptServer(Scheduler &scheduler)
	:m_scheduler(scheduler)
{
	m_uvTcp.data = this;
}

AcceptServer::~AcceptServer(void)
{
}

Scheduler &AcceptServer::scheduler()
{
	return m_scheduler;
}

uv_tcp_t &AcceptServer::uvTcp()
{
	return m_uvTcp;
}

MessageMap &AcceptServer::msgMap()
{
	return m_msgMap;
}

void AcceptServer::start(const std::string &ip, int port)
{
	struct sockaddr_in addr;
	uv_ip4_addr(ip.c_str(), port, &addr);

	int ret = uv_tcp_init(m_scheduler.instance(), &m_uvTcp);
	if (ret)
	{
		LOG(ERROR) << "AcceptServer Init error :" << uv_strerror(ret);
		exit(-1);
	}

	ret = uv_tcp_bind(&m_uvTcp, (struct sockaddr *)&addr, 0);
	if (ret)
	{
		LOG(ERROR) << "AcceptServer Bind error " << uv_strerror(ret);
		exit(-1);
	}

	ret = uv_listen((uv_stream_t *)&m_uvTcp, 128, on_new_connection);
    if (ret)
	{
        LOG(ERROR) << "AcceptServer Listen error " << uv_strerror(ret);
        exit(-1);
    }

	LOG(INFO) << "AcceptServer Start Success";
}
