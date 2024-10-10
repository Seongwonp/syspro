#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
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
			if(row > MAX_ROWS)
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
	for(int i = row-1; i>=0; i--)
		printf("%s\n",savedText[i]);
	
	close(fd);
	exit(0);
}
