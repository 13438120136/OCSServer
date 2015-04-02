#include "AsyncTask.h"

static void async_cb(uv_async_t* handle)
{
	AsyncTask *obj = (AsyncTask *)handle->data;
	obj->exec();	
}

AsyncTask::AsyncTask(Scheduler &scheduler)
	:m_scheduler(scheduler)
{
	uv_async_init(scheduler.instance(), &m_async_t, async_cb);
	m_async_t.data = this;
}

AsyncTask::~AsyncTask(void)
{
}

void AsyncTask::notify()
{
	uv_async_send(&m_async_t);
}
