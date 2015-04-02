#include "ConnectServer.h"
#include "Session.h"
#include "Logger.h"


ConnectServer::ConnectServer(Scheduler &scheduler)
	:SocketHand(scheduler)
{
	m_msgMap = new MessageMap;
}

ConnectServer::~ConnectServer(void)
{
	if (m_msgMap != nullptr)
	{
		delete m_msgMap;
		m_msgMap = nullptr;
	}
}

MessageMap &ConnectServer::msgMap()
{
	return *m_msgMap;
}

void ConnectServer::start(const IPAddress &address)
{
	int ret = tcp_init();
	if (ret)
	{
		LOG(ERROR) << "ConnectServer Init error :" << uv_strerror(ret);
		exit(-1);
	}

	ret = tcp_connect((struct sockaddr *)&address.address());
	if (ret)
	{
		LOG(ERROR) << "ConnectServer Connect error " << uv_strerror(ret);
		exit(-1);
	}
}

void ConnectServer::start(const std::string &ip, unsigned int port)
{
	IPAddress address(ip, port);
	start(address);
}

void ConnectServer::msgcomming(Session *session)
{
	session->render(*m_msgMap);
}
