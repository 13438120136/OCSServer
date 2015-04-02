#include "MessageMap.h"
#include "Session.h"

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

void MessageMap::dispatchMsg(std::vector<char> &buf, Session &session)
{
	session.sendMessage(&buf[0], buf.size());
}
