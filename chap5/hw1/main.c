#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_ROWS 10
#define MAX_COLS 100
int main(int argc, char *argv[]){
	char savedText[MAX_ROWS][MAX_COLS];
	int fd;
	if((fd = open(argv[1], O_RDONLY)) == -1)
		printf("File Open Error\n");
	
	char buf;
	int row =0, col = 0;
	while(Read(fd, &buf,  1) >0){
			Read(fd,&buf,1);
			saveText[row][col]= buf;
			col++;
			if(buf == '\n')
				row++;
		}

	printf("File read success\n");
	printf("Total line : %d\n",row+1);
	printf("You can choose 1~%d Line\n",row+1);
    printf("Pls 'Enter' the line to select : ");
	
	


