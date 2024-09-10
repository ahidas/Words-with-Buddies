#include <stdio.h>
#include "letters.h"
#include "potwords.h"
/*
typedef struct node{
    char* string;
    node_t* left;
    node_t* right;
}node_t;

typedef struct tree{
    node_t* head;
}tree_t;

node_t* new_node(char*);

tree_t* new_tree();

tree_t* tree_add(tree_t*);

int tree_find(tree_t*,char*);

void tree_print(tree_t*);
*/
int words_with_letters(letter_set_t*, pot_word_ll*,char**,int*);

