#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define ONE_LINE 81
#define MAX_ROW 65554
#define BUFSIZE 65554
typedef struct LIST{
  char *txtline;
  char *isEnd;
  struct LINE *NEXT;
  struct LINE *PREV;
}LIST;
void openfail(void);
char *readLine(char **allTEXT,long lineNum,char *fetchedLine);
char *inputLine(void);
void listText(LIST *top);
void writeLine(int lineNum);
void deleteLine(int lineNum);


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
  //altText = malloc(ONE_LINE);
  //*altText = malloc(MAX_ROW);
  buffer = malloc(ONE_LINE+1);
  fetchedLine = malloc(MAXIMUM_TEXT);
  if((fp = fopen(argv[1],"r+")) == NULL){
    if((fp = fopen(argv[1],"w+")) == NULL){
      openfail();
    }
  }
  fgets(buffer,MAXIMUM_TEXT,fp);
  
  LIST *top = new_list(buffer);
  LIST *first = top;
  printf("top is %s\n",buffer);
  //fread(allTEXT,sizeof(char),MAXIMUM_TEXT,fp);
  while(1){
    rewind(fp);
    //memset(allTEXT->txtline,0,ONE_LINE);
    while(!feof(fp)){
      printf("bf\n");
      fgets(buffer,ONE_LINE,fp);
      printf("ef\n");
      addLIST(top,buffer);
      //Line++;
    }
    
      //indextxt = MAXIMUM_TEXT - 1;
    //altText = allTEXT;
    memset(command,0,ONE_LINE);
    /*
    if(allTEXT[sizeof(allTEXT)] != '\0'){
      MAXIMUM_TEXT++;

      altText = malloc(MAXIMUM_TEXT);
      if(altText != allTEXT){
	memcpy(altText,allTEXT,MAXIMUM_TEXT);
	free(allTEXT);
      }
      allTEXT = realloc(altText,MAXIMUM_TEXT);
      if(altText != allTEXT){
	memcpy(allTEXT,altText,MAXIMUM_TEXT);
	free(altText);
      }
      //free(allTEXT);
      //allTEXT = malloc(MAXIMUM_TEXT);

      continue;
    }
    */
    //while(allTEXT[MAXIMUM_TEXT-1] != '\0'){
    /*
    while(*allTEXT[Line] != '\0'){
      rewind(fp);
      memset(allTEXT,0,MAXIMUM_TEXT-1);

      //if(allTEXT[MAXIMUM_TEXT] != '\0'){
      //continue;
      //}
      //printf("now=%s\n",allTEXT);
      free(allTEXT);
      MAXIMUM_TEXT++;
      allTEXT = malloc(MAXIMUM_TEXT);
      fgets(allTEXT[Line],ONE_LINE,fp);
      indextxt = MAXIMUM_TEXT - 1;
      Line++;
      //continue;
    }
    */
    memset(fetchedLine,0,MAXIMUM_TEXT);
    printf("please input command:");
    fgets(command,MAX_ROW,stdin);

    if(!strcmp(command,"q\n")){
      break;
    }
    /*
    if(!strcmp(command,"s\n")){
      tlen = strlen(allTEXT);

      *allTEXT[tlen] = '\0';
      printf("%s\n",allTEXT[Line]);
      printf("written=%d\n",tlen);
      while(*allTEXT[Line] != '\0'){
	err = fwrite(*allTEXT[Line],sizeof(char),tlen,fp);
	if(err < tlen){
	  printf("written error=%d!\n",err);
	}
	Line++;
      }
	printf("MAX is %d\n",MAXIMUM_TEXT);
	
	continue;
    }
      //pending
    if(!strcmp(command,"r\n")){
      fgets(command,MAX_ROW,stdin);
      sscanf(command,"%d",&ROW_NUM);
      fetchedLine = readLine(allTEXT,ROW_NUM,fetchedLine);
      printf("%s\n",fetchedLine);
      continue;
    }
    if(!strcmp(command,"d\n")){
      fgets(command,MAX_ROW,stdin);
      sscanf(command,"%d",&ROW_NUM);
      deleteLine(ROW_NUM);
      continue;
    }
    */
    if(!strcmp(command,"l\n")){
      listText(first);
      listText(top);
      continue;
    }
    /*
    sscanf(command,"%d",&ROW_NUM);
    write = inputLine();
    if(!strcmp("Too long",write)){
      memset(WRITE_LINE,'\0',ONE_LINE);
      continue;
    }
    */
    //writeLine(lineNum);

  }
  //fseek(fp,0,SEEK_END);
  //while(*allTEXT != '\0'){

  //  fputc(*allTEXT,fp);
  //    *allTEXT++;
  //  }
  free(fetchedLine);
  listFree(top);
  fclose(fp);
  return 0;
}
/*
char *readLine(char **allTEXT,long lineNum,char *fetchedLine){
  long linecount = 1;
  long i = 0,j=0;
  while(linecount != lineNum){
    if(*allTEXT[i] == '\n'){
      linecount++;
      i++;
    }
    if(linecount == lineNum){
      while(allTEXT[i]){
	fetchedLine[j] = *allTEXT[i];
	i++;
	j++;
      }
    }
    if(*allTEXT[i] == '\0'){
      printf("please input validate line\n");
      break;
    }
    i++;
  }
  if(lineNum == 1){
    while((*allTEXT[i] != '\n') && (*allTEXT[i] != '\0')){
      fetchedLine[j] = *allTEXT[i];
      i++;
      j++;
    }
  }
  return fetchedLine;
}
char *inputLine(void){
  fgets(WRITE_LINE,ONE_LINE,stdin);
  if(strlen(WRITE_LINE) >= ONE_LINE-1){
    printf("行が長すぎます\n");
    memset(WRITE_LINE,'\0',ONE_LINE);
    return "Too long";
  }
  return WRITE_LINE;
}
void writeLine(int lineNum){
  char dummy[ONE_LINE];
  for(int i=0;i != lineNum;i++){
    fgets(dummy,ONE_LINE,fp);
    if(feof(fp)){
      break;
    }
  }
  fseek(fp,0,SEEK_END);
  //fwrite(WRITE_LINE,sizeof(char),MAXIMUM_TEXT,fp);
}

void deleteLine(int lineNum){
  int i;
  char dummy[ONE_LINE];
  for(i=0;i != lineNum;i++){
    fgets(dummy,ONE_LINE,fp);
    if(feof(fp)){
      break;
    }
  }
  //未実装

}
*/
void listText(LIST *top){
  long lnum=1;
  long i=0;
  printf("into show\n");
  while((top->isEnd)){
    printf("%ld:",lnum);
    while(top->txtline[i] != '\0'){
      printf("%c",top->txtline[i]);
      i++;
    }
    top = top->NEXT;
    lnum++;
    i++;
  }
}
LIST *new_list(char *txtline){
  LIST *new = NULL;
  new = malloc(sizeof(LIST));
  new->NEXT = NULL;
  new->isEnd = 1;
  new->txtline = malloc(ONE_LINE);
  new->txtline = txtline;
  return new;
}
void addLIST(LIST *prev,char *txtline){
  LIST *NEXT = NULL;
  LIST *PREV = prev;
  
  NEXT = new_list(txtline);
  while(PREV->NEXT != NULL){
    PREV = PREV->NEXT;
    PREV->isEnd = 0;
  }
    PREV->NEXT = NEXT;
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

