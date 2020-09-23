#include <stdio.h>
#include "tokenizer.h"
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#include <string.h>
#include "history.h"

int str_len(char *inStr); // Proto-type of the function str_len


int main(){ // Main function 

  char vector[1000]; // Vector saves the user input 
  
  printf("> "); // simple indicator in the console
  
  fgets( vector, sizeof(vector), stdin); // fgets takes user input and place it inside vector according to its size


  char **vector2=tokenize(vector); // **vector2 is the tokenizer  

  print_tokens(vector2); // print the words that are inside tokenizer
  free_tokens(vector2); // release memory from tokenizer


  List *linkedList = init_history(); // creates linkedList

  add_history(linkedList, vector); // add a word to the linkedList
  print_history(linkedList); // prints all words from linkedList
  free_history(linkedList); // release all words and the whole linkedList itself


  
  return 0;

}


List *init_history(){

  //reserves memory from linkedList and the first element in the linkedList 

  List *linkedList = malloc(sizeof(List));

  Item *next = malloc(sizeof(Item));

  linkedList -> root = next;

  return linkedList;
  
}
void add_history(List *list, char *str){

  int len = str_len(str);

  // Check if root (head) is empty and adding the element in sequence
    
  if(list -> root -> next == NULL ){

    list -> root -> id = 1;

    list -> root -> str = copy_str(str,len);

    list -> root -> next = malloc(sizeof(Item));

    
  }else{

    
    Item *nextItem = list -> root -> next;
    Item *toChange; 
    int id = list -> root -> id;
    
    while(nextItem != NULL){ // we move until find the last empty element in the linkedList
      toChange = nextItem;
      nextItem = nextItem -> next; 

      id++;
    }

    // Here we add an item to the last element of linkedList 

    toChange -> id = id;

    toChange -> str = copy_str(str,len);

    toChange -> next = malloc(sizeof(Item));



  }

}
void print_history(List *list){

  Item *next = list -> root;

  // Print all elements inside linkedList
  
  while(next -> next != NULL){ 
  printf("ID: %i\n", next -> id);
  printf("Str: %s\n", next -> str);

    next = next -> next;
    
  }


}
char *get_history(List *list, int id){

Item *next = list -> root;


// We move until find teh same id that the user is asking for, and if its not there returns a "Not found" message
 
  while(next -> next != NULL){ 
    if(next -> id == id){


      return next -> str; 

    }

    next = next -> next;
    
  }

  return "Not Found";

}
void free_history(List *list){
  Item *next = list -> root -> next;
  Item *toDelete;

  // We move through element releasing the string, item, and finally the linkedList
  
  while(next != NULL){

    toDelete = next;
    next = next -> next;

    free(toDelete -> str);
    free(toDelete);


  }
  free(list -> root);
  free(list);

}

int space_char(char c){


  // return true if c is white space or a tab
  
  if( c == ' ' || c == '\t' ){
    return TRUE;
  }
  return FALSE;

}

int non_space_char(char c){

  // return true if c is not white space or tab
  
  if(c != ' ' &&  c != '\t'){
    return TRUE;

  }
  return FALSE;


}
int count_words(char *str){
  char *savechar;
  int counter = 0, state = 0;

  //Count all introducing words by the user
  
  for(savechar = str; *savechar !='\0'; savechar++){

    if(space_char(*savechar)){

      state = 0;
    }
    else if(state == 0){
      state = 1;
      counter++;
    }
  }

  return counter;
}

// Copy the string that the user input in a new memory address

char *copy_str(char *inStr, short len){

  int sIndex = 0;

  char *scopy = malloc((len + 1) * sizeof(char)), c;

  do{

    c = *(scopy + sIndex) = *(inStr + sIndex);
    sIndex++;

  }while(c);

  return scopy;
}

// returns the size of the word

int str_len(char *inStr){

  int i;

  for (i = 0; inStr[i] !='\0' ;i++);

  return i-1;

}

//returns the memory address of the first character word passed
char word_start(char *str){

  char *savechar;
  
  if(str_len(str) == 0)

    return FALSE; 

  for(savechar = str; *savechar !='\0'; savechar++){

    if(non_space_char(*savechar) == 1){
      return *savechar;

    }
  
  }
   return FALSE;
}

//returns the memory address of the last character word passed
char *word_terminator(char *word){

 char *savechar;
 char *end;
 int len = str_len(word);
 if(str_len(word) == 0)

   return FALSE;
 for(savechar = word; *savechar != '\0';  savechar++){
  if(non_space_char(*savechar) == 1 && *savechar != '\n'){
      end = savechar;

 }

 }
 return end;
}

char **tokenize(char *str){

  int totalWords = count_words(str);
  int counter = 0;
  int counter2 = 0;
  
  char *savechar;
  int len = str_len(str);
  char **vector = malloc((len + 1) * sizeof(char));// reserves memory for tokenizer

  char vector2[1000]; // used to store each word introduced
  
  // separates each introduced word and store it in vector

  for(savechar = str; *savechar !='\0'; savechar++){ 
    
    if(non_space_char(*savechar) == 1 && word_terminator(str) != savechar){

      vector2[counter2++] = *savechar;
    

    }else if(space_char(*savechar) == 1 || word_terminator(str) == savechar){

      if(word_terminator(str) == savechar){
	vector2[counter2++] = *savechar;
      }

      int len = str_len(vector2);
      char *scopy = copy_str(vector2,len);

      

      vector[counter++] = scopy;
      counter2 = 0;
      memset(vector2,0,sizeof(vector2));// here we empty vector2, because if its not erase its going to be overwriting
    }

   
  }

   return vector;

}
//print all elements from tokenizer
void print_tokens(char **tokens){

  char **savechar;
  
  for(savechar = &tokens[0]; *savechar; savechar++)
   printf("%s\n", *savechar);                      

}

//release all elements from tokenizer
void free_tokens(char **tokens){

  free(tokens);


}
