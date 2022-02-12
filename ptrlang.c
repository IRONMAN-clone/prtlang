#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  //Tokens - Start
  const char* TOK_WRITE = "Write"; 
  const char* STR_LIT = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char LFT_RND = '('; 
  char RGT_RND = ')';  
  const char* TOK_INT = "PUSH";
  const char* TOK_W_T = "top_wr";
  //Tokens - End 

  //TOK C 
  int token_count = -1;
  int TOK_INT_STACK[350];

  FILE *l;
  l = fopen("main.prtlang","r"); 

  int cx_counter = 0;

  char *newtoken = NULL;

  int c = getc(l);
  char *storage = (char*)malloc(sizeof(char)*c-1);

  while(fgets(storage,500,l)){
    int tmp;
    cx_counter += c-3;
    newtoken = (char*)malloc(sizeof(char)*500);

    for(int i = 0; i < cx_counter; i++){
      newtoken[i] = storage[i];
      tmp = i;
      //printf("%s -ntok num - %d\n",newtoken,tmp);
      if(strcmp(newtoken,TOK_WRITE) == 0){
        free(newtoken);
        newtoken = (char*)malloc(sizeof(char)*500);
        if(storage[tmp+1] == '('){
          for(int nl = tmp+1; nl < 100 && storage[nl] != ')'; nl++){
            newtoken[nl] = storage[nl];
          }
        
          for(int al = tmp+2; al < 100 && newtoken[al] != ')' && newtoken[al] != '#'; al++){
            printf("%c", newtoken[al]);
            if(storage[al+2] == ';'){
              break;
            }
            if(newtoken[al+1] == '#'){
              printf("\n");
            }
          }
        }
      }

      //Under Work
      if(strcmp(newtoken,TOK_INT)==0){
        token_count += 1; 
      }
        
    }

    /*
    if(newtoken[0] == '('){
      printf("LFT_RND FOUND\n"); 
    }
    if(newtoken[0] == ')'){
      printf("RGT_RND FOUND\n"); 
    }
    */

    //printf("%s",storage);
  } 
  

  return 0;
}
