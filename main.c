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
    // printf("given line: %s\n", line);
    strsep(&line, " ");
    // printf("after strsep new line: %s\n", line);
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

int main(){
  char line[100];

  while(1){
    printf("Enter command: ");
    fgets(line, sizeof(line), stdin);
    line[strlen(line)-1] ='\0';
    char ** args = parse_args(line);
    fork_and_run(args);

    /*
    if(!fork()){
      char ** args = parse_args(line);
      execvp(args[0], args);
    }
    else{
      int status;
      wait(&status);

    }
    */
  }



   return 0;
  




}
