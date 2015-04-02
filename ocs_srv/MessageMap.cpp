#include "MessageMap.h"

MessageMap::MessageMap(void)
{
}

MessageMap::~MessageMap(void)
{
}

int MessageMap::check(std::vector<char> &buf)
{
	return buf.size();
}

void MessageMap::dispatchMsg(char *msg, int size)
{
}
