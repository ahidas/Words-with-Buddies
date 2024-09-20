#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 15

typedef struct pot_word pot_word;
typedef struct pot_word{
    int points;
    int x;
    int y;
    int dir;
    int num_new;
    char* word;
    pot_word* next;
} pot_word;

typedef struct pot_word_ll{
    pot_word* head;
}pot_word_ll;

pot_word* new_potword(int,int,int,int,char*,int);

pot_word_ll* new_pot_word_ll(void);

void delete_pot_word(pot_word*);

void delete_pot_word_ll(pot_word_ll*);

pot_word* add_pot_word(pot_word*,pot_word_ll*);

void print_potwords(pot_word_ll*,int);

pot_word* longest_potword(pot_word_ll*);
