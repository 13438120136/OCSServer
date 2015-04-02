#ifndef _IPADDRESS_INCLUDE
#define _IPADDRESS_INCLUDE

#include <uv.h>
#include <string>

class IPAddress
{
public:
	IPAddress(void);
	IPAddress(const std::string &ip, unsigned short port);
	void setIpAndPort(const std::string &ip, unsigned short port);
	struct sockaddr_in address() const;
	std::string ip();
	unsigned short port();
	~IPAddress(void);

private:
	std::string m_ip;
	unsigned short m_port;
};

#endif
