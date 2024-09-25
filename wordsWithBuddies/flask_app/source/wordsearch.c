#include "wordsearch.h"

letter_set_t* letters_horizontal(int y,int x,board_t* board,letter_set_t* set){
    if(board->spaces[y][x]->filled) add_letter(set, board->spaces[y][x]->letter,0);
    //look left
    int let_left = 8;
    int new_x = x;
    while(let_left){
        new_x--;
        if(new_x < 0){
            break;
        }
        if(!board->spaces[y][new_x]->filled){
            let_left--;
        } else{
            add_letter(set,board->spaces[y][new_x]->letter,new_x-x);
        }
    }
    let_left = 8;
    new_x = x;
    while(let_left){
        new_x++;
        if(new_x > 14){
            break;
        }
        if(!board->spaces[y][new_x]->filled){
            let_left--;
        } else{
            add_letter(set,board->spaces[y][new_x]->letter,new_x-x);
        }
    }
    return set;
}

letter_set_t* letters_vertical(int y,int x,board_t* board,letter_set_t* set){
    
    if(board->spaces[y][x]->filled) add_letter(set, board->spaces[y][x]->letter,0);
    //look left
    int let_left = 7;
    int new_y = y;
    while(let_left){
        new_y--;
        if(new_y < 0){
            break;
        }
        if(!board->spaces[new_y][x]->filled){
            let_left--;
        } else{
            add_letter(set,board->spaces[new_y][x]->letter,new_y-y);
        }
    }
    let_left = 7;
    new_y = y;
    while(let_left){ 
        new_y++;
        if(new_y > 14){
            break;
        }
        if(!board->spaces[new_y][x]->filled){
            let_left--;
        } else{
            add_letter(set,board->spaces[new_y][x]->letter,new_y-y);
        }
    }
    return set;
}
int check_boundaries_horizontal(int y,int x,board_t* board,char* word,char** array,int num_words){  
    int len = strlen(word);
//    char* line = malloc(sizeof(char) * (size+2));
    //first do horizontal
   // printf("here\n");
    if(x < 0 || x + len - 1 > 14 || (x != 0 && board->spaces[y][x-1]->filled) || (x+len - 1 != 14 && board->spaces[y][x+len]->filled)){
        return 0;
    }
    char new[16];
   // printf("or here\n");
    //printf("word: %s x: %d y: %d\n",word,x,y);
    for(int i = 0; i < len; i++){
        //look up
        int ind_up = 1;
        int ind_down = 1;
        while(y - ind_up >= 0 && board->spaces[y - ind_up][x+i]->filled){
            ind_up++;
        }
    //    printf("between\n");
        while(y + ind_down <= 14 && board->spaces[y + ind_down][x+i]->filled){
            ind_down++;
        }
        ind_up--;
        ind_down--;
    ///        printf("maybe here\n");
        for(int d = 0; d < ind_up + ind_down + 1; d++){
            new[d] = board->spaces[y-ind_up+d][x+i]->letter;
            if(d == ind_up){
                new[d] = word[i];
            }
        }

        new[ind_down + ind_up+1] = '\0';
        if(ind_up+ind_down > 0){
           // printf("top %d, down %d\n",ind_up,ind_down);
            if(find_word(array,new,num_words) == 0){
               /// printf("didnt: %s!\n",new);
                return 0;
            }
        }
        //    printf("lastly\n");
    }
   // printf("made it: %s\n",word);
    return 1;
}

int check_boundaries_vertical(int y,int x,board_t* board,char* word,char** array,int num_words){  
    int len = strlen(word);
    //char* line = malloc(sizeof(char) * (size+2));
    //first do horizontal
    if(y < 0 || y + len - 1 > 14 || (y != 0 && board->spaces[y - 1][x]->filled) || (y+len -1 != 14 && board->spaces[y+len][x]->filled)){
               //printf("top     pos: %d,%d, word: %s\n",x,y,word);
        return 0;
    }
    char new[25];

   // printf("word: %s x: %d y: %d\n",word,x,y);
    for(int i = 0; i < len; i++){
        //look up
        int ind_up = 1;
        int ind_down = 1;
        while(x - ind_up >= 0 && board->spaces[y +i][x - ind_up]->filled){
            ind_up++;
        }
        while(x + ind_down <= 14 && board->spaces[y + i][x+ind_down]->filled){
            ind_down++;
        }
        ind_up--;
        ind_down--;
        for(int d = 0; d < ind_up + ind_down + 1; d++){
            new[d] = board->spaces[y+i][x-ind_up+d]->letter;
            if(d == ind_up){
                new[d] = word[i];
            }
        }


        new[ind_down + ind_up+1] = '\0';
       // printf("pos: %d,%d, word: %s new: %s\n",x,y,word,new);
        if(ind_up+ind_down > 0){
           // printf("top %d, down %d\n",ind_up,ind_down);
            if(find_word(array,new,num_words) == 0){ ////SOMETHING HERE MAYBE
              //  printf("didnt: %s\n",new);
                return 0;
            }
        }
    }
    //printf("made it: %s\n",word);
    return 1;
}

