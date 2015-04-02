#include "SocketHand.h"
#include "Session.h"
#include "Logger.h"

static void echo_alloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
	ConnHander *conn = (ConnHander *)handle;
	Session *session = (Session *)conn->session;
	if (buf->base == nullptr)
		session->setBuffer(buf, suggested_size);
}

static void read_cb(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
	ConnHander *conn = (ConnHander *)stream;
	Session *session = (Session *)conn->session;
	SocketHand *obj = (SocketHand *)conn->obj;

	if (nread > 0)
	{	
		session->append(buf->base, nread);
		obj->msgcomming(session);
	}
	else if (nread < 0)
	{
		obj->disconnect(session);
	}
	else if (nread == 0)
	{
		uv_read_start(stream, echo_alloc, read_cb);
	}
}

static void on_new_connection(uv_stream_t *server, int status)
{
	ConnHander *head = (ConnHander *)server;
	ConnHander *client = new ConnHander;

	SocketHand *curr = (SocketHand *)head->obj;
	curr->tcp_init((uv_tcp_t *)client);

	int ret = uv_accept(server, (uv_stream_t *)client);
    if (ret)
	{
        LOG(ERROR) << "AcceptServer Accept error: " << uv_strerror(ret);
        exit(-1);
    }

	ret = uv_read_start((uv_stream_t *)client, echo_alloc, read_cb);
    if (ret)
	{
        LOG(ERROR) << "AcceptServer Start Read error: " << uv_strerror(ret);
        exit(-1);
    }

	client->session = new Session(client->tcp);
	client->obj = head->obj;

	curr->connect((Session *)client->session);
}

static void connection_cb(uv_connect_t* req, int status)
{
	ServerInstance *server = (ServerInstance *)req;
	uv_tcp_t &client = server->connect.tcp;
	
	int ret = uv_read_start((uv_stream_t *)&client, echo_alloc, read_cb);
    if (ret)
	{
        LOG(ERROR) << "ConnectServer Start Read error:" <<  uv_strerror(ret);
        exit(-1);
    }
	
	server->connect.session = new Session(client);
	SocketHand *obj = (SocketHand *)server->connect.obj;
	Session *session = (Session *)server->connect.session;
	obj->connect(session);

	LOG(INFO) << "ConnectServer Start Success";
}

SocketHand::SocketHand(Scheduler &scheduler)
	:m_scheduler(scheduler)
{
	m_intance.connect.obj = this;
}

SocketHand::~SocketHand(void)
{
}

int SocketHand::tcp_init()
{
	return uv_tcp_init(m_scheduler.instance(), (uv_tcp_t *)&m_intance.connect);
}

int SocketHand::tcp_init(uv_tcp_t *tcp)
{
	return uv_tcp_init(m_scheduler.instance(), tcp);
}

int SocketHand::tcp_bind(struct sockaddr *addr)
{
	return uv_tcp_bind((uv_tcp_t *)&m_intance.connect, addr, 0);
}

int SocketHand::tcp_listen()
{
	return uv_listen((uv_stream_t *)&m_intance.connect, 128, on_new_connection);
}

int SocketHand::tcp_connect(struct sockaddr *addr)
{
	return uv_tcp_connect((uv_connect_t *)&m_intance, (uv_tcp_t *)&m_intance.connect, addr, connection_cb);
}

void SocketHand::connect(Session *session)
{
}

void SocketHand::disconnect(Session *session)
{
	session->destory();
	delete session;
}

void SocketHand::msgcomming(Session *session)
{
}
