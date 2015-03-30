#include <stdio.h>
#include <uv.h>
#include "AcceptServer.h"
#include "ConnectServer.h"

int main()
{
	Scheduler sch;
	ConnectServer ac(sch);

	ac.start("192.168.2.201", 9000);
	sch.run();

	return 0;
}
