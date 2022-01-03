/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

#ifdef DEBUG
#include "SEGGER_RTT.h"
#endif

#include "wntr_ticks.h"
#include <sys/stat.h>
#include <sys/times.h>

extern int _estack;

void* _sbrk(int incr) {
    static unsigned char* heap = NULL;
    unsigned char* prev_heap;

    if (heap == NULL) {
        heap = (unsigned char*)&_estack;
    }
    prev_heap = heap;

    heap += incr;

    return prev_heap;
}

int _close(int file) { return -1; }

int _fstat(int file, struct stat* st) {
    st->st_mode = S_IFCHR;

    return 0;
}

int _isatty(int file) { return 1; }

int _lseek(int file, int ptr, int dir) { return 0; }

__attribute__((noreturn)) void _exit(int status) {
    __asm("BKPT #0");
    __builtin_unreachable();
}

void _kill(int pid, int sig) { return; }

int _getpid(void) { return -1; }

int _write(int file, char* ptr, int len) { return -1; }

int _read(int file, char* ptr, int len) { return -1; }

void _putchar(char c) {
#ifdef DEBUG
    SEGGER_RTT_PutChar(0, c);
#else
    (void)(c);
#endif
}

clock_t _times(struct tms* tp) {
    clock_t timeval = wntr_ticks();
    if (tp != NULL) {
        tp->tms_utime = timeval; /* user time */
        tp->tms_stime = 0;       /* system time */
        tp->tms_cutime = 0;      /* user time, children */
        tp->tms_cstime = 0;      /* system time, children */
    }

    return timeval;
};
