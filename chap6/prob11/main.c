#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>

void printStat(char*, struct stat*, int, int);
char *formatTime(time_t);
char *perm(mode_t);
// ls -l ls-i ls -s
int main(int argc, char **argv)
{
    DIR *dp;
    char *dir = ".";
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ + 1];
    int print_long = 0, print_inode = 0, print_size = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0)
            print_long = 1;
        else if (strcmp(argv[i], "-i") == 0)
            print_inode = 1;
        else if (strcmp(argv[i], "-s") == 0)
            print_size = 1;
        else if (argv[i][0] != '-')
            dir = argv[i];
    }

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        sprintf(path, "%s/%s", dir, d->d_name);
        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(path, &st, print_long, print_inode);

        if (print_inode)
            printf("Inode: %lu ", st.st_ino);
        if (print_size)
            printf("Size: %ld ", st.st_size);

 
        printf("%s\n", d->d_name);
    }

    closedir(dp);
    exit(0);
}

void printStat(char *pathname, struct stat *st, int print_long, int print_inode) {
    if (print_long) { 
        printf("%5ld ", st->st_blocks);
        printf("%c%s ", (S_ISDIR(st->st_mode) ? 'd' : '-'), perm(st->st_mode));
        printf("%3d ", st->st_nlink);
        printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
		printf("%lu ", st->st_ino);
        printf("%s ", formatTime(st->st_mtime));
    }
}

char *formatTime(time_t time) {
    static char buffer[50];
    struct tm *tm_info;

    tm_info = localtime(&time);
    strftime(buffer, 50, "%Y-%m-%d %H:%M", tm_info);
    return buffer;
}

char *perm(mode_t mode) {
    static char perms[10];
    strcpy(perms, "---------");

    if (mode & S_IRUSR) perms[0] = 'r';
    if (mode & S_IWUSR) perms[1] = 'w';
    if (mode & S_IXUSR) perms[2] = 'x';
    if (mode & S_IRGRP) perms[3] = 'r';
    if (mode & S_IWGRP) perms[4] = 'w';
    if (mode & S_IXGRP) perms[5] = 'x';
    if (mode & S_IROTH) perms[6] = 'r';
    if (mode & S_IWOTH) perms[7] = 'w';
    if (mode & S_IXOTH) perms[8] = 'x';

    return perms;
}

