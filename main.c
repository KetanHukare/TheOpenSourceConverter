#include <stdio.h>
#include <expat.h>
#include <string.h>
#if defined(__amigaos__) && defined(__USE_INLINE__)
#include <proto/expat.h>
#endif
#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif
#include"data.h"
float store[10];
bmp *imgptr;
	static void XMLCALL
startElement(void *userData, const char *name, const char **atts)
{
	int i = 0, j = 0;
	float val;
	char value[128], token[100], *convert, *convert1, *convert2, *convert3, *convert4;
	int *depthPtr = (int *)userData;
	if(!(strcmp(name, "draw:line"))) { 
		puts(name);
		while(atts[i] != NULL) {
			if(!((strcmp(atts[i], "svg:x1"))&&(strcmp(atts[i], "svg:y1")) && (strcmp(atts[i], "svg:x2")) && (strcmp(atts[i], "svg:y2")) )) {
				strcpy(value, atts[i+1]);
				convert = strtok(value, "c");
				strcpy(token, convert);
				val = atof(token);					
				store[j] = val * 10;
				j++;
			}
			i++;
		}
		make_line(imgptr, store[0], store[1], store[2], store[3]);
		for(j = 0; j < 4; j++)
			printf("%f\n", store[j]);
	}
	if(!(strcmp(name, "draw:custom-shape"))) {
		strcpy(value, atts[7]);
		strtok(value, "c");
		//strcpy(token, value);
		val = atof(value);
		store[0] = val * 10;
		strcpy(value, atts[9]);
		strtok(value, "c");
		//strcpy(token, convert2);
		val = atof(value);
		store[1] = val * 10;
		strcpy(value, atts[11]);
		strtok(value, "c");
		//strcpy(token, convert3);
		val = atof(value);
		store[2] = val * 10;
		strcpy(value, atts[13]);
		strtok(value, "c");
		//strcpy(token, convert4);
		val = atof(value);
		store[3] = val * 10;
	}
	if(!(strcmp(name, "draw:enhanced-geometry"))) {
		i = 0;
		while(atts[i] != NULL) {
			if(!(strcmp("draw:type", atts[i]))) {
				printf("%s\n", atts[i+1]);
				for(j = 0; j < 4; j++)
					printf("%f\n", store[j]);
				break;
			}
			i++;
		}
		if(!(strcmp("rectangle", atts[i + 1])))
			make_rectangle(imgptr, store[0], store[1], store[2], store[3]);
	}


	//  }		

	*depthPtr += 1;
}

	static void XMLCALL
endElement(void *userData, const char *name)
{
	int *depthPtr = (int *)userData;
	*depthPtr -= 1;
}

	int
main(int argc, char *argv[])
{
	char buf[BUFSIZ], *rename, name[128], rename1[50], file_unzip[55], file_zip[55], chartarget[128];
	FILE *fd, *fd1;
	fd = fopen(argv[1], "r");
	XML_Parser parser = XML_ParserCreate(NULL);
	int done;
	printf("test0\n");
	imgptr = (bmp *)malloc(sizeof(bmp));
	int depth = 0;
	XML_SetUserData(parser, &depth);
	strcpy(file_unzip,"unzip ");

	strcpy(name, argv[1]);
	rename = strtok(name, ".");
	strcpy(rename1, rename);
	strcat(rename1, ".zip");
	strcat(file_unzip, rename1);
	mymv(argv[1], rename1);
	system(file_unzip);
	//printf("test1\n");
	strcpy(chartarget, name);
	strcat(chartarget, "/");
	strcat(chartarget, "content.xml");
	//printf("test2\n");
	fd1 = fopen("content.xml", "r");
	//printf("test3\n");
	strcat(name, ".bmp");
	imgptr->filename = (char *)malloc(sizeof(strlen(name)+1));
	//printf("test4\n");
	strcpy(imgptr->filename, name);
	//printf("test5\n");
	XML_SetElementHandler(parser, startElement, endElement);
	do {
		int len = (int)fread(buf, 1, sizeof(buf), fd1);
		done = len < sizeof(buf);
		//	make_bmp(imgptr);
		if (XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR) {
			fprintf(stderr,
					"%s at line %" XML_FMT_INT_MOD "u\n",
					XML_ErrorString(XML_GetErrorCode(parser)),
					XML_GetCurrentLineNumber(parser));
			return 1;
		}
	} while (!done);
	XML_ParserFree(parser);
	return 0;
}
