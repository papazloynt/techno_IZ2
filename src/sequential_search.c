// private headers
#include "search.h"

// C headers
#include <stddef.h>

res_t search(const char* str, const int size) {
    int left = -1;
    int max_left = -1;
    int max_right = -1;

    // find first symbol - "
    int i = 0;
    while ((left == -1) && (i < size)) {
        if (str[i] == '\"') {
            left = i;
        }
        ++i;
    }

    // find max subsequence
    for (; i < size; ++i) {
        if (str[i] == '\"') {
            if ((i - left > max_right - max_left) && isAscii(str[left + 1])) {
                max_right = i;
                max_left = left;
            }
            left = i;
        }
    }

    if (max_left != max_right) {
        res_t res = {str + max_left, max_right - max_left + 1};
        return res;
    }

    res_t res = {NULL, -1};
    return res;
}

bool isAscii(const char ch) {
   if ((ch >= 65) && (ch <= 90))
       return true;
    return false;
}