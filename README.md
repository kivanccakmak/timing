# timing

basic -one timer limited- watchdog library.

```c
#include "timing.h"
// setup timer for 3 seconds later

struct timer timer;

clock_gettime(CLOCK_REALTIME, &timer.tm);

timer.tm.tv_sec += 3;
timer.timeout_cb = &timeout;
timer.cancel_cb = &cancel;
timer.ctx = (void *) malloc();

set_timer(&timer);

static int cancel(void *ctx) {
	printf("cancel\n");
	return 0;
}

static int timeout(void *ctx) {
	printf("timeout\n");
	return 0;
}
```

# compile
* `make`

# run
* `./timing`

# doxygen

* `make dox`
* `firefox doc/doxygen/html/index.html`
