#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "wordlist.h"

#define NONE 0
#define DL 1
#define DW 2
#define TL 3
#define TW 4
#define HORIZONTAL 0
#define VERTICAL 1

typedef struct space{
    char letter; //letter the space holds
    int power;
    int filled; //1 for holds a letter, 0 doesnt hold a letter
    int checked_h;
    int checked_v;
}space_t;

typedef struct board{
    int num_letters; //number of letters present on board
    space_t ***spaces; // 2d array to hold the spaces
}board_t;



space_t* new_space(int);

int get_power(int,int);

board_t* new_board();



void print_board(board_t*);

board_t* read_to_board(board_t*,FILE*);


void add_word(board_t*, pot_word_ll*,int);

void delete_board(board_t*);

void mark_as_checked(int, int, board_t*, int);

void board_to_file(board_t*,FILE*);
