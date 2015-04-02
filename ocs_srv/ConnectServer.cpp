#include "ConnectServer.h"
#include "Session.h"
#include "Logger.h"


ConnectServer::ConnectServer(Scheduler &scheduler)
	:SocketHand(scheduler)
{
}

ConnectServer::~ConnectServer(void)
{
}

MessageMap &ConnectServer::msgMap()
{
	return m_msgMap;
}

void ConnectServer::start(const std::string &ip, int port)
{
	struct sockaddr_in addr;
	uv_ip4_addr(ip.c_str(), port, &addr);

	int ret = 0;

	ret = tcp_init();
	if (ret)
	{
		LOG(ERROR) << "ConnectServer Init error :" << uv_strerror(ret);
		exit(-1);
	}

	ret = tcp_connect((struct sockaddr *)&addr);
	if (ret)
	{
		LOG(ERROR) << "ConnectServer Connect error " << uv_strerror(ret);
		exit(-1);
	}
}

void ConnectServer::msgcomming(Session *session)
{
	session->render(m_msgMap);
}
