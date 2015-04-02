#ifndef _SESSION_INCLUDE
#define _SESSION_INCLUDE

#include <uv.h>
#include <vector>
#include "MessageMap.h"

class Session
{
public:
	Session(uv_tcp_t &client);
	~Session();

	void append(char *buf, int size);
	void setBuffer(uv_buf_t *buf, int size);
	void sendMessage(char *buf, int size);
	void render(MessageMap &msgMap);
	void destory();

private:
	std::vector<char> m_recvBuf;
	uv_tcp_t &m_uvClient;
	uv_buf_t *m_uvBuf;
};

#endif
