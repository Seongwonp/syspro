#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    char **ptr;
    extern char **environ;
    
    for(ptr = environ; *ptr != 0; ptr++)
        printf("%s \n", *ptr);
    
    exit(0);
}