int get_points_horizontal(pot_word* pot,board_t* board){
    int total_points = 0;
    int let_points;
    int num_tw = 0;
    int num_dw = 0;
    int len = (int) strlen(pot->word);
    //horizontal
   /// printf("word: %s, pos %d,%d\n",pot->word,pot->x,pot->y);
    for(int i = 0; i < len; i++){
        let_points = letter_points(pot->word[i]);
        if(board->spaces[pot->y][pot->x + i]->power == DW){
            num_dw++;
        }
        if(board->spaces[pot->y][pot->x + i]->power == TW){
            num_tw++;
        }
        if(board->spaces[pot->y][pot->x + i]->power == DL){
            let_points*=2;
        }
        if(board->spaces[pot->y][pot->x + i]->power == TL){
            let_points*=3;
        }
        total_points+=let_points;
    }
    if(num_tw > 0){
        total_points = total_points * (num_tw * 3);
    }
    if(num_dw > 0){
        total_points = total_points * (num_dw*2);
    }
    int offset = 1;
    int sec_word_f = 0;
    for(int i = 0; i < len; i++){
        sec_word_f = 0;
        offset = 1;
         //   printf("check\n");
        if(!board->spaces[pot->y][pot->x + i]->filled){
            while(pot->y+offset != 15 && board->spaces[pot->y+offset][pot->x + i]->filled){
                total_points+=letter_points(board->spaces[pot->y+offset][pot->x + i]->letter);
                offset++;
                sec_word_f = 1;
            }
          //  printf("here\n");
            offset = 1;
            while(pot->y-offset != -1 && board->spaces[pot->y-offset][pot->x + i]->filled){
                total_points+=letter_points(board->spaces[pot->y-offset][pot->x + i]->letter);
                offset++;
                sec_word_f = 1;
            }
                   //     printf("here\n");
            if(sec_word_f){
                let_points = letter_points(pot->word[i]);
                if(board->spaces[pot->y][pot->x+i]->power == DL){
                    let_points*=2;
                }
                if(board->spaces[pot->y][pot->x+i]->power == TL){
                     let_points*=3;
                }
                total_points += let_points;
            }
                     ///   printf("here\n");
        }
    }
    //printf("total: %d\n",total_points);
        if(pot->num_new == 7){
        total_points+=35;
    }
    return total_points;

}
int get_points_vertical(pot_word* pot,board_t* board){
    int total_points = 0;
    int let_points;
    int num_tw = 0;
    int num_dw = 0;
    int len = (int) strlen(pot->word);
    //horizontal
    for(int i = 0; i < len; i++){
        let_points = letter_points(pot->word[i]);
        if(board->spaces[pot->y+i][pot->x]->power == DW){
            num_dw++;
        }
        if(board->spaces[pot->y+i][pot->x]->power == TW){
            num_tw++;
        }
        if(board->spaces[pot->y+i][pot->x]->power == DL){
            let_points*=2;
        }
        if(board->spaces[pot->y+i][pot->x]->power == TL){
            let_points*=3;
        }
     //   printf("let %d\n",let_points);
        total_points+=let_points;
    }
    if(num_tw > 0){
        total_points = total_points * (num_tw * 3);
    }
    if(num_dw > 0){
        total_points = total_points * (num_dw*2);
    }
    int offset = 1;
    int temp = total_points;
    int sec_word_f = 0;
   // printf("pot word: %s\n",pot->word);
    for(int i = 0; i < len; i++){
            //    printf("i: %d\n",i);
        sec_word_f = 0;
        offset = 1;
        if(!board->spaces[pot->y+i][pot->x]->filled){
           // printf("f\n");
            while(pot->x + offset != 15 && board->spaces[pot->y+i][pot->x + offset]->filled){
             //   printf("1\n");
                total_points+=letter_points(board->spaces[pot->y+i][pot->x + offset]->letter);
                offset++;
                sec_word_f = 1;
            }

            offset = 1;
            while(pot->x - offset != -1 && board->spaces[pot->y+i][pot->x -offset]->filled){
                       /// printf("2\n");
                total_points+=letter_points(board->spaces[pot->y+i][pot->x - offset]->letter);
                offset++;
                sec_word_f = 1;
            }
            if(sec_word_f){
                let_points = letter_points(pot->word[i]);
                if(board->spaces[pot->y+i][pot->x]->power == DL){
                    let_points*=2;
                }
                if(board->spaces[pot->y+i][pot->x]->power == TL){
                     let_points*=3;
                }
                total_points += let_points;
            }
        }
    }
    if(pot->num_new == 7){
        total_points+=35;
    }
   // if(temp != total_points) printf("temp %d tot %d\n",temp,total_points);
    return total_points;

}

int starting_word(board_t* board,letter_set_t* set, char** array,int* letter_indexes, pot_word_ll* words){
    pot_word_ll* words_horizontal = new_pot_word_ll();
    board->spaces[7][7]->filled = 1;
    board->spaces[7][7]->letter = '?';
    //print_set(temp);
    pot_word* temp_pot;
    int total_words = 0;
    words_with_letters(set, words_horizontal,array,letter_indexes);
    ///print_potwords(words_horizontal,120);
    pot_word* curr = words_horizontal->head;
    while(curr != NULL){
            temp_pot = new_potword(10,7-curr->x,7,0,curr->word,curr->num_new + 1);
            temp_pot->points = get_points_horizontal(temp_pot,board);
            add_pot_word(temp_pot,words);
            total_words++;
            curr = curr->next;
    }
    return total_words;
}
