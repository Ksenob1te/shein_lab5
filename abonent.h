#ifndef MEPHI_DOZEN_ABONENT_H
#define MEPHI_DOZEN_ABONENT_H

typedef struct Abonent {
    char *name;
    char *phone;
    char *time;

    void (*clear) (struct Abonent*);
} Abonent;

Abonent new_abonent(char *name, char *phone, char *time);

#endif
