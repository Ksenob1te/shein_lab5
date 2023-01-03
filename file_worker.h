#ifndef FILE_WORKER_H
#define FILE_WORKER_H

Abonent * enter_array(FILE *IF, int *len);
void fprint_array(FILE *i_file, const Abonent *array, const int *len);
char *freadline(FILE *file);
void (*get_sort(int sort_type))
        (void* arr, size_t size, size_t sizeOfElement, int (*comparator(const void*, const void*)));
#endif
