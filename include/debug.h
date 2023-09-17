#ifndef DEBUG_H
#define DEBUG_H

#define ERROR_EXIT(...) ({ \
        fprintf(stderr, __VA_ARGS__); \
        exit(-1); })

#endif // DEBUG_H
