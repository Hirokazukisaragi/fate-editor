#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define ONE_LINE 81
#define MAX_ROW 65554
#define BUFSIZE 65554
typedef struct LIST{
  char *txtline;
  struct LINE *NEXT;
  //struct LINE *PREV;
}LIST;
void openfail(void);
char *readLine(char **allTEXT,long lineNum,char *fetchedLine);
char *inputLine(void);
void listText(LIST *top);
void writeLine(int lineNum);
void deleteLine(int lineNum);
// void addLIST(LIST *now,char *txtline);
LIST *addLIST(LIST *first,char *txtline);
LIST *new_list(char *txtline);

char WRITE_LINE[ONE_LINE];
char *write;
FILE *fp;
char EXIT_FLAG = 0;
int main(int argc,char *argv[]){
  char command[ONE_LINE];
  //char **allTEXT;
  LIST *allTEXT;
  char **altText;
  char *buffer;
  char *fetchedLine;
  long MAXIMUM_TEXT = 128;
  int ROW_NUM;
  int tlen = 0;
  long Line = 0;
  long lineNum = 0;
  long indextxt = 0;
  int err = 0;
  LIST *list;
  //altText = malloc(ONE_LINE);
  //*altText = malloc(MAX_ROW);
  buffer = malloc(ONE_LINE+1);
  fetchedLine = malloc(MAXIMUM_TEXT);
  if((fp = fopen(argv[1],"r+")) == NULL){
    if((fp = fopen(argv[1],"w+")) == NULL){
      openfail();
    }
  }
  
  //LIST *first = new_list(NULL,buffer);
  LIST *first;
  first = NULL;
  //first = addLIST(buffer);
  //LIST *top = first;
  //LIST *first = top;
  //printf("top is %s\n",buffer)
  list = first;
  while(1){
    fgets(buffer,ONE_LINE,fp);
    first = addLIST(first,buffer);
    if(feof(fp)){
      break;
    }
  }
  //first = top;
  //fread(allTEXT,sizeof(char),MAXIMUM_TEXT,fp);
  while(1){
    //rewind(fp);
    //first = top;
    
    memset(command,0,ONE_LINE);

    printf("please input command:");
    fgets(command,MAX_ROW,stdin);

    if(!strcmp(command,"q\n")){
      break;
    }
    
    if(!strcmp(command,"l\n")){
      //listText(first);
      listText(first);
      continue;
    }
    
  }
  free(fetchedLine);
  //listFree(top);
  fclose(fp);
  return 0;
}

void listText(LIST *top){
  long lnum=1;
  while(top->NEXT != NULL){
    printf("%ld:",lnum);
    printf("%s",top->txtline);
    top = top->NEXT;
    lnum++;
  }
}
LIST *addLIST(LIST *now,char *txtline){
  LIST *p;
  p = malloc(sizeof(LIST));
  p->txtline = malloc(ONE_LINE);
  strcpy(p->txtline,txtline);
  p->NEXT = now;
  now = p;
  return now;
}
void listFree(LIST *OLD){
  LIST *temp = OLD;
  LIST *swap = NULL;
  while(temp != NULL){
    swap = temp->NEXT;
    free(temp);
    temp = swap;
  }
}
void openfail(void){
  printf("FAITAL ERROR\n");
  exit(1);
}

