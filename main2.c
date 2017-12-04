#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
/*
/======== char ** parse_args() ==========
Input: char * line Returns: Array of the individual strings, which were separated by spaces Separates the string line by ' ' and returns an array of the individual strings

/======== void fork_and_runn() ==========
Input: char ** args Forks the current process, while the parent executes the command given in args, and the child waits for the parent to do so
/======== char ** fork_and_run() ==========
Input: char ** args
int x
int y
Does what fork_and_runn does, but sets 1 to stdout if 1 isn't stdout, and sets 0 to stdin if 0 isn't stdin
/======== void do_everything() ==========
Input: char * line
If there is a ;, will recursively execute the commands separated by the ; If there is a >, will redirect the stdout produced from what comes before the > to a created file with the name of what is after the >
If there is a <, will redirect the stdin from the file, which is named what comes after the < to either the command, which comes before the <, or to the shell program, main2.c, if nothing comes before the <
If there is a |, will create a pipe, which redirects the stdout of what comes before the | to the stdin of what comes after the |
/======== int main() ==========
Prints out "The Shell of Justice$" after every execution of command
Exits program if exit is called If cd <DIRECTORY> is called, changes directory to If the above two conditions arent met, calls do_everything() to execute the command(s) called*/

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


/*void forkandreset(char ** args, int in, int out){
   if(!fork()){
    execvp(args[0], args);


  }
  else{
  
    int status;
    wait(&status);

    dup2(in, 0);
    dup2(out, 1);
  
  }

  }*/


void fork_and_runn(char ** args){
  
  if(!fork()){
    execvp(args[0], args);


  }
  else{
  
    int status;
    wait(&status);
  
  }
}
void fork_and_run(char ** args, int x, int y){
  
  if(!fork()){
    execvp(args[0], args);


  }
  else{
  
    int status;
    wait(&status);
    if (x!= 1){//change stdout back to 1
      dup2(x,1);
    }
    if (y!=0){//change stdin back to 0
      dup2(y,0);
    }
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
  else if (strchr(first,'<')!= NULL){//redirect less than
    char * function = strsep(&first, "<");
    char ** args = parse_args(function);
    while (first[0] == ' '){
      first++;
    }
     if (strcmp(args[0],"") == 0){
       return;
     }
    int fd = open(first, O_RDONLY | O_CREAT, 0666);
    int y = dup(0);
    dup2(fd,0);
    fork_and_run(args, 1, y);
    
  }
  //piping
  else if(strchr(first, '|')!= NULL){
    char * ff = strsep(&first, "|");
    while (first[0] == ' '){
      first++;
    }
    
    
    int in = dup(0);
    int out = dup(1);
    int fil = open("java",   O_WRONLY);
    dup2(fil, 1);
    char ** arg1 = parse_args(ff);
    char ** arg2 = parse_args(first);
    fork_and_runn(arg1);
    
    int fil2 = open("java",O_RDONLY);
    dup2(fil2, 0);
    close(fil);
    dup2(out, 1);
    fork_and_runn(arg2);
    dup2(in, 0);
    close(fil2);
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
    printf("The Shell of Justice$ ");
    fgets(line, sizeof(line), stdin);
    line[strlen(line)-1] ='\0';
    if (strcmp(line, "exit")==0){
      exit(1);
    }
    else if (strstr(line, "cd") != NULL){
      char ** args = parse_args(line);
      chdir(args[1]);
    }
    else{
      do_everything(line);
    }
    
  }
   return 0;
  




}
