#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLS 100
int main(int argc, char *argv[]){
	char savedText[MAX_ROWS][MAX_COLS];
	int fd;
	if(argc<2){
		fprintf(stderr,"How to use: %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDONLY)) == -1){
		perror(argv[1]);
		exit(2);
	}
		
	
	char buf;
	int row =0, col = 0;
	while(read(fd, &buf,  1) >0){
			if(row >= MAX_ROWS)
				break;
			if(buf == '\n'){
				savedText[row][col] = '\0';
				row++;
				col = 0;
			}
			else{
				savedText[row][col] = buf;
				col++;
				if(col >=MAX_COLS)
					col = MAX_COLS-1;
			}
		}
	
	printf("File read success\n");
	printf("Total line : %d\n",row);
	printf("You can choose 1~%d Line\n",row);
    printf("Pls 'Enter' the line to select : ");
	char input[21];
	
	scanf("%20s", input);
	//all text
	if(strcmp(input,"*") == 0){
		for (int i =0; i<row; i++)
			printf("%s\n", savedText[i]);
	}
	
	else{
	
		//n-m used sscanf
		if(strchr(input,'-')!=NULL){
			int start,end;
			sscanf(input,"%d-%d", &start,&end);
			if(start <1 || end<start || end >row){
				printf("Invalid range : %d-%d\n", start, end);
				exit(2);
			}
			for(int i = start-1; i<=end-1 && i<row; i++)
				printf("%s\n", savedText[i]);
		}
		else{
			// n / n,.....,m 
			int lineNum[MAX_ROWS];
			int count=0;
			
			char *token = strtok(input,",");
			while (token != NULL){
				int line = atoi(token);
				if(line >=1 && line<=row){
					lineNum[count++] = line;
				}
				token = strtok(NULL,",");
			}
			//n
			if(count ==1)
				printf("%s\n", savedText[lineNum[0]-1]);
			//n,...,m
			else{
			for(int i=0; i<count; i++)
				printf("%s\n", savedText[lineNum[i]-1]);
			}
		}
	}


	close(fd);
	exit(0);
}

