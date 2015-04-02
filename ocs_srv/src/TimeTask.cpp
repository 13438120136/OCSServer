#include "TimeTask.h"

static void timer_cb(uv_timer_t* handle)
{
	TimeTask *obj = (TimeTask *)handle->data;
	obj->work();
}

TimeTask::TimeTask(Scheduler &scheduler)
	:m_scheduler(scheduler)
{
	uv_timer_init(m_scheduler.instance(), &m_timer);
	m_timer.data = this;
	m_timeout = 0;
	m_interval = 0;
}

TimeTask::~TimeTask(void)
{
}

void TimeTask::start()
{
	uv_timer_start(&m_timer, timer_cb, m_timeout, m_interval);
}

void TimeTask::stop()
{
	uv_timer_stop(&m_timer);
}

void TimeTask::restart()
{
	uv_timer_again(&m_timer);
}

void TimeTask::setTimeOut(uint64_t timeout)
{
	m_timeout = timeout;
}

void TimeTask::setInterval(uint64_t interval)
{
	m_interval = interval;
	uv_timer_set_repeat(&m_timer, m_interval);
}