#ifndef _KBHIT_H
#define _KBHIT_H

#include <sys/types.h>
#include <sys/time.h>   // struct timeval
#include <sys/select.h> // select(), FD_*
#include <unistd.h>     // STDIN_FILENO

static int kbhit(void) {
    struct timeval tv = { 0, 0 };
    fd_set read_fd;
    FD_ZERO(&read_fd);
    FD_SET(STDIN_FILENO, &read_fd);

    // select() returns >0 if data is ready
    return select(STDIN_FILENO + 1, &read_fd, nullptr, nullptr, &tv) > 0;
}

#endif // _KBHIT_H
