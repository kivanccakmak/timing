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
```

# compile
* `make`

# run
* `./timing`

# doxygen

* `make dox`
* `firefox doc/doxygen/html/index.html`
