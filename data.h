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
