#ifndef MM_IO_H_
#define MM_IO_H_

/*
 * machinarium.
 *
 * Cooperative multitasking engine.
*/

typedef struct mmio mmio;

struct mmio {
	uv_os_sock_t  fd;
	uv_tcp_t      handle;
	int           close_ref;
	mm           *f;
	/* connect */
	uv_timer_t    connect_timer;
	uv_connect_t  connect;
	int           connect_timeout;
	int           connected;
	int           connect_status;
	mmfiber      *connect_fiber;
	/* accept */
	int           accept_status;
	mmfiber      *accept_fiber;
	/* read */
	uv_timer_t    read_timer;
	mmbuf         read_buf;
	int           read_size;
	int           read_timeout;
	int           read_eof;
	int           read_status;
	mmfiber      *read_fiber;
	/* write */
	uv_timer_t    write_timer;
	uv_write_t    write;
	int           write_timeout;
	int           write_status;
	mmfiber      *write_fiber;
};

void mm_io_close_handle(mmio*, uv_handle_t*);

static inline void
mm_io_timer_start(uv_timer_t *timer, uv_timer_cb callback, uint64_t time_ms)
{
	if (time_ms > 0)
		uv_timer_start(timer, callback, time_ms, 0);
}

static inline void
mm_io_timer_stop(uv_timer_t *timer)
{
	uv_timer_stop(timer);
	uv_handle_t *handle = (uv_handle_t*)timer;
	if (! uv_is_closing(handle))
		uv_close(handle, NULL);
}

#endif
