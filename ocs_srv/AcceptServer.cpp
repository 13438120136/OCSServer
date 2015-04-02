#include <string.h>  
#include "AcceptServer.h"
#include "Session.h"
#include "Logger.h"

AcceptServer::AcceptServer(Scheduler &scheduler)
	:SocketHand(scheduler)
{
}

AcceptServer::~AcceptServer(void)
{
}


MessageMap &AcceptServer::msgMap()
{
	return m_msgMap;
}

void AcceptServer::msgcomming(Session *session)
{
	session->render(m_msgMap);
}

void AcceptServer::start(const std::string &ip, int port)
{
	struct sockaddr_in addr;
	uv_ip4_addr(ip.c_str(), port, &addr);

	int ret = tcp_init();
	if (ret)
	{
		LOG(ERROR) << "AcceptServer Init error :" << uv_strerror(ret);
		exit(-1);
	}

	ret = tcp_bind((struct sockaddr *)&addr);
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
