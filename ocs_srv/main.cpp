#include <stdio.h>
#include <uv.h>
#include "Logger.h"
#include "AcceptServer.h"
#include "ConnectServer.h"

int main()
{
	Logger log;
	Scheduler ss;
	AcceptServer ac(ss);
	ac.start("192.168.2.201", 9000);
	ss.run();
	return 0;
}
