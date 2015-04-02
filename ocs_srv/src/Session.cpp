#include "Session.h"

Session::Session(uv_tcp_t &client)
	:m_uvClient(client)
{
	m_uvBuf = nullptr;
	m_uvClient.data = this;
	initAddress();
}

Session::~Session()
{
	if (m_uvBuf)
	{
		delete[] m_uvBuf->base;
		m_uvBuf->base = nullptr;
		m_uvBuf->len = 0;
	}
}

void Session::initAddress()
{
	struct sockaddr_in addr;
	int nLen = sizeof(addr);
	uv_tcp_getpeername((uv_tcp_t *)&m_uvClient, (struct sockaddr *)&addr, &nLen);
	char *ip = inet_ntoa(addr.sin_addr);
	int port = addr.sin_port;
	m_address.setIpAndPort(ip, port);
}

IPAddress &Session::getAddress()
{
	return m_address;
}

void Session::append(char *buf, int size)
{
	m_recvBuf.insert(m_recvBuf.end(), buf, buf+size);
}

void Session::render(MessageMap &msgMap)
{
	while (1)
	{
		int offset = msgMap.check(m_recvBuf);
		if (offset <= 0)
			break;

		msgMap.dispatchMsg(m_recvBuf, *this);
		m_recvBuf.erase(m_recvBuf.begin(), m_recvBuf.begin() + offset);
	}
}

void Session::setBuffer(uv_buf_t *buf, int size)
{
	if (buf->base == nullptr)
	{
		buf->base = new char[size];
		buf->len = size;
	}
	m_uvBuf = buf;
}

static void write_cb(uv_write_t* req, int status)
{
	if (status)
	{
		Session *session = (Session *)req->data;
		delete session;
	}
	delete req;
}

void Session::sendMessage(char *buf, int size)
{
	uv_write_t *req = new uv_write_t;
	req->data = this;

	uv_buf_t uvBuf = uv_buf_init(buf, size); 
	uv_write(req, (uv_stream_t *)&m_uvClient, &uvBuf, 1, write_cb);
}

void Session::destory()
{
	uv_read_stop((uv_stream_t *)&m_uvClient);
	uv_close((uv_handle_t*)&m_uvClient, nullptr);
}
