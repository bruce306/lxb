/**************************************************
*
* File: show_options.c
*
*    Copyright (C) 1997  Bruce Parkin 
*
**************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/List.h>

#include "lxb.h"
#include "ResourceEd.h"
#include "data.h"
#include "special.h"

#include "xenum.h"

#include "show_options.h"

/* local prototypes */
static void
show_special_list(char *name, char *value, int *enumlist);

static void
show_enums_list(char *name, char *value, int *enumlist);

/**************************************************
 *
 * Function: 
 *
 *	show possible selections in the bottom list widget
 *
 **************************************************/
void
show_options(char *resource_name, char *resource_value, int *enumlist)
{

	/* if there is an enumerated list, or conversions on the options, show them */
	if (*enumlist >=0) {

		show_enums_list(resource_name, resource_value, enumlist);

	}else if (*enumlist<0) {

		show_special_list(resource_name, resource_value, enumlist);

	};
}
/**************************************************
 *
 * Function: show_special_list
 *
 *	Get and display the available options for a "special"
 *	resource.
 *
 **************************************************/
static void
show_special_list(char *name, char *value, int *enumlist)
{
	int				i;
	XmString	*xmstrings;
	XmString	*xms;
	int				number;

	/* colornames, fonts, widget, conversions,,,, etc */
	xmstrings = get_special_resource(name, value, enumlist, &number);

	if (number == 0)
		return;

	/* clear the list */
	XmListDeleteAllItems(value_list);

	XmListAddItems(value_list, xmstrings, number, 1);

	xms = xmstrings;
	for (i=0; i<number; i++){
		XmStringFree(*xms);
		xms++;
	};

}
/**************************************************
 *
 * Function: show_enums_list
 *
 **************************************************/
static void
show_enums_list(char *name, char *value, int *enumlist)
{
	int				i;
	XmString	*xmstrings;
	XmString	*xms;
	ENUMSTRUCT *eptr;

	eptr = &(enum_unit[*enumlist]);

	/* normal enum types */
	xmstrings = (XmString *)XtCalloc(eptr->count, sizeof(ENUMUNIT));
	xms = xmstrings;

	for (i=0; i< eptr->count; i++){
		(*xms) = XmStringCreateSimple(eptr->unit[i].name);
		xms++;
	};

	XmListAddItems(value_list, xmstrings, eptr->count, 1);

	xms = xmstrings;
	for (i=0; i< eptr->count; i++){
		XmStringFree(*xms);
		xms++;
	};
}

