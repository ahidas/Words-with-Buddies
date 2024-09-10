#include "board.h"

letter_set_t* letters_horizontal(int,int,board_t*,letter_set_t*);

letter_set_t* letters_vertical(int,int,board_t*,letter_set_t*);

int check_boundaries_horizontal(int,int,board_t*,char*,char**,int);

int check_boundaries_vertical(int,int,board_t*,char*,char**,int);

int get_points_horizontal(pot_word*,board_t*);

int get_points_vertical(pot_word*,board_t*);

int starting_word(board_t*,letter_set_t*,char** array,int* letter_indexes, pot_word_ll* words);
