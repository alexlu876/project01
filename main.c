#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

void do_everything(char *);

char ** parse_args( char * line){
  if(line[strlen(line)-1] == ' '){
    line[strlen(line)-1] = '\0';

  }
  
  char ** args = malloc(sizeof(char*) * 100);
  int i = 0;

  while(line){
    args[i] = line;
    strsep(&line, " ");
    i++;
  }
  return args;
}


void fork_and_run(char ** args){
  
  if(!fork()){
    execvp(args[0], args);


  }
  else{
    int status;
    wait(&status);
  }
}


int pipes(char * first){
  
  char * pre = strsep(&first, "|");
  if(!first)
    return 0;
  /*
  int r = 0;
  int w = 1;

  char * pipeup[2];
  pipe(pipeup);
  */
  int sout = dup(1);
  int sin = dup(0);
  int fp = open("cc", O_WRONLY);
  
  int child1 = fork();
  int child2 = 0;
  if(getpid() == child1){
    child2 = fork();
  }
  
  if(getpid() == child2){ //child1
    dup2(fp, 1);
    do_everything(pre);
  }
  else if(getpid() == child1){
    int status;
    wait(&status);
    dup2(fp, 0);
    do_everything(first);
  }
  else{
   dup2(sout, 1); 
   dup2(sin, 0);
   return 1;
  }
  
}

void do_everything(char * line){
  if(!line){
    return;
  }
  
  if(line[0] == ' '){
    line++;
  }

  if(line[strlen(line)-1] == ' '){
    line[strlen(line)-1] = '\0';
  }


  //line to be processed by bash
  char * first = strsep(&line, ";");
  if(!pipes(first)){
  
    
    char ** args = parse_args(first);
    fork_and_run(args);
  }
  //end

  
  do_everything(line);

}


int main(){
  char line[100];

  while(1){
    printf("Enter command: ");
    fgets(line, sizeof(line), stdin);
    line[strlen(line)-1] ='\0';
    
    do_everything(line);

  }



   return 0;
  




}
