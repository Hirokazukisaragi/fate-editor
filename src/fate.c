#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define ONE_LINE 81
#define MAX_ROW 65554

void openfail(void);
char *inputLine(void);
void writeLine(int lineNum);
void deleteLine(int lineNum);

char WRITE_LINE[ONE_LINE];
char *write;
FILE *fp;
char EXIT_FLAG = 0;
int main(int argc,char *argv[]){
  char rowTmp[MAX_ROW];
  int ROW_NUM;
  int lineNum = 0;
  if((fp = fopen(argv[1],"r+")) == NULL){
    if((fp = fopen(argv[1],"w+")) == NULL){
      openfail();
    }
  }
  fseek(fp,0,SEEK_SET);
  while(1){
    rewind(fp);
    printf("please input line number(exit :q):");
    fgets(rowTmp,MAX_ROW,stdin);
    if(!strcmp(rowTmp,":q\n")){
      break;
    }
    if(!strcmp(rowTmp,":d\n")){
      fgets(rowTmp,MAX_ROW,stdin);
      sscanf(rowTmp,"%d",&ROW_NUM);
      fseek(fp,0,SEEK_SET);
      deleteLine(ROW_NUM);
      continue;
    }
    sscanf(rowTmp,"%d",&ROW_NUM);
    write = inputLine();
    if(!strcmp("Too long",write)){
      memset(WRITE_LINE,'\0',ONE_LINE);
      continue;
    }
    writeLine(lineNum);

  }
  //fwrite(write,sizeof(char),strlen(write),fp);
  fclose(fp);
  return 0;
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
    if(!feof(fp)){
      break;
    }
  }
  fwrite(WRITE_LINE,sizeof(char),strlen(WRITE_LINE),fp);
}

void deleteLine(int lineNum){
  int i=0,w=0,nl=1,size=0;
  long debugi = 0;
  fseek(fp,0,SEEK_SET);
  ftell(fp);
  printf("del=%d\n ftell=%ld\n",lineNum,debugi);
  char dummy[ONE_LINE];
  strcpy(dummy,"\r\n");
  //rewind(fp);
  while(1){
    w = fgetc(fp);
    
    if(w == '\n'){
      nl++;
    }
    if(nl == lineNum){
      printf("deleting=%d,now=%d\n",lineNum,i);
      fseek(fp,0,SEEK_SET);
      fseek(fp,i,SEEK_SET);
      debugi = ftell(fp);
      //printf("%s",dummy);
      size = strlen(dummy) + 1;
      //dummy[size-1] = '\r';
      //dummy[size] = '\n';
      fwrite(dummy,1,2,fp);
      //fputs(dummy,fp);
      break;
    }
    i++;
    /*
    if(!feof(fp)){
      printf("end of file\n");
      break;
    }
     */
  }
  
}

void openfail(void){
  printf("FAITAL ERROR\n");
  exit(1);
}
