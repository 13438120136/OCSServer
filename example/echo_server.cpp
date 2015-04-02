#include "AcceptServer.h"
#include "Logger.h"

int main()
{
	Logger log;
	Scheduler ss;
	AcceptServer ac(ss);
	ac.start("0.0.0.0", 9011);
	ss.run();
	return 0;
}