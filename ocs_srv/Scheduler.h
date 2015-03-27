#ifndef _SCHEDULER_INCLUDE
#define _SCHEDULER_INCLUDE

#include <uv.h>

/*
 * 程序的调度器 
 */
class Scheduler
{
public:
	Scheduler();
	~Scheduler();
	uv_loop_t *instance();

	void run();

private:
	uv_loop_t *m_uvLoop;
};

#endif
