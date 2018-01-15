/***************************************************
*
* File: misc.c - routines to get info from the files
*		created by hand.
*
*    Copyright (C) 1997  Bruce Parkin 
*
**************************************************/

/* include files */
#include <stdio.h>
#include <stdlib.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "color.h"
#include "data.h"
#include "dump.h"
#include "misc.h"

/* the lookup struct for resource datatypes */
#include "rstruct.h"

/* the lookup struct for the sizes of the datatypes */
#include "tsizes.h"

/* lookup of for enum types */
#include "xenum.h"

/**************************************************
 *
 * Function: get_enum_type
 *
 **************************************************/
int
get_enum_number(int *enumlist, char *enum_name)
{
	int count;
	int i;
	int	number = -1;

	/* the number of enums in the array */
	count = enum_unit[*enumlist].count;

	/* get the enum Motif value */
	for (i=0; i<count; i++){
																														
		if ( strcmp(enum_unit[*enumlist].unit[i].name, enum_name) == 0 ){
				number = enum_unit[*enumlist].unit[i].number;
			break;
		};
				
	};
	return (number);
}
/**************************************************
 *
 *	Function: get_datatype_index
 *
 *	lookup in file:	tsizes.h
 *
 **************************************************/
int
get_datatype_index(char *datatype)
{
	int i;
	int	index;

	index = -1;

	for (i=0;i<sstruct_count; i++){

		if (strcmp(sstruct[i].datatype, datatype) == 0){
			index = i;
			break;
		};

	};

	if (index == -1)
			fprintf(stderr, "get_datatype_index: entry does not exist for datatype: %s\n", datatype);

	if (verbose >8){
		printf("get_datatype_index: datatype index: (%d)\n", index);
	};

	return (index);

}
/**************************************************
 *
 *	Function: get_datatype
 *
 *	Take the given resource name, lookup the Xm
 *	type in "rstruct.h"
 *
 **************************************************/
char *
get_datatype(char *ptr, int *enumlist)
{
	int		i;
	char 	*name = NULL;
	char 	*tmp = NULL;

	for (i=0;i<rstruct_count; i++){

		if (strcmp(ptr, rstruct[i].resource_name) == 0){
			name = rstruct[i].datatype;
			tmp = rstruct[i].enumlist;
			*enumlist = atoi(tmp);
			break;
		};

	};

	if (name == NULL){
		fprintf(stderr, "get_datatype: entry does not exist for resource: (%s)\n", ptr);
	};

	if (verbose >8)
		printf("get_datatype:  enumlist = (%s)  datatype = (%s)\n", tmp, name);

	return (name);
}
/**************************************************
 *
 * Function: get_enum_type
 *
 *	This will take the "enumlist" (the specific group of
 *	enum types) and the "number" (the specific number that
 *	is the actual value for the resource and also the 
 *	indentifier of the enum type) and return the string
 *	representation of the enum type (ie, "XmNONE").
 *
 **************************************************/
char *
get_enum_type(int *enumlist, int *number, char *buf)
{
	int count;
	int i;

	/* the number of enums in the array */
	count = enum_unit[*enumlist].count;

	/* get the enum Motif value */
	for (i=0; i<count; i++){
																														
		if ( (enum_unit[*enumlist].unit[i].number == *number) ){
			strcpy(buf, enum_unit[*enumlist].unit[i].name);
			break;
		};
				
	};
	return (buf);
}
