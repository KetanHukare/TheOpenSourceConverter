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
#include<stdlib.h>
#include"data.h"
void make_bmp(bmp *ptr){
	FILE *fp;
	fp;
	if((fp=fopen(ptr->filename ,"wb+"))==NULL) {
		printf("error to open c:\\a.bmp!");
		exit(1);
	}

	struct Bimap_File_Header {
		unsigned short bftype; 
		unsigned long bfsize; 
		unsigned short bfreserved1;
		unsigned short bfreserved2;
		unsigned long bfoffbits; 
	} bfh;

	bfh.bftype=0x4d42; //this tells image is BMP

	bfh.bfreserved1=0;
	bfh.bfreserved2=0;
	bfh.bfoffbits=0x3e;

	struct Bitmap_File_Info_Header {
		unsigned long bfihsize;
		unsigned long width;   
		unsigned long height;  
		unsigned short biplanes; 
		unsigned short bibitcount;
		unsigned long bicompression;
		unsigned long bisizeimage;
		unsigned long bixpelspermeter;
		unsigned long biypelspermeter;
		unsigned long biclrused;
		unsigned long biclrimportant;
	} bfih;

	bfih.bfihsize=0x28;
	bfih.width=w;
	bfih.height=h;
	bfih.biplanes=1;
	bfih.bibitcount=1;
	bfih.bicompression=0;
	bfih.bisizeimage=(w/32*4+(w%32?4:0))*h;
	bfih.bixpelspermeter=0;
	bfih.biypelspermeter=0;
	bfih.biclrused=0;
	bfih.biclrimportant=0;

	bfh.bfsize=0x36+8+bfih.bisizeimage;

	fwrite(&bfh.bftype,2,1,fp);
	fwrite(&bfh.bfsize,4,1,fp);
	fwrite(&bfh.bfreserved1,2,1,fp);
	fwrite(&bfh.bfreserved2,2,1,fp);
	fwrite(&bfh.bfoffbits,4,1,fp);

	fwrite(&bfih.bfihsize,4,1,fp);
	fwrite(&bfih.width,4,1,fp);
	fwrite(&bfih.height,4,1,fp);
	fwrite(&bfih.biplanes,2,1,fp);
	fwrite(&bfih.bibitcount,2,1,fp);
	fwrite(&bfih.bicompression,4,1,fp);
	fwrite(&bfih.bisizeimage,4,1,fp);
	fwrite(&bfih.bixpelspermeter,4,1,fp);
	fwrite(&bfih.biypelspermeter,4,1,fp);
	fwrite(&bfih.biclrused,4,1,fp);
	fwrite(&bfih.biclrimportant,4,1,fp);

	struct RGB {
		unsigned short Blue;
		unsigned short Green;
		unsigned short Red;
		unsigned short Reserved;
	} rgb0,rgb1;

	rgb0.Blue=0xff;
	rgb0.Green=0xff;
	rgb0.Red=0xff;
	rgb0.Reserved=0;

	rgb1.Blue=0x00;
	rgb1.Green=0x00;
	rgb1.Red=0x00;
	rgb1.Reserved=0;

	fwrite(&rgb0.Blue,1,1,fp);
	fwrite(&rgb0.Green,1,1,fp);
	fwrite(&rgb0.Red,1,1,fp);
	fwrite(&rgb0.Reserved,1,1,fp);
	fwrite(&rgb1.Blue,1,1,fp);
	fwrite(&rgb1.Green,1,1,fp);
	fwrite(&rgb1.Red,1,1,fp);
	fwrite(&rgb1.Reserved,1,1,fp);

	int i,j,k=0,n=0,m=0,c,b[32];

	for(i=h-1;i>=0;i--,j=0) {
		if(w%32==0) {
			for(j=0;j<w;j++) {
				k=ptr->a[i][j]+k*2;
				m++;
				if(m%8==0) {
					fwrite(&k,1,1,fp);
					k=0;
					m=0;
				}

			}
		}

		else {
			if(w>=32) {
				n=w%32;
				for(j=0;j<w-n;j++) {
					k=ptr->a[i][j]+k*2;
					m++;
					if(m%8==0) {
						fwrite(&k,1,1,fp);
						k=0;
						m=0;
					}
				}


				for(c=0;c<32;c++,j++) {
					if(j<w)
						b[c]=ptr->a[i][j];
					else
						b[c]=0;
				}


				for(c=0;c<32;c++) {
					k=b[c]+k*2;
					m++;
					if(m%8==0) {
						fwrite(&k,1,1,fp);
						k=0;
						m=0;
					}
				}

			}
			else {
				for(c=0;c<32;c++,j++) {
					if(j<w)
						b[c]=ptr->a[i][j];
					else
						b[c]=0;
				}


				for(c=0;c<32;c++) {
					k=b[c]+k*2;
					m++;
					if(m%8==0) {
						fwrite(&k,1,1,fp);
						k=0;
						m=0;
					}
				}
			}

		}
	}

	fclose(fp);
	//    return 0;
}

