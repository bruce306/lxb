/***************************************************
 * File: id_resource.c
 *
 *    Copyright (C) 1997  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <stdlib.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "misc.h"
#include "id_resource.h"

/**************************************************
 *
 * Function: id_resource
 *
 *	Input: resource name (ie, "traversal", not "XmNtraversal" )
 *
 *	Returns: 
 *		- the "index" into the struct in tsizes.h,
 *		- the "enumlist" and string representation of datatype
 *		 	from rstruct.h
 *
 *	NOTES:
 * 		"enumlist" - indicates type of resource
 *		"index"    - allows finding size of datatype from file
 *
 **************************************************/
int
id_resource(char *ptr, int *enumlist, int *index)
{
	char			*datatype;
	int				status;

	if (verbose > 8)
		printf("id_resource: resource name: (%s)\n", ptr);

	status = OK;

	/* get string name of datatype, and enumlist */
	datatype = get_datatype(ptr, enumlist);

	if (datatype == NULL){

		status = NOTOK;

	} else {

		/* get index of named datatype */
		*index = get_datatype_index(datatype);

		if (*index == -1)
			status = NOTOK;
	};

	if (status == NOTOK)
		fprintf(stderr, "id_resource failed\n");

	return (status);
}
