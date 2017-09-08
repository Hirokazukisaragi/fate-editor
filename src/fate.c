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
LIST *delList(LIST *top,long delnum);
LIST *insertTxt(LIST *top,long insert);
LIST *single(char *name);
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
  char immdata[128];
  long immline=0;
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
  first = list;
  list = malloc(sizeof(LIST));
  list->txtline = malloc(ONE_LINE);
  list->NEXT = NULL;
  //first = NULL;
  fgets(buffer,ONE_LINE,fp);
  first = addLIST(list,buffer);
  //LIST *top = first;
  //LIST *first = top;
  //printf("top is %s\n",buffer)
  //first = list;
  while(1){
    
    fgets(buffer,ONE_LINE,fp);
    while(list->NEXT != NULL){
      list = list->NEXT;
    }
    list = addLIST(list,buffer);
    if(feof(fp)){
      break;
    }
  }
  
  LIST *initial;
  
  initial = first;
  //first = top;
  //fread(allTEXT,sizeof(char),MAXIMUM_TEXT,fp);
  while(1){
    //rewind(fp);
    //first = top;
    first = initial;
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
    if(!strcmp(command,"d\n")){
      fgets(immdata,128,stdin);
      sscanf(immdata,"%ld",&immline);
      first = delList(first,immline);
    }
    if(!strcmp(command,"i\n")){
      fgets(immdata,128,stdin);
      sscanf(immdata,"%ld",&immline);
      first = insertTxt(first,immline);
    }
    if(!strcmp(command,"s\n")){
      initial = first;
      fclose(fp);
      fp = fopen(argv[1],"w+");
      rewind(fp);
      while(1){
	fputs(first->txtline,fp);
	first = first->NEXT;
	if(first->NEXT == NULL){
	  break;
	}
      }
      first = initial;
    }
  }
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
LIST *insertTxt(LIST *top,long insert){
  LIST *head,*ins,*temp1,*temp2;
  //head = top;
  listText(head);
  char buffer[ONE_LINE];
  long i = 0,j = 0;
  insert--;
  if(!insert){
    head = top;
    fgets(buffer,ONE_LINE,stdin);
    printf("pregen\n");
    ins = single(buffer);
    printf("buffed\n");
    temp1 = ins;
    top = top->NEXT;
    top = ins;
    ins->NEXT = top->NEXT;
  }else{
    fgets(buffer,ONE_LINE,stdin);
    temp1 = addLIST(top,buffer);
    for(j=1;j < insert;j++){
      top = top->NEXT;
    }
    
    printf("temp1->%s\ntemp2->%s\n",temp1->txtline,temp2->txtline);
  }
  //listText(head);
  return head;
}
LIST *delList(LIST *top,long delnum){
  printf("del:%ld\n",delnum);
  long i = 1,j=0;
  LIST *topdev,*init;
  LIST *temp1,*temp2;
  delnum = delnum - 1;
  if(!delnum){
    top = top->NEXT;
  }else{
    topdev = top;
    for(j=1;j < delnum;j++){
      top = top->NEXT;
    }
    temp1 = top;
    top = top->NEXT;
    
    temp2 = top->NEXT;
    
    top = temp1;
    top->NEXT = temp2;
    
    top = topdev;
  }
  topdev = top;
  listText(topdev);
  return topdev;
}
// LIST *insertTxt( 
LIST *addLIST(LIST *now,char *txtline){
  LIST *p;
  p = malloc(sizeof(LIST));
  p->txtline = malloc(ONE_LINE);
  p->NEXT = NULL;
  while(now->NEXT != NULL){
    now = now->NEXT;
  }
  strcpy(p->txtline,txtline);
  now->NEXT = p;
  //p->NEXT = NULL;
  //now = p;
  return p;
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
LIST *single(char *name){
  LIST *E;
  E = malloc(sizeof(LIST));
  E->NEXT = NULL;
  strcpy(name,E->txtline);
  return E;
}
void openfail(void){
  printf("FAITAL ERROR\n");
  exit(1);
}

