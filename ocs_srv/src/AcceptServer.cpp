#include <string.h>  
#include "AcceptServer.h"
#include "Session.h"
#include "Logger.h"

AcceptServer::AcceptServer(Scheduler &scheduler)
	:SocketHand(scheduler)
{
	m_msgMap = new MessageMap;
}

AcceptServer::~AcceptServer(void)
{
	if (m_msgMap != nullptr)
	{
		delete m_msgMap;
		m_msgMap = nullptr;
	}
}


MessageMap &AcceptServer::msgMap()
{
	return *m_msgMap;
}

void AcceptServer::setMsgMap(MessageMap *msgMap)
{
	if (this->m_msgMap)
	{
		delete this->m_msgMap;
		this->m_msgMap = msgMap;
	}
}

void AcceptServer::msgcomming(Session *session)
{
	session->render(*m_msgMap);
}

void AcceptServer::connect(Session *session)
{
	auto &address = session->getAddress();
	LOG(INFO) << address.ip() << ":" <<address.port() << "come";
}

void AcceptServer::disconnect(Session *session)
{
	auto &address = session->getAddress();
	LOG(INFO) << address.ip() << ":" <<address.port() << "go";
}

void AcceptServer::start(const IPAddress &address)
{
	int ret = tcp_init();
	if (ret)
	{
		LOG(ERROR) << "AcceptServer Init error :" << uv_strerror(ret);
		exit(-1);
	}

	ret = tcp_bind((struct sockaddr *)&address.address());
	if (ret)
	{
		LOG(ERROR) << "AcceptServer Bind error " << uv_strerror(ret);
		exit(-1);
	}

	ret = tcp_listen();
    if (ret)
	{
        LOG(ERROR) << "AcceptServer Listen error " << uv_strerror(ret);
        exit(-1);
    }

	LOG(INFO) << "AcceptServer Start Success";
}

void AcceptServer::start(const std::string &ip, unsigned int port)
{
	IPAddress address(ip, port);
	start(address);
}
