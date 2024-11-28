#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(){
	alarm(5);
	printf("Loop start\n");
	short i = 0;
	while(1){
		sleep(1);
		i++;
		printf("%d second\n",i);
	}
	printf("end\n");
}

