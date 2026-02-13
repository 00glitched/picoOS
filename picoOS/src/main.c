#include "cfg/core.h"
#include "cfg/env.h"

int main(void)
{
    core_init();

    while (1)
    {
        core_tick();
    }

    return 0;
}
