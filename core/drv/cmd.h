/* CMD DRIVER
 * HAL use: UART
 * DSCR: Recognize commands like POSIX shell
*/

#pragma once

typedef void (*cmd_fn_t)(int argc, char **argv);

void cmd_init(void);
void cmd_poll(void);

void cmd_write(const char *s);
void cmd_register(const char *name, cmd_fn_t fn);
