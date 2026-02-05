#include "kernel.h"
#include "scheduler.h"
#include "nkernel.h"
#include "hal/hal.h"
#include "hal/hal_timer.h"


volatile uint64_t nk_ticks = 0;

static void kernel_tick(void) {
    nk_ticks++;
    scheduler_tick();
}

void kernel_init(void) {
    hal_init();
    scheduler_init();
    hal_timer_init(1000, scheduler_tick);
}

//extern const nk_app_t __start_nk_apps[];
//extern const nk_app_t __stop_nk_apps[];

void kernel_launch_apps(void) {
    /*for (const nk_app_t *app = __start_nk_apps;
         app < __stop_nk_apps;
         app++) {

        task_create(app->entry, app->stack_size);
    }*/
}
