#ifdef TEST
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "timing.h"
#include "debug.h"

#define CANCEL -1

pthread_t g_tids[2];

static int timeout(void *ctx);
static int cancel(void *ctx);
static void *consumer_initialize(void *ctx);
static int get_rand_integer(void);
static void sig_handler(int signo);

int main(void)
{
	int ret;

	infof("initializing");

	if (SIG_ERR == signal(SIGINT, sig_handler)) {
		errorf("failed to add sig_handler");
		goto bail;
	}

	ret = pthread_create(&g_tids[0], NULL, timer_initialize, NULL);
	if (ret != 0) {
		errorf("failed to create timer thread");
		goto bail;
	}

	ret = pthread_create(&g_tids[1], NULL, consumer_initialize, NULL);
	if (ret != 0) {
		errorf("failed to create consumer thread");
		goto bail;
	}

	pthread_join(g_tids[0], NULL);
	pthread_join(g_tids[1], NULL);

	infof("exiting");

    return 0;
bail:
	return 1;
}

static void *consumer_initialize(void *ctx)
{
	char str[16] = {0};
	while (fgets(str, sizeof(str), stdin) != NULL) {
		struct timer timer;
		int delay, val;
		delay = atoi(str);
		val = get_rand_integer();
		clock_gettime(CLOCK_REALTIME, &timer.tm);
		if (delay != CANCEL) {
			timer.tm.tv_sec += delay;
			timer.timeout_cb = &timeout;
			timer.cancel_cb = &cancel;
			timer.ctx = (void *) malloc(sizeof(int));
			memcpy(timer.ctx, &val, sizeof(int));
			srand(time(NULL));
			debugf("set_timer(delay=%d, ctx=%d)", delay, val);
			set_timer(&timer);
		} else {
			cancel_timer();
		}
		memset(str, 0, sizeof(str));
	}
	return NULL;
}

static int get_rand_integer(void)
{
	srand(time(NULL));
	return rand() % 10;
}

static int timeout(void *ctx)
{
	debugf("timeout (ctx=%d)", *((int *) ctx));
	free(ctx);
	return 0;
}

static int cancel(void *ctx)
{
	debugf("cancel (ctx=%d)", *((int *) ctx));
	free(ctx);
	return 0;
}

static void sig_handler(int signo)
{
	if (signo == SIGINT) {
		infof("canceling threads");
		pthread_cancel(g_tids[0]);
		pthread_cancel(g_tids[1]);
	}
}
#endif
