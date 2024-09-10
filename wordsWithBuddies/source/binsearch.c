#include "binsearch.h"
#include <stdlib.h>
#include <string.h>
#define size 15
int letter_indexes(FILE* file, int* array){
    int tot_words = 0;
    int i = 0;
    char curr = ' ';
    char* word = malloc(sizeof(char) * (size+2));
    while(fgets(word,size+2,file)){
        if(word[0] != curr){
            array[i] = tot_words + 1;
            curr = word[0];
            i++;
        }
        tot_words++;
    }
    array[i] = tot_words;
    //free(word);
    return tot_words;
}
int file_to_array(FILE* file,char** array){
    int tot_words = 0;
    char* word = malloc(sizeof(char) * (size+2));
    tot_words = 0;
    rewind(file);
    while(fgets(word,size+2,file)){
        word[strcspn(word, "\n")] = '\0';
        strcpy(array[tot_words],word);
        tot_words++;
    }
    free(word);
    return tot_words;
}

int find_word(char** array,char* word,int num){
    int left = 0;
    int middle;
    int right = num - 1;
    while(left <= right){
        middle = left + (right - left)/2;
        //printf("middle: %d\n",middle);
        if(strcmp(array[middle],word) == 0){
            return 1;
        }
        if(strcmp(array[middle],word) < 0){
            left = middle + 1;
            continue;
        }
        if(strcmp(array[middle],word) > 0){
            right = middle - 1;
        }
    }
    return 0;
}
