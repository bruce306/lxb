/**************************************************
 * File: special.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>

#include "lxb.h"
#include "color.h"
#include "data.h"
#include "special.h"

/* local prototypes */
static void *
get_siblings(void *dummy, int *number);

static XmString *
copy_colornames(void *dummy, int *number);

static XmString *
get_fonts(void *dummy, int *number);

/**************************************************
 *
 * Function: get_special_resource
 *
 *	Get the list of options available to a "special"
 *	resource.
 *
 *	Returns:
 *		a XmString list of names for display in a List
 *		no_xmstrings: number of XmStrings returned
 *
 *	Inputs:
 *
 *	name:			X resource name 
 *	value:		X resource value
 *	enumlist:	indicates class of X resource for this program
 *
 **************************************************/
XmString *
get_special_resource(char *name, char *value, int *enumlist, int *no_xmstrings)
{
	XmString		*xmstrings;
	int					number;
	void 				*dummy;

	if (verbose >6)
		printf("get_special_resource\n");

	number = 0;
	xmstrings = NULL;

	switch (*enumlist) {

		/* color */
		case -1:

			/* get list of widget names */
			xmstrings = copy_colornames(dummy, &number);
			break;

		case -2:

			/* no list, just the one widget */
			break;

		case -3:
		
			/* an XmString, with only one value; no list of options */
			break;

		case -4:

			/* fontlist */
			xmstrings = get_fonts(dummy, &number);
			break;

		/* Sibling Widget name - child of this widget's parent */
		case -5:

			/* get list of widget names */
			xmstrings = (XmString *)get_siblings(dummy, &number);
			break;

		default:

			fprintf(stderr, "TBD or Error\n");
	};

	*no_xmstrings = number;
	return (xmstrings);
}
/**************************************************
 *
 * Function: get_fonts - get all fonts available to
 *		this system's X server.
 *
 **************************************************/
static XmString *
get_fonts(void *dummy, int *number)
{
  char **ptr;
	char **x;
  int i;
	XmString *xmstrings;
	XmString *xms;

	if (verbose >6)
		printf("get_fonts\n");

  ptr = XListFonts(XtDisplay(shell), "*", 1000, number);
	x=ptr;

	xmstrings = (XmString *)XtCalloc(*number+1, sizeof(XmString *));
	xms = xmstrings;

	/* make the first one in the list the Default */
	(*xms) = XmStringCreateSimple("Default");
	xms++;

  for (i=0; i<*number; i++){

		/* turn the font names (ascii) to XmStrings */
		(*xms) = XmStringCreateSimple(*ptr);

		xms++;
    ptr++;
  };     

	XFreeFontNames(x);

	return (xmstrings);
}
/**************************************************
 *
 * Function: get_siblings
 *
 *	Get the sibling widgets - children of the selected
 *	widget's parent.
 *
 **************************************************/
static void *
get_siblings(void *dummy, int *number)
{
	Arg 				args[5];
  WidgetList 	widgetlist;
	WidgetList	wptr;
	XmString		*xmstrings;
	XmString		*xms;
	int 				i;

	if (verbose >6)
		printf("get_siblings\n");

	*number = 0;

	/* get the Xt widget names */
	XtSetArg(args[0], XmNnumChildren, number);
	XtSetArg(args[1], XmNchildren, &widgetlist);
	XtGetValues(XtParent(selected_widget), args, 2);

	xmstrings = (XmString *)XtCalloc(*number, sizeof(XmString *));
	xms = xmstrings;

	wptr = widgetlist;
	for (i=0; i<*number; i++){

		/* get the application widget names */
		(*xms) = XmStringCreateSimple(widget_name(*wptr));

		xms++;
		wptr++;
	};

	return (xmstrings);
}
/**************************************************
 *
 * Function: copy_colornames
 *
 **************************************************/
static XmString *
copy_colornames(void *dummy, int *number)
{
	XmString		*xmstrings;
	XmString		*xms;
	CNAMELIST		colornames;
	CNAMELIST		clist;
	int					i;
	int					status;

	*number = 0;
	xmstrings = NULL;

	/* list of colornames from rgb.txt */
	status = get_colornames(&colornames, number);
	if (status == NOTOK)
			return(xmstrings);
	
	xmstrings = (XmString *)XtCalloc(*number, sizeof(XmString *));
	xms = xmstrings;

	clist = colornames;
	for (i=0; i<*number; i++){
		(*xms) = XmStringCreateSimple(clist->colorname);
		xms++;
		clist++;
	};

	return (xmstrings);
}
