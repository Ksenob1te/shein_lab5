#include "abonent.h"
#include <stdlib.h>

void clear(Abonent *this) {
    free(this->name);
    free(this->phone);
    free(this->time);
}

Abonent new_abonent(char *name, char *phone, char *time) {
    return (Abonent) {
        .name=name, .phone=phone, .time=time,
        .clear=clear
    };
}
