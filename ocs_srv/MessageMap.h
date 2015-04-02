#ifndef _MESSAGEMAP_INCLUDE
#define _MESSAGEMAP_INCLUDE

#include <vector>

class Session;
class MessageMap
{
public:
	MessageMap();
	~MessageMap();

	virtual int check(std::vector<char> &buf);
	void dispatchMsg(std::vector<char> &buf, Session &session);
};

#endif
