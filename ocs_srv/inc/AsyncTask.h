#ifndef _ASYNCTASK_INCLUDE
#define _ASYNCTASK_INCLUDE

#include <uv.h>
#include "Scheduler.h"

#ifdef OCSSERVER_API_EXPORTS
#define OCSSERVER_API __declspec(dllexport)
#else
#define OCSSERVER_API __declspec(dllimport)
#endif

class OCSSERVER_API AsyncTask
{
public:
	AsyncTask(Scheduler &scheduler);
	~AsyncTask();
	void notify();

	virtual void exec() = 0;

private:
	Scheduler &m_scheduler;
	uv_async_t m_async_t;
};

#endif
