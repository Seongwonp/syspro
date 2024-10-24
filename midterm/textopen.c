#include <stdio.h>
#include <string.h>
#define MAXLINE 80

int main(int argc, char *argv[]){
    FILE *fp;
    int c;
	int option = 1;
    int line_number = 0;

    if (argc < 2) {
        fp = stdin;
    } else {
        for (int i = 1; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL)
                continue;

            while ((c = getc(fp)) != EOF) {
                putc(c, stdout);
                if (c == '\n') {
                   		line_number++;
					if(option){
						if(line_number == 2)
							break;
					}
                }
            }

            fclose(fp);
        }
    }
    return 0;
}

