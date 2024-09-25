#include "wrappers.h"
int words_at_spot_horizontal(int y,int x,board_t* board, letter_set_t* set, pot_word_ll* words, char** array,FILE* file,int num_words, int* letter_indexes, int floating_letter){
    //first horizontal
    letter_set_t* temp = copy_set(set);
    pot_word* temp_pot;
    int total_words = 0;
    pot_word_ll* words_horizontal = new_pot_word_ll();
    letters_horizontal(y,x,board,temp);
    words_with_letters(temp, words_horizontal,array,letter_indexes);
    pot_word* curr = words_horizontal->head;
    while(curr != NULL){
        if(check_boundaries_horizontal(y,x-curr->x,board,curr->word,array,num_words)){
            temp_pot = new_potword(10,x-curr->x,y,0,curr->word,curr->num_new + floating_letter);
            temp_pot->points = get_points_horizontal(temp_pot,board);
            add_pot_word(temp_pot,words);
            total_words++;
        }
        curr = curr->next;
    }
    ///now vertical
    delete_set(temp);
    delete_pot_word_ll(words_horizontal);
    return total_words;
}
int words_at_spot_vertical(int y,int x,board_t* board, letter_set_t* set, pot_word_ll* words, char** array,FILE* file,int num_words, int* letter_indexes,int floating_letter){
    letter_set_t* temp = copy_set(set);
    pot_word* temp_pot;
    int total_words = 0;
    pot_word_ll* words_vertical= new_pot_word_ll();
    letters_vertical(y,x,board,temp);
    words_with_letters(temp, words_vertical,array, letter_indexes);
    pot_word* curr = words_vertical->head;
    while(curr != NULL){
        if(check_boundaries_vertical(y-curr->y,x,board,curr->word,array,num_words)){
            temp_pot = new_potword(10,x,y-curr->y,1,curr->word,curr->num_new + floating_letter);
            temp_pot->points = get_points_vertical(temp_pot,board);
            add_pot_word(temp_pot,words);
            total_words++;
        }
        curr = curr->next;
    }
    delete_set(temp);
    delete_pot_word_ll(words_vertical);
    return total_words;
}
int traverse_board(board_t* board, char** array, letter_set_t* set, pot_word_ll* words,FILE* file,int num_words, int* letter_indexes){
   int tot = 0;
   letter_t* curr;
   for(int y = 0; y < size; y++){
      for(int x = 0; x < size; x++){
        printf("%d\n", size * y + x + 1);
        fflush(stdout);
         if(board->spaces[y][x]->filled){
           // printf("loop\n");
            if(!board->spaces[y][x]->checked_h){
                tot += words_at_spot_horizontal(y,x,board,set,words,array,file,num_words,letter_indexes,0);
                mark_as_checked(x,y, board, HORIZONTAL);
            }
            if(!board->spaces[y][x]->checked_v){
                tot += words_at_spot_vertical(y,x,board,set,words,array,file,num_words,letter_indexes,0);
                mark_as_checked(x,y, board, VERTICAL);
            }
         }
         else{
            if((x + 1 != 15 && board->spaces[y][x+1]->filled) || ( x - 1 != -1 && board->spaces[y][x - 1]->filled)){
                curr = set->head;
                while(curr != NULL){
                    curr->pos = 0;
                    tot += words_at_spot_vertical(y,x,board,set,words,array,file,num_words,letter_indexes,1);
                    curr->pos = 20;
                    curr = curr->next;
                }
            }
            if((y + 1 != 15 && board->spaces[y+1][x]->filled) || ( y - 1 != -1 && board->spaces[y-1][x]->filled)){
                curr = set->head;
                while(curr != NULL){
                    curr->pos = 0;
                    tot += words_at_spot_horizontal(y,x,board,set,words,array,file,num_words,letter_indexes,1);
                    curr->pos = 20;
                    curr = curr->next;
                }
            }
         }
      }
   }
   return tot;
}
