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
#define h 317
#define w 230
typedef struct bmp {
	char *filename;
	int a[h][w];
} bmp;

/*typedef struct data_rectangle {
	char *filename;
	int x, y, width, height;
} data_rectangle;
*/
void make_line(bmp *ptr, int x1, int y1, int x2, int y2);
void make_rectangle(bmp *ptr, int width, int height, int x, int y);
void make_bmp(bmp *ptr);
void mymv(char *s, char *d);
