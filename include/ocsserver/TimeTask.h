#ifndef _TIMETASK_INCLUDE
#define _TIMETASK_INCLUDE

#include <uv.h>
#include "Scheduler.h"

#ifdef OCSSERVER_API_EXPORTS
#define OCSSERVER_API __declspec(dllexport)
#else
#define OCSSERVER_API __declspec(dllimport)
#endif

class OCSSERVER_API TimeTask
{
public:
	TimeTask(Scheduler &scheduler);
	~TimeTask();

	void setTimeOut(uint64_t timeout);
	void setInterval(uint64_t interval);
	void start();
	void stop();
	void restart();
	virtual void work() = 0;

private:
	Scheduler &m_scheduler;
	uv_timer_t m_timer;
	uint64_t m_timeout;
	uint64_t m_interval;
};

#endif
