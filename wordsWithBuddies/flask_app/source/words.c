#include "wrappers.h"
//Ideas:
//most new letters, most words, most powerups, word score/sum of letters
//sum of letters should be sum of new letters
//keep track of letters in potword adt

int main( int argc, char *argv[] )  {

   if( argc < 3){
      printf("Usage './words <file_name> <letters>'\n");
      return 1;
   }
   ///open files
   char boardpath[50];
   snprintf(boardpath,50,"boards/%s",argv[1]);
   FILE* file = fopen(boardpath,"r");
   FILE* words_f = fopen("wordlist.txt","r");


   //fill array with words from file
   int* index_array = calloc(27,sizeof(int));
   int num_words = letter_indexes(words_f,index_array);
   char** array = calloc(num_words,sizeof(char*));
   for(int i = 0; i < num_words; i++){
      array[i] = malloc(sizeof(char) * size + 2);
   }
   file_to_array(words_f,array);


   //create the board   
   board_t* board = new_board();
   read_to_board(board,file);
   //print_board(board);


   //create letter set from users letters
   letter_set_t* set = new_letter_set();
   parse_string(set,argv[2],1);

   
   //create linked list to hold words
   pot_word_ll* words = new_pot_word_ll();


   //test if board is blank, if it is need to create a starting word
   int tot = 0;
    if(board->num_letters == 0){
      set->head->pos = 0;
      tot = starting_word(board,set,array,index_array,words);
      //printf("Blank Board!\n");
    } else{
      tot = traverse_board(board,array,set,words,words_f,num_words,index_array);
    }


   printf("total %d\n",tot);
   if(words->head == NULL){
      printf("couldnt find any words\n");
   } else {
      //printf("what\n");
      pot_word* curr = longest_potword(words);
      //printf("longest word: Word: %s Points: %d Pos: %d,%d in the %d direction\n",curr->word,curr->points,curr->x, curr->y,curr->dir);
      printf("%s %d %d %d %d %d\n",curr->word,curr->points,curr->x, curr->y,curr->dir,curr->num_new);
      print_potwords(words,10);
   //   printf("Which word should be added? Type 0 for none\n");
      int wordind = 1;
   //   scanf("%d",&wordind);
     // add_word(board,words,wordind);
    //  print_board(board);
     // fclose(file);
    //  file = fopen(boardpath,"w");
   //   board_to_file(board,file);
   }



   //free and null
   //fclose(file);
   fclose(words_f);
   delete_set(set);
   delete_pot_word_ll(words);
   delete_board(board);
   for(int i = 0; i < num_words; i++){
      free(array[i]);
   }
   free(array);
   set = NULL;
   words = NULL;
   board = NULL;
   array = NULL;
   return 0;
}

