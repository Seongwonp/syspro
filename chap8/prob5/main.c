#include <stdio.h>
#include <unistd.h>

int main(){
    printf("My process number: [%d] \n", getpid());
    printf("My parent process number: [%d] \n", getppid());
}
