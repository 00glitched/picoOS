#include "core/drivers/cmd.h"
#include "core/include/nkernel.h"

static void hello_cmd(int argc, char **argv) {
    cmd_write("Hola picoOS!\r\n");
}

void term_task(void) {
    static int init = 0;

    if (!init) {
        cmd_init();
        cmd_register("hello", hello_cmd);
        init = 1;
    }

    cmd_poll();
    nk_sleep_ms(5);
}
