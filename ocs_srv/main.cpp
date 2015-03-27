#include <stdio.h>
#include <uv.h>
#include "AcceptServer.h"

int main()
{
	Scheduler sch;
	AcceptServer ac(sch);

	ac.start("0,0,0,0", 9000);
	sch.run();

	return 0;
}
