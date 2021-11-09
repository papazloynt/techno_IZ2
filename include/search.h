#ifndef IZ2_SEARCH_H
#define IZ2_SEARCH_H
// C headers
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

typedef struct str_t {
    char* seq;
    int size;
} str_t;

str_t search(char* str, const int size);

bool readString(str_t* str, FILE* in);

bool isUpper(const char ch);

#endif //IZ2_SEARCH_H
