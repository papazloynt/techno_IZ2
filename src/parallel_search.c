// private headers
#include "search.h"

// C headers
#include <string.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROC_STEP 20000
#define NEW_STEP 10

str_t maxSeq(char* str, node_search_t* nodes,  size_t pid_num) {
    if (!str) {
        printf("String is empty!");
        str_t res = {NULL, -1};
        return res;
    }
 str_t max;
 max.size = 0;

 size_t i = 0;
 size_t j = 0;
 while (i < pid_num) {
    if (nodes[i].last_el != -1) {
        if (nodes[i].data.size > max.size) {
            max.seq = nodes[i].data.seq;
            max.size = nodes[i].data.size;
        }
        j = i + 1;
        while (j < pid_num) {
            if (nodes[j].first_el != -1) {
                if (nodes[i].after_last_is_upper) {
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

    if (nodes[pid_num - 1].data.size > max.size) {
        max.seq = nodes[pid_num - 1].data.seq;
        max.size = nodes[pid_num - 1].data.size;
    }
    return max;
}

str_t pidSearchDelegate(char* pid_str,
                           const int size, size_t pid_num) {
    if (!pid_str) {
        printf("String is empty!");
        str_t res = {NULL, -1};
        return res;
    }

    node_search_t* node_num = mmap(NULL,
                                 pid_num * sizeof (node_search_t),
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

int getStep(const int size) {
    if (size <= PROC_STEP) {
        return size;
    }
    return size / NEW_STEP;
}

size_t getNumPid(const int size, const int step) {
    struct rlimit max_pids;
    getrlimit(RLIMIT_NPROC, &max_pids);
    size_t pid_num = (size_t)((size + step - 1)/ (double)step);

    if (pid_num > max_pids.rlim_max) { pid_num = max_pids.rlim_max; }

    return pid_num;
}

str_t search(char* str, const int size) {
    if (!str) {
        printf("String is empty!");
        str_t res = {NULL, -1};
        return res;
    }

    int step = getStep(size);
    size_t pid_num = getNumPid(size, step);

    // Use mmap for non-copy str in current pid's children
    char* pid_str = mmap(NULL,
                         size,
                         PROT_READ | PROT_WRITE,
                         MAP_SHARED | MAP_ANONYMOUS,
                         -1,
                         0);

    if (pid_str == MAP_FAILED) {
        printf("mmap failed\n");
        str_t res = {NULL, -1};
        return res;
    }
    memcpy(pid_str, str, size);

    return pidSearchDelegate(pid_str, size, pid_num);
}
