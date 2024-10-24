
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
	int id;
	FILE *fp;
	struct storedata rec;
	if(argc <2){
		fprintf(stderr,"How to use : %s file\n", argv[0]);
		exit(1);
	}
	if((fp = fopen(argv[1],"rb")) == NULL){
		fprintf(stderr,"Errer Open File\n");
		exit(2);
	}

		printf("(n): sell one goods ]");
		if(scanf("%d", &id) == 1){
			fseek(fp, (id-ID)*sizeof(rec), SEEK_SET);
			if((fread(&rec, sizeof(rec),1,fp)>0) && (rec.id !=0) && (rec.stock !=0)){
				printf("'%12s' (%d) has been sold..\n",rec.name,rec.stock);
				rec.stock--;
				fseek(fp,-sizeof(rec), SEEK_CUR);
				fwrite(&rec, sizeof(rec),1,fp);

			}
			else{
				printf("'%12s' has been sold out...(There is no stock)\n",rec.name);
			}
			printf("%3s %15s %8s %12s %5s\n", "id", "Name","category","expired date","stock");
                  while(fread(&rec,sizeof(rec),1, fp)>0){
                      if(rec.id !=0)
                          printf("%3d %15s %8s %12d %5d \n",rec.id, rec.name, rec.category, rec.expired_date, rec.stock);
		
				  } 
		}
		else
			printf("Insert Error\n");
	fclose(fp);
	exit(0);
}


