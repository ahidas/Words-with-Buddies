#include "potwords.h"

pot_word* new_potword(int points,int x, int y, int dir, char* word,int num_new){
    pot_word* new = malloc(sizeof(pot_word));
    new->points = points;
    new->x = x;
    new->y = y;
    new->dir = dir;
    new->word = malloc(size);
    new->next = NULL;
    new->num_new = num_new;
    strcpy(new->word,word);
    //printf("word in new: %s\n",word);
    return new;
}

pot_word_ll* new_pot_word_ll(){
    pot_word_ll* new = malloc(sizeof(pot_word_ll));
    new->head = NULL;
    return new;
}
void delete_pot_word(pot_word* pot){
    free(pot->word);
    free(pot);
}

void delete_pot_word_ll(pot_word_ll* ll){
    pot_word* curr = ll->head;
    pot_word* temp = NULL;
    while(curr != NULL){
        temp = curr->next;
        delete_pot_word(curr);
        curr = temp;
    }
    free(ll);
}

pot_word* add_pot_word(pot_word* pot,pot_word_ll* ll){
    if(ll->head == NULL){
        ll->head = pot;
        return pot;
    }
    if(pot->points > ll->head->points){
        pot->next = ll->head;
        ll->head = pot;
        return pot;
    }

    pot_word* curr = ll->head;
    while(curr->next != NULL){
        if(pot->points > curr->next->points){
            pot->next = curr->next;
            curr->next = pot;
            return pot;
        }
        curr = curr->next;
    }
    curr->next = pot;
    return pot;
}

void print_potwords(pot_word_ll* ll,int top){
    pot_word* curr = ll->head;
    int i = 0;
    char* word;
    //printf("\nPrinting top %d potential words\n\n",top);
    while(curr != NULL && i < top){
        if(curr->dir == 0){
            word = "horizontal";
        } else {
            word = "vertical";
        }
        printf("%s %d %d %d %s %d\n",curr->word,curr->points,curr->x, curr->y,word,curr->num_new);
        curr = curr->next;
        i++;
    }
}
pot_word* longest_potword(pot_word_ll* ll){
    int len = 0;
    pot_word* curr = ll->head;
    pot_word* longest = NULL;
    while(curr != NULL){
        if((int)strlen(curr->word) > len){
            longest = curr;
            len = strlen(curr->word);
        }
        curr = curr->next;
    }
    return longest;
}
