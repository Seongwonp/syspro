#include <stdio.h>
#define MAXLINE 100

int main(int argc, char* argv[]){
	char line[MAXLINE];
	FILE *fpin, *fpout;

	if((fpin = popen(argv[1],"r")) == NULL){
		perror("popen ERROR");
		return 1;
	}

	if((fpout = popen(argv[2],"w"))==NULL){
		perror("popen ERROR");
		return 1;
	}

	while(fgets(line, MAXLINE, fpin))
		fputs(line,fpout);

	pclose(fpin);
	pclose(fpout);
	return 0;
}

