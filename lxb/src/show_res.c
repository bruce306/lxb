/**************************************************
*
* File: show_resources.c
*
*    Copyright (C) 1997  Bruce Parkin 
*
* 	file for getting and displaying the strings in
*		the top scrolled list - the resource names of
*		standard, callback, and constraint resources.
*
**************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/List.h>

#include "lxb.h"
#include "ResourceEd.h"
#include "get_resnames.h"
#include "show_res.h"

/**************************************************
 *
 * Function: show_resources
 *
 * display resource names in the list widget
 *
 **************************************************/
void
show_resources()
{
	int				i;
	XmString	*xmstrings;
	XmString	*xms;
	ALLLIST		res_ptr;
	Cardinal  no_resources;
	ALLLIST   resources;
                                 
	/* get names and other info */

	get_resources(selected_widget, &resources, &no_resources);

	xmstrings = (XmString *)XtCalloc(no_resources, sizeof(XmString));

	xms = xmstrings;
	res_ptr = resources;
	for (i=0; i< no_resources; i++){

		(*xms) = XmStringCreateSimple(res_ptr->name);

		xms++;
		res_ptr++;
	};

	/* clear the lists */
	XmListDeleteAllItems(name_list);
	XmListDeleteAllItems(value_list);

	/* clear the text "value" widget */
	XmTextSetString(value_text, "");

	XmListAddItems(name_list, xmstrings, no_resources, 1);

	xms = xmstrings;
	for (i=0; i< no_resources; i++){
		XmStringFree(*xms);
		xms++;
	};

	resource_type = RESOURCES;
}
/**************************************************
 *
 * Function: show_callbacks
 *
 *	Display the callbacks in the resource list widget
 *
 **************************************************/
void
show_callbacks()
{
	int				i;
	XmString	*xmstrings;
	XmString	*xms;
	ALLLIST		cptr;
	ALLLIST   callbacks;
	Cardinal  no_callbacks;
                                 
	/* get names and other info */

	get_callbacks(selected_widget, &callbacks, &no_callbacks);

	xmstrings = (XmString *)XtCalloc(no_callbacks, sizeof(XmString));

	xms = xmstrings;
	cptr = callbacks;
	for (i=0; i< no_callbacks; i++){

		(*xms) = XmStringCreateSimple(cptr->name);

		xms++;
		cptr++;
	};

	/* clear the lists */
	XmListDeleteAllItems(name_list);
	XmListDeleteAllItems(value_list);

	/* clear the text value */
	XmTextSetString(value_text, "");

	XmListAddItems(name_list, xmstrings, no_callbacks, 1);

	xms = xmstrings;
	for (i=0; i< no_callbacks; i++){
		XmStringFree(*xms);
		xms++;
	};

	resource_type = CALLBACKS;
}
/**************************************************
 *
 * Function: show_constraints
 *
 *	Display the constraints in the resource list widget
 *
 **************************************************/
void
show_constraints()
{
	int				i;
	XmString	*xmstrings;
	XmString	*xms;
	ALLLIST		cptr;
	ALLLIST   constraints;
	Cardinal  no_constraints;
                                 
	/* get names and other info */

	get_constraints(selected_widget, &constraints, &no_constraints);

	xmstrings = (XmString *)XtCalloc(no_constraints, sizeof(XmString));

	xms = xmstrings;
	cptr = constraints;
	for (i=0; i< no_constraints; i++){

		(*xms) = XmStringCreateSimple(cptr->name);

		xms++;
		cptr++;
	};

	/* clear the lists */
	XmListDeleteAllItems(name_list);
	XmListDeleteAllItems(value_list);

	/* clear the text value */
	XmTextSetString(value_text, "");

	XmListAddItems(name_list, xmstrings, no_constraints, 1);

	xms = xmstrings;
	for (i=0; i< no_constraints; i++){
		XmStringFree(*xms);
		xms++;
	};

	resource_type = CONSTRAINTS;
}
