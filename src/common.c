// private headers
#include "search.h"

bool readString(str_t* str, FILE* in) {
    if (str || !in) {
        return false;
    }
    int digit = 10;
    char size_[digit];
    fgets(size_, digit, in);

    int size = (int)strtol(size_, NULL, 10);

    str->seq = (char*)malloc(size);                                     // check malloc
    fgets(str->seq, size, in);

    str->size = size;
    return true;
}

node_search_t pidSearch(char* str, const int start_pos, const int end_pos) {
    int left = -1;
    int max_left = -1;
    int max_right = -1;
    node_search_t res;

    res.first_el = res.last_el = -1;
    res.after_last_is_upper = false;

    // find first symbol - "
    int i = start_pos;
    while (i < end_pos) {
        if (str[i] == '\"') {
            left = i;
            res.first_el = res.last_el = i;
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
            res.last_el = left = i;
        }
    }

    if ((res.last_el != -1) && (isUpper(str[res.last_el + 1]))) {
        res.after_last_is_upper = true;
    }

    if (max_left != max_right) {
        res.data.seq = str + max_left;
        res.data.size = max_right - max_left + 1;
        return res;
    }

    res.data.seq = NULL;
    res.data.size = - 1;
    return res;
}

bool isUpper(const char ch) {
    if ((ch >= 65) && (ch <= 90))
        return true;
    return false;
}
