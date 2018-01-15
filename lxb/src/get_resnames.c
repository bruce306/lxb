/***************************************************
 * File: get_resnames.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "dump.h"
#include "get_resnames.h"

/**************************************************
 *
 *	Function: get_resources
 *
 *	get regular resources
 *
 **************************************************/
void
get_resources(Widget w, ALLLIST *resources, Cardinal *no_resources)
{
	XtResourceList resource_list;
	XtResource *ptr;
	Cardinal num_resources;
	int i;
	ALLLIST rlist;
	char tmp[100];

	*no_resources = 0;
	
	XtGetResourceList(XtClass(w), &resource_list, &num_resources);

	if (num_resources >0) {

		/* count the number of callbacks */
		ptr = resource_list;
		for (i=0; i<num_resources; i++){

			if ( strcmp(ptr->resource_type, "Callback") == 0 ){
			}else 
				(*no_resources)++;
			ptr++;
		};

		/* allocate lists */

		*resources = (ALLLIST)XtCalloc(*no_resources, sizeof(ALL) );

		/* fill lists */
		rlist = *resources;

		ptr = resource_list;
		for (i=0; i<num_resources; i++){

			if ( strcmp(ptr->resource_type, "Callback") == 0 ){

			} else {

				/* make the actual name */
				strcpy(tmp, "XmN");
				strcat(tmp, ptr->resource_name);
				rlist->name = XtNewString(tmp);
				rlist->type = ptr->resource_type;
				rlist->size = (int)ptr->resource_size;
				rlist++;
			};

			ptr++;
		};
	
		if (verbose >6)
			dump_resources(w, no_resources, resources);

		XtFree((char *)resource_list);
	};
}	
/**************************************************
 *
 *	Function: get_constraints
 *
 *	get constraint resources
 *
 **************************************************/
void
get_constraints(Widget w, ALLLIST *constraints, Cardinal *no_constraints)
{

	XtResourceList resource_list;
	XtResource *ptr;
	Cardinal num_resources;
	int i;
	ALLLIST clist;
	char tmp[100];

	*no_constraints = 0;
	
	XtGetConstraintResourceList(XtClass(XtParent(w)), &resource_list, &num_resources);

	if (num_resources >0) {

		*no_constraints = num_resources;

		/* allocate lists */
		*constraints = (ALLLIST)XtCalloc(*no_constraints, sizeof(ALL) );

		/* fill lists */
		clist = *constraints;
		ptr = resource_list;
		for (i=0; i<num_resources; i++){

			/* make the actual name */
			strcpy(tmp, "XmN");
			strcat(tmp, ptr->resource_name);
			clist->name = XtNewString(tmp);
			clist->type= XtNewString(ptr->resource_type);
			clist->size = (int)ptr->resource_size;
			clist++;

			ptr++;
		};
		
		if (verbose >6) 
			dump_constraint_names(XtParent(w), no_constraints, constraints);

		XtFree((char *)resource_list);
	};
}	
/**************************************************
 *
 *	Function: get_callbacks
 *
 *	get callback resources
 *
 **************************************************/
void
get_callbacks(Widget w, ALLLIST *callbacks, Cardinal *no_callbacks)
{
	XtResourceList resource_list;
	XtResource *ptr;
	Cardinal num_resources;
	int i;
	ALLLIST	clist;
	char tmp[100];

	*no_callbacks = 0;
	
	XtGetResourceList(XtClass(w), &resource_list, &num_resources);

	if (num_resources >0) {

		/* count the number of callbacks */
		ptr = resource_list;
		for (i=0; i<num_resources; i++){

			if ( strcmp(ptr->resource_type, "Callback") == 0 )
				(*no_callbacks)++;

			ptr++;
		};

		/* allocate list */
		*callbacks = (ALLLIST)XtCalloc(*no_callbacks, sizeof(ALL) );

		/* fill lists */
		clist = *callbacks;

		ptr = resource_list;
		for (i=0; i<num_resources; i++){

			if ( strcmp(ptr->resource_type, "Callback") == 0 ){

				/* make the actual name */
				strcpy(tmp, "XmN");
				strcat(tmp, ptr->resource_name);
				clist->name = XtNewString(tmp);
				clist->type= XtNewString(ptr->resource_type);

				clist->size = (int)ptr->resource_size;
				clist++;

			};

			ptr++;
		};

		/* for debug - TBD */
		if (verbose >6)
			dump_callbacks();
	
		XtFree((char *)resource_list);
	};
}	
