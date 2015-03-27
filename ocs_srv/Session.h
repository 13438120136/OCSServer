#ifndef _SESSION_INCLUDE
#define _SESSION_INCLUDE

#include <uv.h>
#include <vector>
#include "MessageMap.h"

class Session
{
public:
	Session(uv_tcp_t &uvTcp, MessageMap &msgMap);
	~Session();

	void append(char *buf, int size);
	void setBuffer(uv_buf_t *buf, int size);
	void sendMessage(char *buf, int size);

private:
	std::vector<char> m_recvBuf;
	uv_tcp_t &m_uvClient;
	MessageMap &m_msgMap;
	uv_buf_t *m_uvBuf;
};

#endif
