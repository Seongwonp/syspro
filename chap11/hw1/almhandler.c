#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int mysignal(int signo, void(*func)(int)){
        struct sigaction act, oldact;
        act.sa_handler = func;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        if(sigaction(signo, &act, &oldact)<0){
                return -1;
        }
        return 0;
}

void alarmHandler(int signo){
        printf("Wake up\n");
        exit(0);
}

int main(){
	if(mysignal(SIGALRM, alarmHandler)<0){
		perror("signal error");
		return 1;
	}

	alarm(5);
	short i =0;
	while(1){
		sleep(1);
		i++;
		printf("%d second\n",i);
	}
	printf("end\n");
}

