/**************************************************
 *
 * File: scvt.c 
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 * Format of resource input file: (see scvt.h)
 *
 * (datatype)  (sizeof)
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**************************************************
 * Funcion: main
 **************************************************/
int 
main(int argc, char *argv[])
{
	FILE *file;
	char type[100];
	char extra[25];
	int  size;
	int  flag;
	int  i;

	FILE *out;

	/* input file */
	file = fopen("tmpsizes", "r");
	if (file == NULL){
		perror("problem with type sizes file\n");
		exit(-1);
	};

	/* output file */
	out = fopen("tsizes.h", "w");
	if (out == NULL){
		perror("problem with type sizes output file");
		exit(-1);
	};

	/* file header */
	fprintf(out,"\n");
	fprintf(out,"/*    File: tsizes.h    */\n");
	fprintf(out,"\n");

	/* data struct def */
	fprintf(out,"typedef struct _sstruct {\n");
	fprintf(out,"\tString datatype;\n");
	fprintf(out,"\tint size;\n");
	fprintf(out,"} SSTRUCT, *SSTRUCTLIST;\n");
	fprintf(out,"\n");

	/* fill in the data struct */
	fprintf(out,"static SSTRUCT sstruct[] = {\n");

	flag = fscanf(file, "%s", type);
	if (strcmp(type, "unsigned") == 0){
		strcat(type, " ");
		flag = fscanf(file, "%s", extra);
		strcat(type, extra);
	};

	flag = fscanf(file, "%d", &size);

	i = 0;
	while (flag != EOF){

		i++;

		fprintf(out, "\t{\"%s\",\t%d},\n", type, size);

		flag = fscanf(file, "%s", type);
		if (strcmp(type, "unsigned") == 0){
			strcat(type, " ");
			flag = fscanf(file, "%s", extra);
			strcat(type, extra);
		};

		flag = fscanf(file, "%d", &size);
	};

	fprintf(out,"};\n");

	fprintf(out,"\nstatic int sstruct_count = %d;\n", i);

	fclose(file);

	return (0);

}
