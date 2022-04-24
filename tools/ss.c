/**************************************************
 *
 * File: ss.c 
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 *
 * Format of resource input file:
 *
 * (X datatype) (c datatype)
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
	char extra[100];
	int  flag;
	int  i;
	FILE *out;

	/* input file */
	file = fopen("xtypes", "r");
	if (file == NULL){
		perror("problem with types input file");
		exit(-1);
	};

	/* output file */
	out = fopen("getsizes.c", "w");
	if (out == NULL){
		perror("problem with sizes output file");
		exit(-1);
	};

	fprintf(out,"/*\t\tProgram: ss - get sizes of datatypes */\n");
	fprintf(out,"/*\t\t\tProgram generated (ss) - any changes are lost */\n");
	fprintf(out,"#include <stdio.h>\n");
	fprintf(out,"#include <string.h>\n");
	fprintf(out,"#include <stdlib.h>\n");
	fprintf(out,"#include <Xm/Xm.h>\n");
	fprintf(out,"#include <X11/Intrinsic.h>\n");
	fprintf(out,"#include <X11/X.h>\n");

	fprintf(out,"int main(int argc, char *argv[])\n{\n");

	fprintf(out, "\tFILE *out;\n\n");
	fprintf(out, "\tout = fopen(\"tmpsizes\", \"w\");\n");
	fprintf(out, "\tif (out == NULL){\n");
	fprintf(out, "\t\tperror(\"problem with sizes output file\");\n");
	fprintf(out, "\t\texit(-1);\n");
	fprintf(out, "\t};\n\n");

	flag = fscanf(file, "%s", type);

	/* deal with 2 word types for the first variable */
	if (strcmp(type, "unsigned") == 0){
		strcat(type, " ");
		flag = fscanf(file, "%s", extra);
		strcat(type, extra);
	};

	while (flag != EOF){

		fprintf(out, "\tfprintf(out, \"%s\t%%d\\n\", (int)sizeof(%s));\n", type, type);

		flag = fscanf(file, "%s", type);

		/* deal with 2 word types */
		if (strcmp(type, "unsigned") == 0){
			strcat(type, " ");
			flag = fscanf(file, "%s", extra);
			strcat(type, extra);
		};

	};

	fprintf(out, "\n\tfclose(out);\n");
	fprintf(out,"\treturn (0);\n");
	fprintf(out,"}\n");

	fclose(file);

	return (0);

}
