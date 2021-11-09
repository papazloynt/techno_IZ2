// private headers
#include "search.h"

bool isUpper(const char ch) {
    if ((ch >= 65) && (ch <= 90))
        return true;
    return false;
}

bool readString(str_t* str, FILE* in) {
    if (!str || !in) {
        return false;
    }
    int MAX_DIGIT_SIZE = 10;
    char count[MAX_DIGIT_SIZE];
    fgets(count, MAX_DIGIT_SIZE, in);
    int _count = (int)strtol(count, NULL, 10);
    str->seq = (char*)malloc(_count);                                     // check malloc
    fgets(str->seq, _count, in);
    str->size = _count;
    return true;
}
