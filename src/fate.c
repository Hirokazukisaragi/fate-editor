/****************************************************************
Copyright (C) 2017  Hirokazu Seno

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define ONE_LINE 81
#define MAX_ROW 65554
#define BUFSIZE 65554
typedef struct LIST{
  char *txtline;
  struct LIST *NEXT;
  //struct LINE *PREV;
}LIST;
/* 
openfail if FILE open fail, exit
listText is show LIST add line number
deleteLine is select line disconnect pointer
listFree do free() LIST
 */
void openfail(void);
void listText(LIST *top);
void deleteLine(int lineNum);
void listFree(LIST *top);

LIST *addLIST(LIST *first,char *txtline);
LIST *new_list(LIST *next,char *txtline);
LIST *delList(LIST *top,long delnum);
LIST *insertTxt(LIST *top,long insert);
FILE *saveFile(FILE *fp,LIST *sLIST);
int validation(char Flag);

char WRITE_LINE[ONE_LINE];
char *write;
FILE *fp;
char fName[6554];
char SAVED_FLAG = 1;
char EXIT_FLAG = 0;
int base = 10;
int main(int argc,char *argv[]){
  char command[ONE_LINE];
  char *buffer;
  char immdata[128];
  long immline=0;
  strcpy(fName,argv[1]);
  LIST *list = NULL;
  buffer = malloc(ONE_LINE+1);
  if((fp = fopen(fName,"r+")) == NULL){
    if((fp = fopen(fName,"w+")) == NULL){
      openfail();
    }
  }
  /*
first is head of LIST 
 */
  LIST *first;
  first = list;
  list = malloc(sizeof(LIST));
  list->txtline = malloc(ONE_LINE);
  list->NEXT = NULL;
  fgets(buffer,ONE_LINE,fp);
  first = addLIST(list,buffer);
    /*
generate initial LIST 
 */
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
  
  while(1){
    memset(command,0,ONE_LINE);
    
    printf("please input command:");
    fgets(command,MAX_ROW,stdin);
    
    if(!strcmp(command,"q\n")){
      if(SAVED_FLAG == 1){
	break;
      }else if(SAVED_FLAG == 0){
	printf("FILE NOT SAVED. QUIT OK(Y/N):");
	fflush(stdout);
	fgets(buffer,ONE_LINE,stdin);
	if(!strcmp(buffer,"Y\n")){
	  break;
	}else{
	  continue;
	}
      }
    }
    if(!strcmp(command,"l\n")){
      listText(first);
      continue;
    }
    if(!strcmp(command,"d\n")){
      printf("which line delete:");
      fgets(immdata,128,stdin);
      immline = strtol(immdata,NULL,base);
      if(immline < 1){
	validation(0);
	continue;
      }
      SAVED_FLAG = 0;
      first = delList(first,immline);

    }
    if(!strcmp(command,"i\n")){
      printf("where insert line:");
      fgets(immdata,128,stdin);
      immline = strtol(immdata,NULL,base);
      SAVED_FLAG = 0;
      if(immline < 1){
	validation(0);
	continue;
      }
      first = insertTxt(first,immline);
      if(immline < 1){
	validation(0);
	SAVED_FLAG = 0;
	continue;
      }
    }
    if(!strcmp(command,"s\n")){
      //first = initial;
      saveFile(fp,first);
    }

  }
  listFree(first);
  fclose(fp);
  return 0;
}
/* create new LIST */
LIST *new_list(LIST *next,char *txtline){
  LIST *now;  
  now = malloc(sizeof(LIST));
  now->txtline = malloc(ONE_LINE);
  now->NEXT = next;
  strcpy(now->txtline,txtline);
  return now;
}
/* show the LIST */
void listText(LIST *top){
  long lnum=1;
  while(top->NEXT != NULL){
    if(top->NEXT == NULL){
      break;
    }
    printf("%ld:",lnum);
    printf("%s",top->txtline);
    top = top->NEXT;
    lnum++;
  }
  printf("\n");
}
/* insert single LIST into second argument */
LIST *insertTxt(LIST *top,long insert){
  LIST *head,*ins,*temp;
  ins = malloc(sizeof(LIST));
  char buffer[ONE_LINE];
  long j = 0;
  memset(buffer,0,ONE_LINE);
  insert--;
  if(!insert){
    head = top;
    ins = top;
    fgets(buffer,ONE_LINE,stdin);
    ins = new_list(head,buffer);
    ins->NEXT = head;
    return ins;
  }else{
    head = top;
    fgets(buffer,ONE_LINE,stdin);
    for(j=1;j < insert;j++){
      top = top->NEXT;
    }
    temp = top;
    top = new_list(top->NEXT,buffer);
    temp->NEXT = top;
    return head;
  }
  return head;
}
/* dettach LIST and LIST->NEXT
ATTENTION! this function NOT free LIST!
 */
LIST *delList(LIST *top,long delnum){
  printf("del:%ld\n",delnum);
  long j=0;
  LIST *topdev;
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
/* do free the LIST */
void listFree(LIST *OLD){
  LIST *temp = OLD;
  LIST *swap = NULL;
  char *swaptxt = "";
  while(temp != NULL){
    swap = temp->NEXT;
    swaptxt = temp->txtline;
    free(swaptxt);
    free(temp);
    temp = swap;
  }
}

void openfail(void){
  printf("FAITAL ERROR\n");
  exit(1);
}
int validation(char Flag){
  if(Flag == 0){
    printf("NO permit input\n");
  }
  return 0;
}
FILE *saveFile(FILE *fp,LIST *first){
  char YorN[16];
  FILE *wfp;
  wfp = fp;
  
  memset(YorN,0,16);
  printf("File overrite OK? Y/N:");
  fflush(stdout);
  fgets(YorN,15,stdin);
  if(!strcmp(YorN,"N\n")){
    SAVED_FLAG =0;
    return NULL;
  }
  if(!strcmp(YorN,"Y\n")){
    SAVED_FLAG = 1;
    wfp = fopen(fName,"w+");
    rewind(wfp);
    while(1){
      fputs(first->txtline,wfp);
      first = first->NEXT;
      if(first->NEXT == NULL){
	break;
      }
    }
  }
  return wfp;
}
