#ifndef _ACCEPTSERVER_INCLUDE
#define _ACCEPTSERVER_INCLUDE

#include <uv.h>
#include <string>
#include "Scheduler.h"
#include "MessageMap.h"
#include "SocketHand.h"

class AcceptServer : public SocketHand
{
public:
	AcceptServer(Scheduler &scheduler);
	~AcceptServer(void);

	MessageMap &msgMap();
	void start(const std::string &ip, int port);

	//消息到来
	virtual void msgcomming(Session *session);
private:
	MessageMap m_msgMap;
};

#endif
