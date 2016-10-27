#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#define NUM 100000

void mymv(char *s, char *d) {
	int fd1, fd2, count, buf[NUM];
	fd1 = open(s, O_RDONLY);
	
	fd2 = open(d, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXG | S_IRWXU | S_IRWXO);
	
	
	while((count = read(fd1, buf, NUM)) > 0) {
		write(fd2, buf, count);
		close(fd1);
		close(fd2);
	}	
	
}
