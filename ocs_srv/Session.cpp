#include "Session.h"

Session::Session(uv_tcp_t &uvTcp, MessageMap &msgMap)
	:m_uvClient(uvTcp)
	,m_msgMap(msgMap)
{
	m_uvBuf = nullptr;
	m_uvClient.data = this;
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

void Session::append(char *buf, int size)
{
	sendMessage(buf, size);
	//m_recvBuf.insert(m_recvBuf.end(), buf, buf+size);
	//m_msgMap.dispatchMsg(&m_recvBuf[0], m_recvBuf.size());
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