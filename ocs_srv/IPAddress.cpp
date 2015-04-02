#include "IPAddress.h"

IPAddress::IPAddress()
{
}

IPAddress::IPAddress(const std::string &ip, unsigned short port)
{
	m_ip = ip;
	m_port = port;
}

IPAddress::~IPAddress()
{
}

struct sockaddr_in IPAddress::address() const
{
	struct sockaddr_in addr;
	uv_ip4_addr(m_ip.c_str(), m_port, &addr);
	return addr;
}

void IPAddress::setIpAndPort(const std::string &ip, unsigned short port)
{
	m_ip = ip;
	m_port = port;
}

std::string IPAddress::ip()
{
	return m_ip;
}

unsigned short IPAddress::port()
{
	return m_port;
}
