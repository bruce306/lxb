/**************************************************
 *
 * File: code_hdr.c
 *
 *    Copyright (C) 1997  Bruce Parkin 
 *
 **************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "code_hdr.h"

/**************************************************
 *
 * Function: code_header_file
 *
 **************************************************/
int
code_header_file(FILE *file)
{
	WSTRUCT *ptr;

	fprintf(file, "/* external variables */\n");

	ptr = top_ptr;
	while (ptr != NULL){

		if (ptr->global){
			fprintf(file, "extern Widget %s;\n", ptr->appname);
		};
		ptr = ptr->last;
	};

	fprintf(file, "\n");

	return (OK);

}
