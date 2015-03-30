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
	ac.start("0.0.0.0", 9000);
	ss.run();
	return 0;
}
