#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "timing.h"
#include "debug.h"

typedef enum {
	INSTRUCTION_WAIT,
	TIMER_WAIT,
	NUM_STATES
} cond_state;

struct tic {
	cond_state state;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
	sem_t sem_obj;
};

struct timer g_timer;
struct tic g_tic;

void *timer_initialize(void *ctx)
{
	int ret;
	struct timer timer;
	ret = pthread_mutex_init(&g_tic.mutex, NULL);
	ret = pthread_cond_init(&g_tic.cond, NULL);
	ret = sem_init(&g_tic.sem_obj, 0, 0);

	while (1) {
		g_tic.state = INSTRUCTION_WAIT;
		debugf("pthread_cond_wait()");
		ret = pthread_cond_wait(&g_tic.cond, &g_tic.mutex);
		memcpy(&timer, &g_timer, sizeof(struct timer));
		g_tic.state = TIMER_WAIT;
		debugf("sem_timedwait()");
		ret = sem_timedwait(&g_tic.sem_obj, &timer.tm);
		debugf("ret: %d", ret);
		if (ret == 0) {
			timer.cancel_cb(timer.ctx);
		} else {
			timer.timeout_cb(timer.ctx);
		}
	}
	return NULL;
}

int set_timer(struct timer *timer)
{
	if (g_tic.state == INSTRUCTION_WAIT) {
		debugf("memcpy");
		memcpy(&g_timer, timer, sizeof(struct timer));
		debugf("pthread_cond_signal()");
		pthread_cond_signal(&g_tic.cond);
		return 0;
	}
	debugf("timer already set");
	return 1;
}

int cancel_timer(void)
{
	if (g_tic.state == TIMER_WAIT) {
		sem_post(&g_tic.sem_obj);
		return 0;
	}
	debugf("no task to cancel\n");
	return 1;
}
