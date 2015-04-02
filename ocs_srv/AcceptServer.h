#ifndef _ACCEPTSERVER_INCLUDE
#define _ACCEPTSERVER_INCLUDE

#include <uv.h>
#include <string>
#include "Scheduler.h"
#include "MessageMap.h"
#include "SocketHand.h"
#include "IPAddress.h"

class AcceptServer : public SocketHand
{
public:
	AcceptServer(Scheduler &scheduler);
	~AcceptServer(void);

	MessageMap &msgMap();
	void start(const std::string &ip, unsigned int port);
	void start(const IPAddress &address);

	//消息到来
	virtual void msgcomming(Session *session);
	virtual void connect(Session *session);
	virtual void disconnect(Session *session);

private:
	MessageMap m_msgMap;
};

#endif
