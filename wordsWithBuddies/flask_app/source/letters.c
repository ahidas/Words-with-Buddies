#include "letters.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define size 15
letter_t* new_letter(char c, int pos){
    letter_t* new = malloc(sizeof(letter_t));
    new->letter = c;
    new->pos = pos;
    new->used = 0;
    new->next = NULL;
    return new;
}

letter_set_t* new_letter_set(void){
    letter_set_t* new = malloc(sizeof(letter_set_t));
    new->head = NULL;
    new->num = 0;
    return new;
}

letter_set_t* add_letter(letter_set_t* set, char c,int pos){
    letter_t* new = new_letter(c,pos);
    if(set->head == NULL){
        set->head = new;
        return set;
    }
    letter_t* curr = set->head;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = new;
    return set;
}

void delete_letter(letter_t* let){
    free(let);
}

letter_set_t* copy_set(letter_set_t* source){
    letter_t* curr = source->head;
    letter_set_t* new = new_letter_set();
    while(curr != NULL){
        add_letter(new,curr->letter,curr->pos);
        curr = curr->next;
    }
    return new;
}

int parse_string(letter_set_t* set, char* arg, int flag){
    int len = strlen(arg);
    if (!flag){
        for(int i = 0; i < len; i++){
            add_letter(set, arg[i], i);
        }
        return 1;
    }
    for(int i = 0; i < len; i++){
        add_letter(set, arg[i], 20);
    }
    return 1;
}
void set_used(letter_set_t* set){
    letter_t* curr = set->head;
    while(curr != NULL){
        curr->used = 0;
        curr = curr->next;
    }
}
int set_compare(letter_set_t* word,letter_set_t* letters, int num_wilds, int* num_new){
    letter_t* curr = letters->head;
    letter_t* other_curr;
    int new_word_f = 0;
    int floating_letter_check = 0; //if all the letters are the users and none from the board this will become one
    char starting = '0'; // this is the letter that has position zero in the available letters set
    while(curr != NULL && starting == '0'){
        if(curr->pos == 0){
            starting = curr->letter;
        }
        if(curr->pos == -1){
            floating_letter_check = 1;
            curr->pos = 0;
            starting = curr->letter;
        }
        curr = curr->next;
    }

    int a_index = 0;
    int pos_array[15];
    int safe = 0;
    int flag = 1;
    while(1){
       // printf("up at the top\n");
        curr = word->head;    //curr is a letter from the word we are checking
        while(curr != NULL){
            if(curr->letter == starting){   //if the letter is equal to the one in the main position
                if(a_index == 0 || pos_array[a_index - 1] < curr->pos){  //if this is the first letter checked, or if were on a duplicate of the starting letter later in the word. 
                    pos_array[a_index] = curr->pos;
                    flag = 0;
                } else{
                    flag = 1;
                }
            }
            curr = curr->next;
        }
        if(flag){
            return 20;
        }
        curr = word->head;
     //   printf("curr: %c\n",curr->letter);
     int rel_pos;
     int break_flag;
     int wilds = num_wilds;
        while(curr != NULL){

            rel_pos = curr->pos - pos_array[a_index];
            other_curr = letters->head;
            break_flag = 0;
            while(other_curr != NULL){
                if(other_curr->letter == curr->letter){
                   // printf("comparing pos of letter %c, used: %d, letter pos: %d\n",curr->letter, other_curr->used, other_curr->pos);
                   if(break_flag){
                        if(rel_pos == other_curr->pos){
                            new_word_f--;
                        }
                                other_curr = other_curr->next;
                    continue;
                   }else if(other_curr->used == 0 && (other_curr->pos == 20 || rel_pos == other_curr->pos)){ //if the letter has already been used, or its relative position is same as in the word
                        safe = 1;
                        if(other_curr->pos == 20){
                            new_word_f++;
                        }
                        other_curr->used = 1; //set that letter as used 
                        break_flag = 1; //can move to next letter in the word, will go through remaining letters to make sure no position conflicts
                    }else {
                        safe = 0;
                    }
                } else {
                    if(rel_pos == other_curr->pos){ //if the letters are not the same, but have same position, word wont work
                        return 20;
                    }
                }
            other_curr = other_curr->next;
            }
                if(!safe){
                    wilds--;
                    if(wilds < 0){
                        break;
                    }
                }
            curr = curr->next;
        }
                set_used(letters);
        if(curr == NULL && new_word_f){
           /// printf("num_wilds: %d wilds: %d\n",num_wilds,wilds);
            *num_new = new_word_f + (num_wilds - wilds) + floating_letter_check;
            return pos_array[a_index];
        }
        new_word_f = 0;
        a_index++;
    }

}
void print_set(letter_set_t* set){
    letter_t* curr = set->head;
    printf("Printing Set!\n");
    while(curr != NULL){
        printf("%c %d\n", curr->letter, curr->pos);
        curr = curr->next;
    }
}

void delete_set(letter_set_t* set){
    letter_t* curr = set->head;
    letter_t* temp;
    while(curr != NULL){
        temp = curr->next;
        curr->next = NULL;
        delete_letter(curr);
        curr = temp;
    }
    set->head = NULL;
    free(set);
}

int letter_points(char let){
    if(let == 'a' || let == 'e' || let == 'i' || let == 'o' || let == 'r' || let == 's' || let == 't'){
        return 1;
    }
    if(let == 'd' || let == 'l' || let == 'n'|| let == 'u'){
        return 2;
    }
    if(let == 'g' || let == 'h' || let == 'y'){
        return 3;
    }
    if(let == 'b' || let == 'c' || let == 'm' || let == 'f' || let == 'p' || let == 'w'){
        return 4;
    }
    if(let == 'k' || let == 'v'){
        return 5;
    }
    if(let == 'x'){
        return 8;
    }
    if(let == 'j' || let == 'q' || let == 'z'){
        return 10;
    }
    return 0;
}
