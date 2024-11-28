#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

void p1(), p2();
jmp_buf env;

int main(){
	if(setjmp(env) != 0){
		printf("Exception handling after return due to error\n");
		exit(0);
	}
	else printf("First pass\n");

	p1();
}

void p1(){
	p2();
}

void p2(){
	int error;

	error =1;
	
	if (error){
		printf("Error \n");
		longjmp(env,1);
	}
}