void make_line(bmp *ptr, int x1, int y1, int x2, int y2) {
	int i, j, k=0,n=0,m=0,c,b[32];
	FILE *fp;
	fp = fopen(ptr->filename, "wb+");
	struct Bimap_File_Header {
		unsigned short bftype; 
		unsigned long bfsize; 
		unsigned short bfreserved1;
		unsigned short bfreserved2;
		unsigned long bfoffbits; 
	} bfh;

	bfh.bftype=0x4d42; //this tells image is BMP

	bfh.bfreserved1=0;
	bfh.bfreserved2=0;
	bfh.bfoffbits=0x3e;

	struct Bitmap_File_Info_Header {
		unsigned long bfihsize;
		unsigned long width;   
		unsigned long height;  
		unsigned short biplanes; 
		unsigned short bibitcount;


		unsigned long bicompression;
		unsigned long bisizeimage;
		unsigned long bixpelspermeter;
		unsigned long biypelspermeter;
		unsigned long biclrused;
		unsigned long biclrimportant;
	} bfih;

	bfih.bfihsize=0x28;
	bfih.width=w;
	bfih.height=h;
	bfih.biplanes=1;
	bfih.bibitcount=1;
	bfih.bicompression=0;
	bfih.bisizeimage=(w/32*4+(w%32?4:0))*h;
	bfih.bixpelspermeter=0;
	bfih.biypelspermeter=0;
	bfih.biclrused=0;
	bfih.biclrimportant=0;

	bfh.bfsize=0x36+8+bfih.bisizeimage;

	fwrite(&bfh.bftype,2,1,fp);
	fwrite(&bfh.bfsize,4,1,fp);
	fwrite(&bfh.bfreserved1,2,1,fp);
	fwrite(&bfh.bfreserved2,2,1,fp);
	fwrite(&bfh.bfoffbits,4,1,fp);

	fwrite(&bfih.bfihsize,4,1,fp);
	fwrite(&bfih.width,4,1,fp);
	fwrite(&bfih.height,4,1,fp);
	fwrite(&bfih.biplanes,2,1,fp);
	fwrite(&bfih.bibitcount,2,1,fp);
	fwrite(&bfih.bicompression,4,1,fp);
	fwrite(&bfih.bisizeimage,4,1,fp);
	fwrite(&bfih.bixpelspermeter,4,1,fp);
	fwrite(&bfih.biypelspermeter,4,1,fp);
	fwrite(&bfih.biclrused,4,1,fp);
	fwrite(&bfih.biclrimportant,4,1,fp);

	struct RGB {
		unsigned short Blue;
		unsigned short Green;
		unsigned short Red;
		unsigned short Reserved;
	} rgb0,rgb1;

	rgb0.Blue=0xff;
	rgb0.Green=0xff;
	rgb0.Red=0xff;
	rgb0.Reserved=0;

	rgb1.Blue=0x00;
	rgb1.Green=0x00;
	rgb1.Red=0x00;
	rgb1.Reserved=0;

	fwrite(&rgb0.Blue,1,1,fp);
	fwrite(&rgb0.Green,1,1,fp);
	fwrite(&rgb0.Red,1,1,fp);
	fwrite(&rgb0.Reserved,1,1,fp);
	fwrite(&rgb1.Blue,1,1,fp);
	fwrite(&rgb1.Green,1,1,fp);
	fwrite(&rgb1.Red,1,1,fp);
	fwrite(&rgb1.Reserved,1,1,fp);

	for(i = y1; i <= y2; i++) {
		for(j = x1; j <= x2; j++) {
			ptr->a[i][j] = 1;
		}
	}

	for(i=h-1;i>=0;i--,j=0) {
		if(w%32==0) {
			for(j=0;j<w;j++) {
				k=ptr->a[i][j]+k*2;
				m++;
				if(m%8==0) {
					fwrite(&k,1,1,fp);
					k=0;
					m=0;
				}

			}
		}

		else {
			if(w>=32) {
				n=w%32;
				for(j=0;j<w-n;j++) {
					k=ptr->a[i][j]+k*2;
					m++;
					if(m%8==0) {
						fwrite(&k,1,1,fp);
						k=0;
						m=0;
					}
				}


				for(c=0;c<32;c++,j++) {
					if(j<w)
						b[c]=ptr->a[i][j];
					else
						b[c]=0;
				}


				for(c=0;c<32;c++) {
					k=b[c]+k*2;
					m++;
					if(m%8==0) {
						fwrite(&k,1,1,fp);
						k=0;
						m=0;
					}
				}

			}
			else {
				for(c=0;c<32;c++,j++) {
					if(j<w)
						b[c]=ptr->a[i][j];
					else
						b[c]=0;
				}


				for(c=0;c<32;c++) {
					k=b[c]+k*2;
					m++;
					if(m%8==0) {
						fwrite(&k,1,1,fp);
						k=0;
						m=0;
					}
				}
			}


		}
	}

	fclose(fp);
}

