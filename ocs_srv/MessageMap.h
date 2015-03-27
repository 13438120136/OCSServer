#ifndef _MESSAGEMAP_INCLUDE
#define _MESSAGEMAP_INCLUDE

class MessageMap
{
public:
	MessageMap();
	~MessageMap();

	void dispatchMsg(char *msg, int size);
};

#endif
