#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

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

int main(){
  char line[100];
  printf("Enter command: ");
  fgets(line, sizeof(line), stdin);
  line[strlen(line)-1] ='\0';

  
  char ** args = parse_args(line);
  execvp(args[0], args);
  return 0;





}
