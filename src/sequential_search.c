// private headers
#include "search.h"

str_t pid_search(char* str, const int start_pos, const int end_pos) {
    if (!str) {
        printf("String is empty!");
        str_t res = {NULL, -1};
        return res;
    }

    int left = -1;
    int max_left = -1;
    int max_right = -1;

    // find first symbol - "
    int i = start_pos;
    while (i < end_pos) {
        if (str[i] == '\"') {
            left = i;
            break;
        }
        ++i;
    }

    // find max subsequence
    for (; i < end_pos; ++i) {
        if (str[i] == '\"') {
            if ((i - left > max_right - max_left) && isUpper(str[left + 1])) {
                max_right = i;
                max_left = left;
            }
            left = i;
        }
    }

    if (max_left != max_right) {
        str_t res = {str + max_left, max_right - max_left + 1};
        return res;
    }

    str_t res = {NULL, -1};
    return res;
}

str_t search(char* str, const int size) {
    if (!str) {
        printf("String is empty!");
        str_t res = {NULL, -1};
        return res;
    }
   return pid_search(str, 0, size);
}
