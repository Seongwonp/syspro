#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define ID 1
struct storedata{
  char name[MAX];
  int id;
  char category[MAX];
  int expired_date;
  int stock; 
 };



int main(int argc, char *argv[]){
	
	struct storedata record;
	FILE *fp;

	if(argc != 2){
		fprintf(stderr,"How to use: %s FileName\n", argv[0]);
		exit(1);
	}

	fp = fopen(argv[1],"wb");
	printf("%3s %12s %8s %12s %5s\n","id","name","category","expried date","stock");
	while(scanf("%d %s %s %d %d",&record.id,record.name,record.category,&record.expired_date,&record.stock) == 5)
		fwrite(&record, sizeof(record), 1, fp);
	
	fclose(fp);
	exit(0);
}

