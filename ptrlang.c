#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define BOOL int 
#define TRUE 1 
#define FALSE 0

//<DOC> Stack Only supports 0-9 for now <DOC>
//<INF> Better Stack will come soon <INF>
//<DOC> Write Function type has defects <DOC>
//<DOC> Need to rework on # (newline) flag <DOC>

int main(int argc,char** argv) {
  if(argv[1] == NULL){
    printf("USAGE: ./sim filename.wpp\n");
  }
  BOOL isNewLine = FALSE;

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
  const char* TOK_S_R = "STACK-RESULT";
  const char* TOK_P2 = "PUSH-T";
  const char* TOK_S_IN = "STACK-INDEX";
  const char* TOK_OS_SL = "SLP-FOR";

  //Not-Formatted PrintF prototype (Unimplemented)
  const char* TOK_BT_PF = "N-PRINT";

  //Variable Initializers (IN WORK)
  const char* TOK_CHAR_IN = "PUSH-C";
  const char* TOK_CHAR_INDEX = "CSTACK-INDEX";

  char CHAR_STACK_STACK[15000] = {'\0'};
  //Variable Initializers

  //Tokens - End 

  int STACK[15000] = {0};
  int count = 0;


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
      //Under Work
      //Need To Make a better stack operation set
      //stack-operation set is remade and works better
      else if(strcmp(newtoken,TOK_PL_IN) == 0){
        int first_;
        int sec_; 
        char op;

        char tok[] = {'\0'};
        int t=0;
        /*
        first_ = (int)storage[i+2] - '0';
        op = storage[i+4]; 
        sec_ = (int)storage[i+6]  - '0';
        */
       for(int f=i+2;f<500;f++){
         tok[t] = storage[f]; 
         t+=1; 
         if(storage[f+1] == ','){
           tok[t] = '\0';
           first_ = atoi(tok); 
           t = t-t;
           for(int f2=f+1;f2<500;f2++){
             tok[t] = storage[f2];
             t+=1;
             if(storage[f2+1] == ','){
                op = storage[f2];
                t = t-t; 
                for(int f3=f2+2;f3<500;f3++){
                  tok[t] = storage[f3];
                  t += 1;
                  if(storage[f3+1] == ';'){
                    tok[t] = '\0';
                    sec_ = atoi(tok);
                    break;
                  }
                }
                break;
             }
           }
           break;
         }
       }

        if(first_ == 0){
          printf("ERROR: Calling Stack Storage Reserved portion containing blank values! or Pre-Stored , Pre-Used values\n");
        }
        if(first_ > sizeof(STACK)/sizeof(STACK[0])){
          printf("ERROR: You can not access the memory that is out of the reserved memory\n");
        }
        if(first_ < 0){
          printf("ERROR: You can not access the memory that is out of the reserved memory\n");
        }
        switch(op){
          case '+':
            STACK[0] = STACK[first_] + STACK[sec_];
            break;
          case '-': 
            STACK[0] = STACK[first_] - STACK[sec_];
            break;
          case '*':
            STACK[0] = STACK[first_] * STACK[sec_];
            break;
          case '/':
            STACK[0] = STACK[first_] / STACK[sec_];
            break;
          case '<':
            STACK[0] = STACK[first_] << STACK[sec_];
            break;
          case '>':
            STACK[0] = STACK[first_] >> STACK[sec_];
            break; 
          case '^':
            STACK[0] = STACK[first_] ^ STACK[sec_];
            break;
          case '|':
            STACK[0] = STACK[first_] | STACK[sec_];
            break;
        }
      }

      else if(strcmp(newtoken,TOK_S_R) == 0){
        printf("%d",STACK[0]);
      }

      //Character Stack Operation
      else if(strcmp(newtoken,TOK_P2) == 0){
        int n1,n2;
        char keyset[] = {'\0'};
        int t=0;
        int t2=0; 

        for(int g=i+2;g<50;g++){
          keyset[t] = storage[g];
          t+=1;
          if(storage[g+1] == ','){ 
            keyset[t] = '\0';
            n1 = atoi(keyset);
            for(int j=g+2;j<50;j++){
              keyset[t2] = storage[j];
              t2 += 1; 
              if(storage[j+1] == ';'){
                keyset[t2] = '\0';
                n2 = atoi(keyset);
                break;
              }
            }
            break;
          }
        }
        if(n2 != 0){
          STACK[n2] = n1;
        }
        else if(n2 == 0){
          printf("ERROR: Stack Storage Portion Access Permission Denied\nStack Storage can't be accessed!");
        }
        if(n2 > sizeof(STACK)/sizeof(STACK[0])){
          printf("ERROR: You can not access the memory that is out of the reserved memory\n");
        }
        if(n2 < 0){
          printf("ERROR: You can not access the memory that is out of the reserved memory\n");
        }
      }

      else if(strcmp(newtoken,TOK_CHAR_IN) == 0){
        int n2;
        char n1;
        char keyset[] = {'\0'};
        int t=0;
        int t2=0; 

        n1 = storage[i+2];
        for(int g=i+2;g<50;g++){
          keyset[t] = storage[g];
          t+=1;
          if(storage[g+1] == ','){ 
            keyset[t] = '\0';
            for(int j=g+2;j<50;j++){
              keyset[t2] = storage[j];
              t2 += 1; 
              if(storage[j+1] == ';'){
                keyset[t2] = '\0';
                n2 = atoi(keyset);
                break;
              }
            }
            break;
          }
        }
        
        CHAR_STACK_STACK[n2] = n1;

        if(n2 > sizeof(CHAR_STACK_STACK)/sizeof(CHAR_STACK_STACK[0])){
          printf("ERROR: You can not access the memory that is out of the reserved memory\n");
        }
        if(n2 < 0){
          printf("ERROR: You can not access the memory that is out of the reserved memory\n");
        }
      }
    


      else if(strcmp(newtoken,TOK_CHAR_INDEX) == 0){
        int n1;
        char keyto[] = {'\0'};
        int t = 0;
        for(int i3=i+2; i3 < 500;i3++){
          keyto[t] = storage[i3];
          t += 1;
          if(storage[i3] == ';')
          {
            keyto[t] = '\0';
            n1=atoi(keyto);
            break;
          }
        }
        printf("%c",CHAR_STACK_STACK[n1]);
      }

      //Sleep() function
      else if(strcmp(newtoken,TOK_OS_SL) == 0)
      {
        char ntok[] = {'\0'};
        int forsl; 
        int t = 0;

        for(int i3=i+2;i3<500;i3++){
          ntok[t] = storage[i3];
          t += 1;
          if(storage[i3+1] == ';'){
            ntok[t] = '\0';
            forsl = atoi(ntok);
            break;
          }
        }
        Sleep(forsl);
      }

      //STACK-INDEX Implemented to peek at a perticular index
      else if(strcmp(newtoken,TOK_S_IN) == 0){
        char n[] = {'\0'};
        int t = 0;
        int in;
        for(int gh=i+2;gh<500;gh++){
          n[t] = storage[gh];
          t += 1; 
          if(storage[gh+1] == ';'){
            n[t] = '\0';
            in = atoi(n);
            break;
          }
        }
        printf("%d",STACK[in]);
      }  
    }

    //Next ToDo String Stack Operation 
    //Next Next IF - THEN - ELSE statement 

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
