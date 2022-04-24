/**************************************************
 *
 * File: cvt.c 
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 *
 * Format of resource input file: (see cvt.h)
 *
 * (XmN{name})  (datatype)  (enum: 0 = no, >0 = enumlist) TBD: (Default)
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
	char name[100];
	char type[100];
	char  enum_no[100];
	int  flag;
	int  i;

	FILE *out;

	/* input file */
	file = fopen("xres", "r");
	if (file == NULL){
		perror("problem with resource input file");
		exit(-1);
	};

	/* output file */
	out = fopen("rstruct.h", "w");
	if (out == NULL){
		perror("problem with resource output file");
		exit(-1);
	};

	/* file header */
	fprintf(out,"\n");
	fprintf(out,"/*    File: rstruct.h    */\n");
	fprintf(out,"\n");

	/* data struct def */
	fprintf(out,"typedef struct _rstruct {\n");
	fprintf(out,"\tString resource_name;\n");
	fprintf(out,"\tString datatype;\n");
	fprintf(out,"\tString enumlist;\n");
	fprintf(out,"} RSTRUCT, *RSTRUCTLIST;\n");
	fprintf(out,"\n");

	/* fill in the data struct */
	fprintf(out,"static RSTRUCT rstruct[] = {\n");

	flag = fscanf(file, "%s%s%s", name, type, enum_no);

	if (strcmp(type, "unsigned") == 0){
		strcat(type, " ");
		strcat(type, enum_no);
		flag = fscanf(file, "%s", enum_no);
	};

	i = 0;
	while (flag != EOF){

		i++;

		fprintf(out, "\t{\"%s\",\t\"%s\",\t\"%s\"},\n", name, type, enum_no);

		flag = fscanf(file, "%s%s%s", name, type, enum_no);

		if (strcmp(type, "unsigned") == 0){
			strcat(type, " ");
			strcat(type, enum_no);
			flag = fscanf(file, "%s", enum_no);
		};
	};

	fprintf(out,"};\n");

	fprintf(out,"\nstatic int rstruct_count = %d;\n", i);

	fclose(file);

	return (0);

}
