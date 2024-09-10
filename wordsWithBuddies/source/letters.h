#include "binsearch.h"
typedef struct letter letter_t;

typedef struct letter{
    char letter;
    int pos;
    int used;
    letter_t* next;
}letter_t;

typedef struct letter_set{
    letter_t* head;
    int num;
} letter_set_t;


letter_t* new_letter(char,int);

letter_set_t* new_letter_set();

letter_set_t* add_letter(letter_set_t*,char,int);

void delete_letter(letter_t*);

letter_set_t* copy_set(letter_set_t*);

void set_used(letter_set_t*);

int set_compare(letter_set_t*,letter_set_t*,int,int*);

int parse_string(letter_set_t*,char* args, int flag);

void print_set(letter_set_t*);

void delete_set(letter_set_t*);

int letter_points(char);

