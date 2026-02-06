#include "cmd.h"
#include "core/hal/hal_uart.h"
#include <string.h>

#define MAX_CMDS 8
#define BUF_SZ 64

typedef struct {
    const char *name;
    cmd_fn_t fn;
} cmd_t;

static cmd_t cmds[MAX_CMDS];
static int cmd_count = 0;

static char buf[BUF_SZ];
static int idx = 0;

void cmd_init(void) {
    cmd_count = 0;
    idx = 0;
}

void cmd_write(const char *s) {
    hal_uart_write(s);
}

void cmd_register(const char *name, cmd_fn_t fn) {
    if (cmd_count < MAX_CMDS) {
        cmds[cmd_count++] = (cmd_t){name, fn};
    }
}

static void execute(char *line) {
    for (int i = 0; i < cmd_count; i++) {
        if (strcmp(line, cmds[i].name) == 0) {
            cmds[i].fn(0, 0);
        }
    }
}

void cmd_poll(void) {
    int c;

    while ((c = hal_uart_getc()) >= 0) {
        if (c == '\n') {
            buf[idx] = 0;
            execute(buf);
            idx = 0;
        } else if (idx < BUF_SZ-1) {
            buf[idx++] = c;
        }
    }
}
