#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <string.h>
#include "board.h"
#define size 15


space_t* new_space(int power){
    space_t* new = malloc(sizeof(space_t));
    if(new == NULL){
        err(errno,"Failed to malloc space\n");
        return NULL;
    }
    new->filled = 0;
    new->letter = '0';
    new->power = power;
    new->checked_h = 0;
    new->checked_v = 0;
    return new;
}
int get_power(int y,int x){
    //tripple letter
    if(((y == 0 || y == 14) && (x == 6 || x == 8)) || ((y == 3 || y == 11) && (x == 3  || x == 11)) || ((y==5 || y == 9) && (x == 5 || x == 9)) || ((y == 6 || y == 8) && (x == 0 || x == 14))){
        return TL;
    }
    //tripple word
    if(((y == 0 || y == 14) && (x == 3 || x == 11)) || ((y == 3 || y == 11) && (x == 0  || x == 14))){
        return TW;
    }
    //Double Letter
    if(((y == 1 || y == 13) && (x == 2 || x == 12)) || ((y == 2 || y == 12) && (x == 1  || x == 4 || x == 13 || x == 10)) || ((y==4 || y == 10) && (x == 2 || x == 6 || x == 12 || x == 8)) || ((y == 6 || y == 8) && (x == 4 || x == 10))){
        return DL;
    }
    ///double word
    if(((y == 1 || y == 13) && (x == 5 || x == 9)) || ((y == 3 || y == 11) && (x == 7)) || ((y==5 || y == 9) && (x == 1 || x == 13)) || ((y == 7) && (x == 3 || x == 11))){
        return DW;
    }
    return NONE;
}

board_t* new_board(){
    board_t* new = malloc(sizeof(board_t));
    if(new == NULL){
        err(errno,"Failed to malloc board_t\n");
        return NULL;
    }
    new->num_letters = 0;

    new->spaces = (space_t***) calloc(size,sizeof(space_t**));
    if(new->spaces == NULL){
        err(errno, "Failed to calloc board array");
        return NULL;
    }

    for(int i = 0; i < size; i++){
        new->spaces[i] = (space_t**) calloc(size,sizeof(space_t*));
        if(new->spaces[i] == NULL){
            err(errno, "Failed to calloc board array");
            return NULL;
        }
        for(int d = 0; d < size; d++){
        new->spaces[i][d] = new_space(get_power(i,d));
///        if(i == 7 && d == 7){
 //           new->spaces[i][d]->filled = 1;
//        }
        }
    }
    return new;
}



board_t* read_to_board(board_t* board, FILE* file){
    char* line = malloc(sizeof(char)*(size+2));
    int row = 0;
    while(fgets(line,size+2,file) != NULL){
        if(strcmp(line,"0\n") != 0){
            for(int i = 0; i < size; i++){
                if(line[i] != '0'){
                    board->spaces[row][i]->letter = line[i];
                    board->spaces[row][i]->filled = 1;
                    board->spaces[row][i]->power = NONE;
                    board->num_letters++;
                }
            }
        }
        row++;
    }
    free(line);
    return board;
}

void add_word(board_t* board, pot_word_ll* pot_ll,int num){
    //if word is vertical, dir = 1;
    
    //horizontal, dir = 0
    if(num == 0){
        return;
    }
    pot_word* pot = pot_ll->head;
    int i = 1;
    //printf("checkl\n");
    while(pot != NULL && i < num){
        pot = pot->next;
        i++;
    }
    printf("Adding %s to board!\n",pot->word);
    if(pot->dir){
        for(int i = 0; i < (int) strlen(pot->word);i++){
            board->spaces[pot->y + i][pot->x]->letter = pot->word[i]; 
            board->spaces[pot->y+i][pot->x]->filled = 1; 
            board->spaces[pot->y+i][pot->x]->power = NONE;
        }
        return;
    }
    for(int i = 0; i < (int) strlen(pot->word);i++){
        board->spaces[pot->y][pot->x + i]->letter = pot->word[i]; 
        board->spaces[pot->y][pot->x + i]->filled = 1; 
        board->spaces[pot->y][pot->x+i]->power = NONE;
    }
}
void print_board(board_t* board){
    for(int i = 0; i < size; i++){
        for(int p = 0; p < size*4; p++){
            printf("-");
        }
        printf("\n");
        for(int d = 0; d < size; d++){
            if(board->spaces[i][d]->filled){
            printf("|%c| ",board->spaces[i][d]->letter);
            }else{
                if(board->spaces[i][d]->power == NONE){
                    printf("|_| ");
                } else {
                    printf("|%d| ",board->spaces[i][d]->power);
                }
            }
        }
        printf("\n");
    }
}

void delete_board(board_t* board){
    for(int i = 0; i < size; i++){
        for(int d = 0; d < size; d++){
            free(board->spaces[i][d]);
        }
        free(board->spaces[i]);        
    }
    free(board->spaces);
    free(board);
}

void mark_as_checked(int x, int y, board_t* board, int dir){
    int i = 0;
    if(dir == HORIZONTAL){
        while(x+i != 15 && board->spaces[y][x+i]->filled){
            board->spaces[y][x+i]->checked_h = 1;
            i++;
        }
        return;
    } 
    while(y+i != 15 && board->spaces[y+i][x]->filled){
        board->spaces[y+i][x]->checked_v = 1;
        i++;
    }
}

void board_to_file(board_t* board, FILE* file){
   for(int y = 0; y < size; y++){
      for(int x = 0; x < size; x++){
            fprintf(file,"%c",board->spaces[y][x]->letter);
      }
      fprintf(file,"\n");
   }
}

