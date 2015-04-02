#include "AcceptServer.h"
#include "Logger.h"

int main()
{
	Logger log;
	Scheduler scheduler;

	AcceptServer acceptServer(scheduler);
	acceptServer.start("0.0.0.0", 9011);

	scheduler.run();
	return 0;
}