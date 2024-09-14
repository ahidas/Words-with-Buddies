#include "wordlist.h"
#include <string.h>
#include <stdlib.h>
#define size 15


int char_in_letters(letter_t* head,char c){
    if(head == NULL){
        printf("head was NULL\n");
        return -1;
    }
    letter_t* curr = head;
    while(curr != NULL){
        if(curr->letter == c){
            if(!curr->used){
                curr->used = 1;
                return 1;
            }
        }
            curr = curr->next; 
    }
    return -1;
}
int num_wilds(letter_set_t* letters){
    letter_t* let = letters->head;
    int wilds = 0;
    while(let != NULL){
        if (let->letter == '?'){
            wilds++;
        }
        let = let->next;
    }
    return wilds;
}
int words_with_letters(letter_set_t* letters, pot_word_ll* ll, char** array, int* letter_indexes){
    int letter_index;
    int off;
    letter_set_t* word_set = NULL;
    char* word = malloc(sizeof(char) * (size+2));
    int ind;
    char letter;
    int end;
    letter_t* curr = letters->head;
    int wilds = num_wilds(letters);
    int wild_hold = wilds;
    int num_new = 0;
    while(curr != NULL){
        letter = curr->letter;
        if(wilds > 0){
          //  printf("wilds!\n");
            ind = 0;
            end = letter_indexes[26];
            curr = NULL;
        } else {
        ind = letter_indexes[letter - 97];
        end = letter_indexes[letter - 96];
        curr = curr->next;
        }
        while(ind < end){
            letter_index = 0;
            wilds = wild_hold;
            while(array[ind][letter_index] != '\0'){
                if(char_in_letters(letters->head, array[ind][letter_index]) == -1){
                    wilds--;
                    if(wilds < 0){
                        break;
                    }
                }
                letter_index++;
            }
            word_set = new_letter_set();
            set_used(letters);
            if(array[ind][letter_index] == '\0'){
                parse_string(word_set,array[ind],0);
                if((off = set_compare(word_set,letters,wild_hold,&num_new)) != 20){
                   // printf("word: %s\n",array[ind]);
                    add_pot_word(new_potword(10,off,off,0,array[ind],num_new),ll);
                }
            }
            delete_set(word_set);
            ind++;
        }
        }
        return ind;
    }
    

/*int words_with_letters(letter_set_t* letters, pot_word_ll* ll, FILE* file){
    int letter_index;
    int off;
    letter_set_t* word_set = NULL;
    char* word = malloc(sizeof(char) * (size+2));
    int ind = 0;
    rewind(file);
    while(fgets(word,size+2,file)){
         word[strcspn(word, "\n")] = '\0';
       // printf("word in loop %s\n",word);
        letter_index = 0;
        while(word[letter_index] != '\0'){
            //printf("letter: %c\n",word[letter_index]);
            if(char_in_letters(letters->head, word[letter_index]) == -1){
                break;
            }
            ////printf("in letters\n");
            letter_index++;
        }
        word_set = new_letter_set();
        set_used(letters);
        if(word[letter_index] == '\0'){
            parse_string(word_set,word,0);
           // printf("parsed: %s\n",word);
            //print_set(word_set);
            if((off = set_compare(word_set,letters)) != 20){
                //printf("wordked!\n");
               // printf("%s\n",word);
                add_pot_word(new_potword(10,off,off,0,word),ll);
                ind++;
                //printf("check\n");
            }
        }
        delete_set(word_set);
    }
    free(word);
    return ind;

}
*/
