#ifndef _SCHEDULER_INCLUDE
#define _SCHEDULER_INCLUDE

#include <uv.h>

#ifdef OCSSERVER_API_EXPORTS
#define OCSSERVER_API __declspec(dllexport)
#else
#define OCSSERVER_API __declspec(dllimport)
#endif

/*
 * 程序的调度器 
 */
class OCSSERVER_API Scheduler
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
