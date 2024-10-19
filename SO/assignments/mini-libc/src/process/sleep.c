#include <time.h>
#include <stddef.h>
#include <internal/syscall.h>

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    return syscall(__NR_nanosleep, req, rem);
}

unsigned int sleep(unsigned int seconds)
{
    struct timespec req = { seconds, 0 };
    return nanosleep(&req, NULL);
}
