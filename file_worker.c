#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abonent.h"
#include "methods.h"

char *freadline(FILE *file) {
    char *ptr = (char *) malloc(sizeof(char));
    char buf[81];
    int n, len = 0;
    *ptr = '\0';
    do {
        n = fscanf(file, "%80[^\n]", buf);
        if (n < 0) {
            if (len > 0) n = 0;
            else {
                free(ptr);
                return NULL;
            }
        }
        if (n == 0)
            fscanf(file, "%*c");
        else {
            len += strlen(buf);
            ptr = (char *) realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (n > 0);
    return ptr;
}

Abonent * enter_array(FILE *IF, int *len) {
    int status = 0;
    Abonent *array = malloc(10 * sizeof(Abonent));
    int size = 10, i = 0;
    for (; !status; ++i) {
        if (i >= size) {
            array = realloc(array, (size + 10) * sizeof(Abonent));
            size += 10;
        }

        char *name = freadline(IF);
        char *phone = freadline(IF);
        char *time = freadline(IF);
        if (!name || !phone || !time) {
            status = 1;
        } else if (check_phone(phone) || check_number(time)) {
            fprintf(stderr, "wrong format of input, %d agent skipped\n", i + 1);
            i--;
        } else {
            array[i] = new_abonent(name, phone, time);
        }
    }
    i--;
    array = realloc(array, i * sizeof(Abonent));
    *len = i;
    return array;
}


void fprint_array(FILE *i_file, const Abonent *array, const int *len) {
    for (int i = 0; i < *len; ++i) {
        fprintf(i_file, "Agent %d: %s; %s; %s\n", i + 1, (array + i)->name, (array + i)->phone, (array + i)->time);
    }
}
