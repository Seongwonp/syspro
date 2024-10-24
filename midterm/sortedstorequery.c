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
	struct storedata rec;
	FILE *fp;
	int op =0;
	if(argc !=2){
		fprintf(stderr,"How to use: %s FileName\n",argv[0]);
		return 1;
	}
	if((fp = fopen(argv[1],"rb")) == NULL){
		fprintf(stderr,"Error Open File\n");
		return 2;
	}

	printf("--Goods query--\n");
	printf("0: list of all goods, 1: list of available goods) ");
	scanf("%d",&op);

	printf("%3s %15s %8s %12s %5s\n", "id", "Name","category","expired date","stock");

	if(op ==1){
		 while(fread(&rec,sizeof(rec),1, fp)>0){
		 	if(rec.id !=0 && rec.expired_date>=2023 && rec.stock>0)
                 printf("%3d %15s %8s %12d %5d \n",rec.id, rec.name, rec.category, rec.expired_date, rec.stock);

		}
	}
	else{
		while(fread(&rec,sizeof(rec),1, fp)>0){
			if(rec.id !=0)
				printf("%3d %15s %8s %12d %5d \n",rec.id, rec.name, rec.category, rec.expired_date, rec.stock);
		}
	}
	
	
	fclose(fp);
	return 0;
}
