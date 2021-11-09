// private headers
#include "search.h"

str_t search(char* str, const int size) {
    if (!str) {
        printf("String is empty!");
        str_t res = {NULL, -1};
        return res;
    }
    node_search_t tmp = pidSearch(str, 0, size);
    return tmp.data;
}
