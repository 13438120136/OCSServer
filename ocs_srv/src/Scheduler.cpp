#include "Scheduler.h"

Scheduler::Scheduler()
{
	m_uvLoop = uv_loop_new();
}

Scheduler::~Scheduler()
{
	uv_loop_close(m_uvLoop);
	uv_loop_delete(m_uvLoop);
}

void Scheduler::run()
{
	uv_run(m_uvLoop, UV_RUN_DEFAULT);
}

uv_loop_t *Scheduler::instance()
{
	return m_uvLoop;
}
