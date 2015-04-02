#ifndef _SOCKETHAND_INCLUDE
#define _SOCKETHAND_INCLUDE

#include <uv.h>
#include "Scheduler.h"

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
class SocketHand
{
public:
	SocketHand(Scheduler &scheduler);
	~SocketHand();

	int tcp_init();
	int tcp_init(uv_tcp_t *tcp);
	int tcp_bind(struct sockaddr *addr);
	int tcp_listen();
	int tcp_connect(struct sockaddr *addr);

	//���ӵ���
	virtual void connect(Session *session);
	//��Ϣ����
	virtual void msgcomming(Session *session);
	//���ӶϿ�
	virtual void disconnect(Session *session);

private:
	Scheduler &m_scheduler;
	ServerInstance m_intance;
};

#endif
