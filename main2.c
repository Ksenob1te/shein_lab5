#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "methods.h"
#include "abonent.h"
#include "file_worker.h"


int main(int argc, char *argv[]) {
    // parse command line arguments
    char *elements_count = NULL, *arrays_count = NULL, *type = NULL, *dir = NULL, *field = NULL;
    int status = 0, tempOptind = 0;
    while (optind < argc && tempOptind < argc) {
        tempOptind = optind;
        status = getopt(argc, argv, "s:f:d:");
        if (status != -1) {
            switch (status) {
                case 's': type = optarg; break;
                case 'f': field = optarg; break;
                case 'd': dir = optarg; break;
                default: break;
            }
        } else {
            optind = tempOptind;
            if (!elements_count) elements_count = argv[tempOptind];
            else arrays_count = argv[tempOptind];
            optind++;
        }
    }
    int sort_type = -1, sort_field = -1, sort_dir = -1;

    // check input and output files
    if (!elements_count || !arrays_count) { fprintf(stderr, "no elements count or arrays count file\n"); return 132;}

    // check sorting type
    if (!type || !strcmp(type, "qsort")) sort_type = 0;
    if (!strcmp(type, "shaker")) sort_type = 1;
    if (!strcmp(type, "shell")) sort_type = 2;
    if (sort_type == -1) { fprintf(stderr, "wrong sort method, expected 'qsort', 'shaker' or 'shell'"); return 132;}

    // check sort direction
    if (!type || !strcmp(dir, "up")) sort_dir = 0;
    if (!strcmp(dir, "down")) sort_dir = 1;
    if (sort_dir == -1) { fprintf(stderr, "wrong sort direction, expected 'up' or 'down'"); return 132;}

    // check sorting field
    if (!field || !strcmp(field, "name")) sort_field = 0;
    if (!strcmp(field, "phone")) sort_field = 1;
    if (!strcmp(field, "time")) sort_field = 2;
    if (sort_field == -1) { fprintf(stderr, "wrong sort field, expected 'name', 'phone' or 'time'"); return 132;}


    int (*comp)() = get_comparator(sort_field, sort_dir);
    void (*sort)() = get_sort(sort_type);

    clock_t whole_process = 0;
    for (int j = 0; j < str_to_size_t(arrays_count); ++j) {
        size_t len = str_to_size_t(elements_count);
        Abonent *array = malloc(len * sizeof(Abonent));
        srand(time(NULL));
        for (int i = 0; i < len; ++i)
            array[i] = generate_random();

        clock_t begin = clock();
        sort((void *) array, len, sizeof(Abonent), comp);
        clock_t end = clock();

        whole_process += (end - begin);
        printf("Time %d: %lf\n", j + 1, (double)(end - begin) / CLOCKS_PER_SEC);

        for (int i = 0; i < len; ++i) {
            array[i].clear(array + i);
        }
        free(array);
    }
    printf("Average time per iteration: %lf\n", (double)whole_process / CLOCKS_PER_SEC / str_to_size_t(arrays_count));
}