#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "methods.h"
#include "abonent.h"
#include "file_worker.h"


int main(int argc, char *argv[]) {
    // parse command line arguments
    char *input_file = NULL, *output_file = NULL, *type = NULL, *dir = NULL, *field = NULL;
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
            if (!input_file) input_file = argv[tempOptind];
            else output_file = argv[tempOptind];
            optind++;
        }
    }
    int sort_type = -1, sort_field = -1, sort_dir = -1;

    // check input and output files
    if (!input_file || !output_file) { fprintf(stderr, "no input or output file\n"); return 132;}

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


    FILE *i_file = fopen(input_file, "r"), *o_file = fopen(output_file, "w");
    if (i_file == NULL) { fprintf(stderr, "cant open input file\n"); return 132;}
    int len = 0;

    Abonent *array = enter_array(i_file, &len);

    int (*comp)() = get_comparator(sort_field, sort_dir);
    void (*sort)() = get_sort(sort_type);
    sort((void *) array, len, sizeof(Abonent), comp);
    fprint_array(o_file, array, &len);

    for (int i = 0; i < len; ++i) {
        array[i].clear(array + i);
    }
    free(array);
    fclose(i_file);
    fclose(o_file);
}