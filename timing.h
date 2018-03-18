#ifndef _TIMING_H
#define _TIMING_H
#include <semaphore.h>
#include <pthread.h>

struct timer {
	struct timespec tm;
	int (*timeout_cb)(void *ctx);
	int (*cancel_cb)(void *ctx);
	void *ctx;
};

/**
 * @brief set timer, call timeout_cb
 * if not canceled. does not set if
 * any timer already set.
 *
 * @param[in] timer
 *
 * @return 0 if set, 1 if not set.
 */
int set_timer(struct timer *timer);

/**
 * @brief cancel existing timer, and call
 * cancel_cb.
 *
 * @return 0 if cancel, 1 if no timer to cancel.
 */
int cancel_timer(void);

/**
 * @brief initialize infinite loop,
 * that waits any timer to be set.
 *
 * @param[in] ctx
 *
 * @return 
 */
void *timer_initialize(void *ctx);

#endif
