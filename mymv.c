/*  This is an odg to bmp converter using expat.h library.
    Copyright (C) 2016  Ketan Girish Hukare
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
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
