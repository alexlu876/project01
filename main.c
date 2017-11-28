#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

char ** parse_args( char * line){

  
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

void do_everything(char * line){
  if(!line){
    return;
  }
  char * first = strsep(&line, ";");
  

  
  char ** args = parse_args(first);
  fork_and_run(args);

  do_everything(line);

}


void chop_spaces(char * line){
  



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
