#ifndef _ACCEPTSERVER_INCLUDE
#define _ACCEPTSERVER_INCLUDE

#include <string>
#include "Scheduler.h"
#include "MessageMap.h"
#include "SocketHand.h"
#include "IPAddress.h"

#ifdef OCSSERVER_API_EXPORTS
#define OCSSERVER_API __declspec(dllexport)
#else
#define OCSSERVER_API __declspec(dllimport)
#endif

class OCSSERVER_API AcceptServer : public SocketHand
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
