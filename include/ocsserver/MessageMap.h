#ifndef _MESSAGEMAP_INCLUDE
#define _MESSAGEMAP_INCLUDE

#include <vector>

#ifdef OCSSERVER_API_EXPORTS
#define OCSSERVER_API __declspec(dllexport)
#else
#define OCSSERVER_API __declspec(dllimport)
#endif

class Session;
class OCSSERVER_API MessageMap
{
public:
	MessageMap();
	~MessageMap();

	virtual int check(std::vector<char> &buf);
	void dispatchMsg(std::vector<char> &buf, Session &session);
};

#endif
