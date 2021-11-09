// private headers
#include "search.h"

// C headers
#include <string.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROC_STEP 20000

typedef struct node_search {
    int first_el;
    int last_el;
    bool last_is_good;
    char* seq;
    int size;
} node_search;

str_t maxSeq(char* str, node_search* nodes,  size_t pid_num) {
 str_t max;
 max.size = 0;

 size_t i = 0;
 size_t j = 0;
 while (i < pid_num) {
    if (nodes[i].last_el != -1) {
        if (nodes[i].size > max.size) {
            max.seq = nodes[i].seq;
            max.size = nodes[i].size;
        }
        j = i + 1;
        while (j < pid_num) {
            if (nodes[j].first_el != -1) {
                if (nodes[i].last_is_good) {
                    if ((nodes[j].first_el - nodes[i].last_el + 1) > max.size) {
                        max.seq = str + nodes[i].last_el;
                        max.size = nodes[j].first_el - nodes[i].last_el + 1;
                    }
                }
                i = j;
                break;
            }
            ++j;
        }
        if (j >= pid_num) { break;}
    }
 }

    if (nodes[pid_num - 1].size > max.size) {
        max.seq = nodes[pid_num - 1].seq;
        max.size = nodes[pid_num - 1].size;
    }
    return max;
}

node_search pidSearch(char* str, const int start_pos, const int end_pos) {
    int left = -1;
    int max_left = -1;
    int max_right = -1;
    node_search res;

    res.first_el = res.last_el = -1;
    res.last_is_good = false;

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
        res.last_is_good = true;
    }

    if (max_left != max_right) {
        res.seq = str + max_left;
        res.size = max_right - max_left + 1;
        return res;
    }

    res.seq = NULL;
    res.size = - 1;
    return res;
}

str_t pidsSearchDelegate(char* pid_str,
                           const int size, size_t pid_num) {
    node_search* node_num = mmap(NULL,
                                 pid_num * sizeof (node_search),
                                 PROT_READ | PROT_WRITE,
                                 MAP_SHARED | MAP_ANONYMOUS,
                                 -1,
                                 0);

    if (node_num == MAP_FAILED) {
        printf("mmap failed\n");
        str_t res = {NULL, -1};
        return res;
    }

    int status;
    size_t counter = 0;
    int left = 0;
    int right = PROC_STEP > size ? size : PROC_STEP;

    while (counter < pid_num) {
        int pid = fork();

        if (pid == 0) {
            node_num[counter] = pidSearch(pid_str, left, right);
            exit(0);
        }
        ++counter;
        left = right;
        right = right + PROC_STEP > size ? size : right + PROC_STEP;
    }

    for (size_t i = 0; i < pid_num; ++i) {
        wait(&status);
    }

    str_t result = maxSeq(pid_str, node_num, pid_num);
    return result;
}


str_t search(char* str, const int size) {
    if (!str) {
        printf("String is empty!");
        str_t res = {NULL, -1};
        return res;
    }
    struct rlimit max_pids;
    getrlimit(RLIMIT_NPROC, &max_pids);
    size_t pid_num = (size_t)((size + PROC_STEP - 1)/ (double)PROC_STEP);
    if (pid_num > max_pids.rlim_max) { pid_num = max_pids.rlim_max; }

    // Use mmap for non-copy str in current pid's children
    char* pid_str = mmap(NULL,
                         size * sizeof(char),
                         PROT_READ | PROT_WRITE,
                         MAP_SHARED | MAP_ANONYMOUS,
                         -1,
                         0);

    if (pid_str == MAP_FAILED) {
        printf("mmap failed\n");
        str_t res = {NULL, -1};
        return res;
    }
    memcpy(pid_str, str, size * sizeof(char));

    return pidsSearchDelegate(pid_str, size, pid_num);
}
