#ifndef _CONNECTSERVER_INCLUDE
#define _CONNECTSERVER_INCLUDE

#include <uv.h>
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

class OCSSERVER_API ConnectServer : public SocketHand
{
public:
	ConnectServer(Scheduler &scheduler);
	~ConnectServer(void);
	MessageMap &msgMap();

	void start(const std::string &ip, unsigned int port);
	void start(const IPAddress &address);

	//消息到来
	virtual void msgcomming(Session *session);

private:
	MessageMap m_msgMap;
};

#endif
