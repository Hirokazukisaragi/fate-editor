#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define ONE_LINE 81
#define MAX_ROW 655554
void openfail(void);
char *readLine(char *allTEXT,long lineNum,char *fetchedLine);
char *inputLine(void);
void listText(char *allTEXT);
void writeLine(int lineNum);
void deleteLine(int lineNum);

char WRITE_LINE[ONE_LINE];
char *write;
FILE *fp;
char EXIT_FLAG = 0;
int main(int argc,char *argv[]){
  char command[ONE_LINE];
  char *allTEXT;
  char *altText;
  char *fetchedLine;
  long MAXIMUM_TEXT = 128;
  int ROW_NUM;
  int tlen = 0;
  long lineNum = 0;
  long indextxt = 0;
  int err = 0;
  allTEXT = malloc(MAXIMUM_TEXT);
  altText = malloc(MAXIMUM_TEXT);
  fetchedLine = malloc(MAXIMUM_TEXT);
  if((fp = fopen(argv[1],"r+")) == NULL){
    if((fp = fopen(argv[1],"w+")) == NULL){
      openfail();
    }
  }
  //fread(allTEXT,sizeof(char),MAXIMUM_TEXT,fp);
  while(1){
    rewind(fp);
    memset(allTEXT,0,MAXIMUM_TEXT);
    fread(allTEXT,sizeof(char),MAXIMUM_TEXT,fp);
    indextxt = MAXIMUM_TEXT - 1;
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
    while(allTEXT[indextxt] != '\0'){
      rewind(fp);
      memset(allTEXT,0,MAXIMUM_TEXT-1);

      //if(allTEXT[MAXIMUM_TEXT] != '\0'){
      //continue;
      //}
      //printf("now=%s\n",allTEXT);
      free(allTEXT);
      MAXIMUM_TEXT++;
      allTEXT = malloc(MAXIMUM_TEXT);
      fread(allTEXT,sizeof(char),MAXIMUM_TEXT,fp);
      indextxt = MAXIMUM_TEXT - 1;
      //continue;
    }
    memset(fetchedLine,0,MAXIMUM_TEXT);
    printf("please input command:");
    fgets(command,MAX_ROW,stdin);

    if(!strcmp(command,"q\n")){
      break;
    }

    if(!strcmp(command,"s\n")){
      tlen = strlen(allTEXT);

      allTEXT[tlen] = '\0';
      printf("%s\n",allTEXT);
      printf("written=%d\n",tlen);
      err = fwrite(allTEXT,sizeof(char),tlen,fp);
      if(err < tlen){
	printf("written error=%d!\n",err);
      }
      printf("MAX is %d\n",MAXIMUM_TEXT);
      continue;
    }

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
    if(!strcmp(command,"l\n")){
      listText(allTEXT);
      continue;
    }
    sscanf(command,"%d",&ROW_NUM);
    write = inputLine();
    if(!strcmp("Too long",write)){
      memset(WRITE_LINE,'\0',ONE_LINE);
      continue;
    }
    //writeLine(lineNum);

  }
  //fseek(fp,0,SEEK_END);
  //while(*allTEXT != '\0'){

  //  fputc(*allTEXT,fp);
  //    *allTEXT++;
  //  }
  free(fetchedLine);
  free(allTEXT);
  free(altText);
  fclose(fp);
  return 0;
}
char *readLine(char *allTEXT,long lineNum,char *fetchedLine){
  long linecount = 1;
  long i = 0,j=0;
  while(linecount != lineNum){
    if(allTEXT[i] == '\n'){
      linecount++;
      i++;
    }
    if(linecount == lineNum){
      while((allTEXT[i] != '\n') && (allTEXT[i] != '\0')){
	fetchedLine[j] = allTEXT[i];
	i++;
	j++;
      }
    }
    if(allTEXT[i] == '\0'){
      printf("please input validate line\n");
      break;
    }
    i++;
  }
  if(lineNum == 1){
    while((allTEXT[i] != '\n') && (allTEXT[i] != '\0')){
      fetchedLine[j] = allTEXT[i];
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
void listText(char *allTEXT){
  long lnum=1;
  long i=0;
  while(allTEXT[i] != '\0'){
    printf("%ld:",lnum);
    while(allTEXT[i] != '\n'){
      printf("%c",allTEXT[i]);
      i++;
      if(allTEXT[i] == '\n'){
	printf("\n");
      }
    }
    lnum++;
    i++;
  }
}
void openfail(void){
  printf("FAITAL ERROR\n");
  exit(1);
}

