#include <stdio.h>
#include <string.h>
#define MAXLINE 80
int main(int argc, char *argv[]){
	FILE *fp;
	int c;
	int line_number = 1;
	int add_line_numbers = 0;

	 if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        add_line_numbers = 1;
        argc--;
        argv++;
    }


	if(argc<2)
		fp=stdin;
	else{
		for(int i=1; i<argc; i++){
		fp=fopen(argv[i],"r");
		if (fp == NULL)
			continue;
		}

	 while ((c = getc(fp)) != EOF) {
         if (c == '\n' && add_line_numbers) {
              printf("%d: ", line_number++);
             }
          putc(c, stdout);
        }
	fclose(fp);
	return 0;
}
}
