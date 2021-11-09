// private headers
#include "search.h"

// C headers
#include <stdio.h>
#include <getopt.h>
#include <time.h>
#include <string.h>

#define AVRG 5
#define MACRO 1000000000
#define MIL 1000

int main(int argc, char *argv[]) {
    int opt;
    char* opts = "i:o:h";
    char* in = NULL;
    char* out = NULL;

    while ((opt = getopt(argc, argv, opts)) != -1) {
        switch (opt) {
            case 'i':
                in = malloc((strlen(optarg) + 1) * sizeof(char));
                strcpy(in, optarg);
                break;
            case 'o':
                out = malloc((strlen(optarg) + 1) * sizeof(char));
                strcpy(out, optarg);
                break;
            case 'h':
                printf("Use this forms: %s [-h|-i|-o] <args>\n", argv[0]);
                break;
            default:
                break;
        }
    }

    str_t str;
    str.seq = NULL;
    if (!in) {
        if (!readString(&str, stdin)) {
            printf("Read string failed\n");
            return 1;
        }
    } else {
        FILE *f = fopen(in, "r");

        if (!f) {
            printf("Open file failed\n");
            return 1;
        }

        if (!readString(&str, f)) {
            printf("Read string failed\n");
            return 1;
        }

        if (fclose(f)) {
            printf("Close file failed\n");
            return 1;
        }
    }

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    str_t res;
    for (size_t i = 0; i < AVRG; ++i) {
        res = search(str.seq, str.size);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    size_t time = ((MACRO * (end.tv_sec - start.tv_sec) +
                   (end.tv_nsec - start.tv_nsec)) / MIL) / AVRG;

    if (!out) {
        printf("Sequence :");

        for (int i = 0; i < res.size; ++i) {
            printf("%c", res.seq[i]);
        }

        printf("\nTime : %zu mks\n", time);
    } else {
        FILE *f = fopen(out, "w");

        if (!f) {
            printf("Open file failed\n");
            return 1;
        }

        fprintf(f, "Sequence :");

        for (int i = 0; i < res.size; ++i) {
            fprintf(f, "%c", res.seq[i]);
        }

        fprintf(f, "\nTime : %zu mks\n", time);

        if (fclose(f)) {
            printf("Close file failed\n");
            return 1;
        }
    }

    if (str.seq) { free(str.seq); }
    if (in) { free(in); }
    if (out) { free(out); }
    return 0;
}
