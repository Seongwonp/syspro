#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct sigaction newact;
struct sigaction oldact;
void sigint_handler(int signo);

int main(void){
	newact.sa_handler = sigint_handler;
	sigfillset(&newact.sa_mask);

	sigaction(SIGINT, &newact, &oldact);

	while(1){
		printf("Type Ctrl-C!\n");
		sleep(1);
	}
}

void sigint_handler(int signo){
	printf("signal number %d\n",signo);
	printf("press it again, Exit.\n");
	sigaction(SIGINT, &oldact, NULL);
}

