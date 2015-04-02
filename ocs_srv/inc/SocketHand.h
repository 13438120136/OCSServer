#ifndef _SOCKETHAND_INCLUDE
#define _SOCKETHAND_INCLUDE

#include <uv.h>
#include "Scheduler.h"

#ifdef OCSSERVER_API_EXPORTS
#define OCSSERVER_API __declspec(dllexport)
#else
#define OCSSERVER_API __declspec(dllimport)
#endif

struct ConnHander
{
	uv_tcp_t tcp;
	void *session;
	void *obj;
};

struct ServerInstance
{
	uv_connect_t curr;
	ConnHander connect;
};

class Session;
class OCSSERVER_API SocketHand
{
public:
	SocketHand(Scheduler &scheduler);
	~SocketHand();

	int tcp_init();
	int tcp_init(uv_tcp_t *tcp);
	int tcp_bind(struct sockaddr *addr);
	int tcp_listen();
	int tcp_connect(struct sockaddr *addr);

	//连接到来
	virtual void connect(Session *session);
	//消息到来
	virtual void msgcomming(Session *session);
	//连接断开
	virtual void disconnect(Session *session);

private:
	Scheduler &m_scheduler;
	ServerInstance m_intance;
};

#endif
