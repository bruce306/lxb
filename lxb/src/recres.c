/**************************************************
*
* File: recres.c
*
*    Copyright (C) 1997  Bruce Parkin 
*
**************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "recres.h"

/**************************************************
 *
 * Function: re_record_resource
 *
 *	Find if the resource has been recorded already,
 *	and if so change only it's value in the list;
 *	else call "record_resource".
 *
 **************************************************/
void
re_record_resource(WSTRUCT *ptr, char *resource_name, char *resource_value, int enumlist)
{
	RES *rptr;
	Boolean found;

	found = False;
	rptr = ptr->resptr;

	if (verbose >6){

		if (rptr != NULL){
			printf("Searching changed resources of widget %s...\n", ptr->appname);
		};

	};

	while (rptr != NULL){
		
		if ( (strcmp(resource_name, rptr->name) == 0) ){
		
			found = True;
			
			/* replace with new values */
			strcpy(rptr->value, resource_value);

			if (verbose >6){
				printf("Search found resource name: %s and is changing to value: %s\n", 
								rptr->name, rptr->value);
			};

			break;
		};
		rptr = rptr->next;
	};

	if (!found)
		record_resource(ptr, resource_name, resource_value, enumlist);
}
/**************************************************
 *
 * Function: record_resource
 *
 *	NOTE:	all you have to do is start with the "ptr->resptr"
 *				(which points to a type RES with member "next")
 *				and walk down the rptr->next until it's "NULL",
 *				and you will have all the nodes.
 *
 **************************************************/
void
record_resource(WSTRUCT *ptr, char *resource_name, char *resource_value, int enumlist)
{
	RES *rptr;

	rptr = (RES *)XtMalloc(sizeof(RES));
	memset(rptr, 0, sizeof(RES));
	
	strcpy(rptr->name, resource_name);
	strcpy(rptr->value, resource_value);
	rptr->enumlist = enumlist;
	
	if (verbose >6) {
		printf("First time changing widget (%s) resource\n", ptr->appname);
		printf("    resource name: %s     value: %s\n", rptr->name, rptr->value);
	};

	rptr->next = ptr->resptr;
	ptr->resptr = rptr;

}
