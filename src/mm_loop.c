
/*
 * machinarium.
 *
 * cooperative multitasking engine.
*/

#include <machinarium_private.h>
#include <machinarium.h>

int mm_loop_init(mm_loop_t *loop)
{
	loop->poll = mm_epoll_if.create();
	if (loop->poll == NULL)
		return -1;
	mm_timers_init(&loop->timers);
	return 0;
}

int mm_loop_shutdown(mm_loop_t *loop)
{
	mm_timers_free(&loop->timers);
	int rc;
	rc = loop->poll->iface->shutdown(loop->poll);
	if (rc == -1)
		return -1;
	loop->poll->iface->free(loop->poll);
	return 0;
}

int mm_loop_step(mm_loop_t *loop)
{
	int timeout = INT_MAX;
	mm_timer_t *min;
	min = mm_timers_min(&loop->timers);
	if (min == NULL)
		timeout = min->timeout;
	int rc;
	rc = loop->poll->iface->step(loop->poll, timeout);
	if (rc == -1)
		return -1;
	return 0;
}

int mm_loop_add(mm_loop_t *loop, mm_fd_t *fd, int mask)
{
	return loop->poll->iface->add(loop->poll, fd, mask);
}

int mm_loop_modify(mm_loop_t *loop, mm_fd_t *fd, int mask)
{
	return loop->poll->iface->modify(loop->poll, fd, mask);
}

int mm_loop_delete(mm_loop_t *loop, mm_fd_t *fd)
{
	return loop->poll->iface->del(loop->poll, fd);
}
