#include <stdio.h>
#include <stdlib.h>
#define w 300
#define h 300

int main() {

    FILE *fp;
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
    bfih.biclrimportant=0; //every color is imp

    bfh.bfsize=0x36+8+bfih.bisizeimage;

    if((fp=fopen("a.bmp","wb+"))==NULL) {
    
        printf("error to open c:\\a.bmp!");
        exit(1);
    }

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

    int a[h][w],i,j,k=0,n=0,m=0,c,b[32];

/* sample for a cross 

    for(i=0;i<h;i++) {
            for(j=0;j<w;j++) {
        	if(j==i||i+j==w-1) {
        	    	a[i][j]=1;
            }
            else {
                a[i][j]=0;
            }
        }
    }



    for(i=h-1;i>=0;i--,j=0) {
            if(w%32==0)
        {
         for(j=0;j<w;j++) {
                k=a[i][j]+k*2;
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
              		for(j=0;j<w-n;j++)
                }
                k=a[i][j]+k*2;
                m++;
                if(m%8==0) {
                    fwrite(&k,1,1,fp);
                    k=0;
                    m=0;
                }
              }


              for(c=0;c<32;c++,j++) {
                if(j<w)
                b[c]=a[i][j];
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
                		b[c]=a[i][j];
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



  */

	

    fclose(fp);






    return 0;
}
