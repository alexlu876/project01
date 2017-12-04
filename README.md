Implemented:  
  
Basic commands such as `ls` and `ps` and variations of them such as `ls -l` and `ps -e`  
Running multiple commands on one line with `;`
Redirecting stdout with `>`  
Redirecting stdin with `<`  
Piping with `|`  
    
Failed Implementations:  
  
Bugs:  
  
Function headers:  
main2.c  
  
/*======== char ** parse_args() ==========  
Input: char * line
Returns: Array of the individual strings, which were separated by spaces
Separates the string `line` by `' '` and returns an array of the individual strings

/*======== void fork_and_runn() ==========  
Input: char ** args
Forks the current process, while the parent executes the command given in args, and the child waits for the parent to do so  
/*======== char ** fork_and_run() ==========  
Input: char ** args  
int x  
int y  
Does what fork_and_runn does, but sets 1 to stdout if 1 isn't stdout, and sets 0 to stdin if 0 isn't stdin  
/*======== void do_everything() ==========   
Input: char * line  
If there is a `;`, will recursively execute the commands separated by the `;`
If there is a `>`, will redirect the stdout produced from what comes before the `>` to a created file with the name of what is after the `>`  
If there is a `<`, will redirect the stdin from the file, which is named what comes after the `<` to either the command, which comes before the `<`, or to the shell program, main2.c, if nothing comes before the `<`  
If there is a `|`, will create a pipe, which redirects the stdout of what comes before the `|` to the stdin of what comes after the `|`  
/*======== int main() ==========  
Prints out "The Shell of Justice$" after every execution of command  
Exits program if `exit` is called
If `cd <DIRECTORY>` is called, changes directory to <DIRECTORY>
If the above two conditions aren't met, calls do_everything() to execute the command(s) called
