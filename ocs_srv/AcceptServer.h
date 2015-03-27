#ifndef _ACCEPTSERVER_INCLUDE
#define _ACCEPTSERVER_INCLUDE

#include <uv.h>
#include <string>
#include "Scheduler.h"
#include "MessageMap.h"

class AcceptServer
{
public:
	AcceptServer(Scheduler &scheduler);
	~AcceptServer(void);

	Scheduler &scheduler();
	uv_tcp_t &uvTcp();
	MessageMap &msgMap();
	void start(std::string ip, int port);
	void postAccept();

private:
	uv_tcp_t m_uvTcp;
	MessageMap m_msgMap;
	Scheduler &m_scheduler;
};

#endif
