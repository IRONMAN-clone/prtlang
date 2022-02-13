#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//<DOC> Stack Only supports 0-9 for now <DOC>
//<INF> Better Stack will come soon <INF>

int main(int argc,char** argv) {
  if(argv[1] == NULL){
    printf("USAGE: ./sim filename\n");
  }


  //Tokens - Start
  const char* TOK_WRITE = "Write"; 
  const char* STR_LIT = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char LFT_RND = '('; 
  char RGT_RND = ')';  
  const char* TOK_INT = "PUSH";
  const char* TOK_W_T = "TOP_WR";
  const char* TOK_N_L = "NEWLINE";
  const char* PLUS_ALL = "PLUS_STACK()";
  const char* TOK_P = "PAUSE";
  const char* TOK_F_S = "FLUSH";
  const char* TOK_PL_IN = "OPERATE_STACK-ATINDEX";

  //Tokens - End 

  int STACK[15000] = {0};
  int count = -1;


  FILE *l;
  l = fopen(argv[1], "r"); 

  int cx_counter = 0;

  char *newtoken = NULL;

  int c = getc(l);
  char *storage = (char*)malloc(sizeof(char)*15000);

  while(fgets(storage,15000,l)){
    int tmp;
    cx_counter += c-3;
    newtoken = (char*)malloc(sizeof(char)*15000);

    for(int i = 0; i < cx_counter; i++){
      newtoken[i] = storage[i];
      tmp = i;
      //printf("%s -ntok num - %d\n",newtoken,tmp);
      if(strcmp(newtoken,TOK_WRITE) == 0){
        if(storage[tmp+1] == '('){
          for(int nl = tmp+1; nl < c && storage[nl] != ')'; nl++){
            newtoken[nl] = storage[nl];
          }
        
          for(int al = tmp+2; al < c && newtoken[al] != ')'&& newtoken[al] != '#'; al++){
            printf("%c", newtoken[al]);
            if(storage[al+1] == ';'){
              break;
            }

            //NewLine Revisited (rework needed on New Line)
            if(storage[al+1] == '#'){     
              printf("\n");
            }
          }
        }
      }

      else if(strcmp(newtoken, TOK_INT) == 0){
        int t=i;
        count += 1;
        STACK[count] = storage[t+2] - '0';
      }
      else if(strcmp(newtoken, TOK_W_T) == 0){
        printf("%d",STACK[count]);
      }

      //WORK TO DO LEFT (PLUS ALL ELEMENTS IN STACK)
      else if(strcmp(newtoken, PLUS_ALL) == 0){
        int tmp = STACK[0];
        for(int gg=0; gg<=count; gg++){
          STACK[0] += STACK[gg]; 
        }
        STACK[0] = STACK[0] - tmp;
        printf("%d",STACK[0]);
      }

      else if(strcmp(newtoken,TOK_P) == 0)
      {
        system("pause");
      }

      else if(strcmp(newtoken,TOK_F_S) == 0)
      {
        for(int i5 = 0; i5 < sizeof(STACK)/sizeof(STACK[0]); i5++){
          STACK[i5] = 0;
        }
        count = count - count;
      }


      //Particular Operation at a particular index of the global stack
      else if(strcmp(newtoken,TOK_PL_IN) == 0){
        printf("%c",storage[i]);
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
