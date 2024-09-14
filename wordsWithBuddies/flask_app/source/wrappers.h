#include "wordsearch.h"

int words_at_spot_horizontal(int,int,board_t*, letter_set_t*,pot_word_ll*,char**,FILE*,int,int*);

int words_at_spot_vertical(int,int,board_t*, letter_set_t*,pot_word_ll*,char**,FILE*,int,int*);

int traverse_board(board_t*, char**, letter_set_t*, pot_word_ll*,FILE*,int,int*);
