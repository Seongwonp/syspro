#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 80

int main(int argc, char *argv[]){
	FILE *fp;
	int line = 0;
	char buffer[MAXLINE];

	if(argc !=2){
		fprintf(stderr,"How to use : line FileName\n");
		exit(1);
	}

	if((fp=fopen(argv[1],"r")) == NULL){
		fprintf(stderr,"Error Open File\n");
		exit(2);
	}

	while(fgets(buffer,MAXLINE, fp) != NULL){
		line++;
		printf("%3d %s",line,buffer);
	}
	exit(0);
}

