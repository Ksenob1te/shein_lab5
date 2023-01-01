#ifndef MEPHI_DOZEN_METHODS_H
#define MEPHI_DOZEN_METHODS_H
#include "abonent.h"

int check_phone(const char *phone);
int check_number(const char *time);
int (*get_comparator(int field, int reverse)) (const void *, const void *);
void swap(void *a, void *b, size_t len);
size_t str_to_size_t(const char *str);
Abonent generate_random();

#endif
