#ifndef _MESSAGEMAP_INCLUDE
#define _MESSAGEMAP_INCLUDE

#include <vector>

class MessageMap
{
public:
	MessageMap();
	~MessageMap();

	virtual int check(std::vector<char> &buf);
	void dispatchMsg(char *msg, int size);
};

#endif