void make_rectangle(bmp *ptr, int width, int height, int y, int x) {
	int i, j, k=0,n=0,m=0,c,b[32];
	FILE *fp;
	fp = fopen(ptr->filename, "wb+");
	struct Bimap_File_Header {
		unsigned short bftype; 
		unsigned long bfsize; 
		unsigned short bfreserved1;
		unsigned short bfreserved2;
		unsigned long bfoffbits; 
	} bfh;

	bfh.bftype=0x4d42; //this tells image is BMP

	bfh.bfreserved1=0;
	bfh.bfreserved2=0;
	bfh.bfoffbits=0x3e;

	struct Bitmap_File_Info_Header {
		unsigned long bfihsize;
		unsigned long width;   
		unsigned long height;  
		unsigned short biplanes; 
		unsigned short bibitcount;


		unsigned long bicompression;
		unsigned long bisizeimage;
		unsigned long bixpelspermeter;
		unsigned long biypelspermeter;
		unsigned long biclrused;
		unsigned long biclrimportant;
	} bfih;

	bfih.bfihsize=0x28;
	bfih.width=w;
	bfih.height=h;
	bfih.biplanes=1;
	bfih.bibitcount=1;
	bfih.bicompression=0;
	bfih.bisizeimage=(w/32*4+(w%32?4:0))*h;
	bfih.bixpelspermeter=0;
	bfih.biypelspermeter=0;
	bfih.biclrused=0;
	bfih.biclrimportant=0;

	bfh.bfsize=0x36+8+bfih.bisizeimage;

	fwrite(&bfh.bftype,2,1,fp);
	fwrite(&bfh.bfsize,4,1,fp);
	fwrite(&bfh.bfreserved1,2,1,fp);
	fwrite(&bfh.bfreserved2,2,1,fp);
	fwrite(&bfh.bfoffbits,4,1,fp);

	fwrite(&bfih.bfihsize,4,1,fp);
	fwrite(&bfih.width,4,1,fp);
	fwrite(&bfih.height,4,1,fp);
	fwrite(&bfih.biplanes,2,1,fp);
	fwrite(&bfih.bibitcount,2,1,fp);
	fwrite(&bfih.bicompression,4,1,fp);
	fwrite(&bfih.bisizeimage,4,1,fp);
	fwrite(&bfih.bixpelspermeter,4,1,fp);
	fwrite(&bfih.biypelspermeter,4,1,fp);
	fwrite(&bfih.biclrused,4,1,fp);
	fwrite(&bfih.biclrimportant,4,1,fp);

	struct RGB {
		unsigned short Blue;
		unsigned short Green;
		unsigned short Red;
		unsigned short Reserved;
	} rgb0,rgb1;

	rgb0.Blue=0xff;
	rgb0.Green=0xff;
	rgb0.Red=0xff;
	rgb0.Reserved=0;

	rgb1.Blue=0x00;
	rgb1.Green=0x00;
	rgb1.Red=0x00;
	rgb1.Reserved=0;

	fwrite(&rgb0.Blue,1,1,fp);
	fwrite(&rgb0.Green,1,1,fp);
	fwrite(&rgb0.Red,1,1,fp);
	fwrite(&rgb0.Reserved,1,1,fp);
	fwrite(&rgb1.Blue,1,1,fp);
	fwrite(&rgb1.Green,1,1,fp);
	fwrite(&rgb1.Red,1,1,fp);
	fwrite(&rgb1.Reserved,1,1,fp);

	for(i = x, j = y; i < (x + height); i++)
		ptr->a[i][j] = 1;
	for(j = y, i = x; j < (y + width); j++)
		ptr->a[i][j] = 1;
	for(i = x, j = (y + width); i < (x + height); i++)
		ptr->a[i][j] = 1;
	for(i = (x + height), j = y; j < (y + width); j++)
		ptr->a[i][j] = 1;

	for(i=h-1;i>=0;i--,j=0) {
		if(w%32==0) {
			for(j=0;j<w;j++) {
				k=ptr->a[i][j]+k*2;
				m++;
				if(m%8==0) {
					fwrite(&k,1,1,fp);
					k=0;
					m=0;
				}

			}
		}

		else {
			if(w>=32) {
				n=w%32;
				for(j=0;j<w-n;j++) {
					k=ptr->a[i][j]+k*2;
					m++;
					if(m%8==0) {
						fwrite(&k,1,1,fp);
						k=0;
						m=0;
					}
				}


				for(c=0;c<32;c++,j++) {
					if(j<w)
						b[c]=ptr->a[i][j];
					else
						b[c]=0;
				}


				for(c=0;c<32;c++) {
					k=b[c]+k*2;
					m++;
					if(m%8==0) {
						fwrite(&k,1,1,fp);
						k=0;
						m=0;
					}
				}

			}
			else {
				for(c=0;c<32;c++,j++) {
					if(j<w)
						b[c]=ptr->a[i][j];
					else
						b[c]=0;
				}


				for(c=0;c<32;c++) {
					k=b[c]+k*2;
					m++;
					if(m%8==0) {
						fwrite(&k,1,1,fp);
						k=0;
						m=0;
					}
				}
			}


		}
	}

	fclose(fp);
}
