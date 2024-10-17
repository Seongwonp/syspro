#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main(int argc, char *argv[]){
	
	struct student record;
	FILE *fp;

	if(argc != 2){
		fprintf(stderr,"How to use: %s FileName\n", argv[0]);
		exit(1);
	}

	fp = fopen(argv[1],"wb");
	printf("%-9s %-8s %-4s\n","StudentID","Name","Score");
	while(scanf("%d %s %d", &record.id, record.name, &record.score) == 3)
		fwrite(&record, sizeof(record), 1, fp);
	
	fclose(fp);
	exit(0);
}

