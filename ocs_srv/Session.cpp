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
	m_recvBuf.insert(m_recvBuf.end(), buf, buf+size);
	while (1)
	{
		int offset = check(m_recvBuf);
		if (offset == 0)
			break;
		m_msgMap.dispatchMsg(&m_recvBuf[0], m_recvBuf.size());
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

int Session::check(const std::vector<char> &buf)
{
	return buf.size();
}
