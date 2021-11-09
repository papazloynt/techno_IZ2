// private headers
#include "search.h"

// C headers
#include <stdio.h>
#include <getopt.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int opt;
    char* opts = "i:o:h";
    char* input = NULL;
    char* output = NULL;

    while ((opt = getopt(argc, argv, opts)) != -1) {
        switch (opt) {
            case 'i':
                input = malloc((strlen(optarg) + 1) * sizeof(char));
                strcpy(input, optarg);
                break;
            case 'o':
                output = malloc((strlen(optarg) + 1) * sizeof(char));
                strcpy(output, optarg);
                break;
            case 'h':
                printf("Use this forms: %s [-h|-i|-o] <args>\n", argv[0]);
                break;
            default:
                break;
        }
    }


    str_t str;

    if (!input) {
        if (!readString(&str, stdin)) {
            printf("Reading string failed\n");
            return 1;
        }
    } else {
        FILE *file = fopen(input, "r");

        if (!file) {
            printf("Opening file failed\n");
            return 1;
        }

        if (!readString(&str, file)) {
            printf("Reading string failed\n");
            return 1;
        }

        if (fclose(file)) {
            printf("Closing file failed\n");
            return 1;
        }
    }
    size_t calls_count = 5;

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    str_t result;
    for (size_t i = 0; i < calls_count; ++i) {
        result = search(str.seq, str.size);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    size_t time = (1000000000 * (end.tv_sec - start.tv_sec) +
                   (end.tv_nsec - start.tv_nsec)) / 1000;

    if (!output) {
        printf("Result :");

        for (int i = 0; i < result.size; ++i) {
            printf("%c", result.seq[i]);
        }
        printf("\nTime : %zu mks\n\n", time / calls_count);
    } else {
        FILE *file = fopen(output, "w");

        if (!file) {
            printf("Opening file failed\n");
            return 1;
        }

        fprintf(file, "Result %s:\n", result.seq);
        fprintf(file, "Time : %zu mks\n\n", time / calls_count);

        if (fclose(file)) {
            printf("Closing file failed\n");
            return 1;
        }
    }

    free(str.seq);
    if (input) {
        free(input);
    }
    if (output) {
        free(output);
    }
    return 0;
}
