#include "core/include/nkernel.h"

/* tasks externas */
extern void blink_task(void);
extern void term_task(void);

int main(void)
{
    kernel_init();

    task_create(blink_task, 512);
    task_create(term_task, 512);

    scheduler_start();

    while (1); // nunca debería llegar acá
}
