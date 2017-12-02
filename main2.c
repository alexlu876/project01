#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
char ** parse_args(char * line);//parse the line by space and return the array of the individual strings
void fork_and_run(char ** args,int x,int y);//forks and executes the command given
void do_everything(char * line);//the entire program

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


void fork_and_run(char ** args, int x, int y){
  
  if(!fork()){
    execvp(args[0], args);


  }
  else{
  
    int status;
    if (x!= 1){//change stdout back to 1
      dup2(x,1);
    }
    if (y!=0){//change stdin back to 0
      dup2(y,0);
    }
    wait(&status);
  }
}

void do_everything(char * line){
  if(!line){
    return;
  }
  
  while(line[0] == ' '){
    line++;
  }

  while(line[strlen(line)-1] == ' '){
    line[strlen(line)-1] = '\0';
  }
  char * first = strsep(&line, ";");
  
  if (strchr(first,'>') != NULL){//redirect greater than
    char * function = strsep(&first, ">");
    // printf("%s\n%s\n", function, first);
    // first is file
    char ** args = parse_args(function);
    while(first[0] == ' '){
      first++; 
    }
    int fd = open(first, O_WRONLY | O_CREAT, 0666);
    int x = dup(1);
    dup2(fd, 1);
    fork_and_run(args, x,0);   
  }
  //< <FILE> doesn't work 
  else if (strchr(first,'<')!= NULL){//redirect less than
    char * function = strsep(&first, "<");
    char ** args = parse_args(function);
    while (first[0] == ' '){
      first++;
    }
    
    int fd = open(first, O_RDONLY | O_CREAT, 0666);
    int y = dup(0);
    dup2(fd,0);
    fork_and_run(args, 1, y);
    
  }
  else{
    char ** args = parse_args(first);
    fork_and_run(args,1,0);  
    do_everything(line);
  }  
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
