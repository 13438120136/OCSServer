#ifndef _CONNECTSERVER_INCLUDE
#define _CONNECTSERVER_INCLUDE

#include <uv.h>
#include <string>
#include "Scheduler.h"
#include "MessageMap.h"
#include "Session.h"

class ConnectServer
{
public:
	ConnectServer(Scheduler &scheduler);
	~ConnectServer(void);
	MessageMap &msgMap();
	Scheduler &scheduler();
	uv_tcp_t &uvTcp();
	void start(const std::string &ip, int port);

private:
	Scheduler &m_scheduler;
	uv_tcp_t m_uvTcp;
	MessageMap m_msgMap;
	Session m_session;
};

#endif
