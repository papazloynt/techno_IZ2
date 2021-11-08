#ifndef IZ2_SEARCH_H
#define IZ2_SEARCH_H
// C headers
#include <stdbool.h>

typedef struct res_t {
    const char* seq;
    int size;
} res_t;

res_t search(const char* str, const int size);

bool isAscii(const char ch);

#endif //IZ2_SEARCH_H
