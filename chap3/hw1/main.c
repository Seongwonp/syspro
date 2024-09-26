#include <stdio.h>
#include "copy.h"
#define MAX_LINES 5

char line[MAX_LINES][MAXLINE];
char temp[MAXLINE];

int main(){

	for(int i=0; i<MAX_LINES; i++){
		gets(line[i]);
	}


	for(int a=0; a<MAX_LINES-1; a++){
		for(int b=a+1; b<MAX_LINES;b++){
			if(strlen(line[a])<strlen(line[b])){
				copy(line[a],temp);
				copy(line[b],line[a]);
				copy(temp, line[b]);
			}
		}
	}

	for(int i=0; i<MAX_LINES; i++)
		printf("%s\n", line[i]);


	return 0;
}

