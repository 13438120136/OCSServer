#ifndef _CONNECTSERVER_INCLUDE
#define _CONNECTSERVER_INCLUDE

#include <uv.h>
#include <string>
#include "Scheduler.h"
#include "MessageMap.h"
#include "SocketHand.h"

class ConnectServer : public SocketHand
{
public:
	ConnectServer(Scheduler &scheduler);
	~ConnectServer(void);
	MessageMap &msgMap();

	void start(const std::string &ip, int port);

	//消息到来
	virtual void msgcomming(Session *session);

private:
	MessageMap m_msgMap;
};

#endif
