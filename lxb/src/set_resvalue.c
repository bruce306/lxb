/**************************************************
 * File: set_resvalue.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <stdlib.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "color.h"
#include "fonts.h"
#include "data.h"
#include "misc.h"
#include "recres.h"
#include "id_resource.h"
#include "set_resvalue.h"

/* local prototypes */
static void
set_std_value(Widget w, char *ptr, char *resource_value, int index, int enumlist);

static void
set_enum_value(Widget w, char *ptr, char *resource_value, int enumlist);

static void
set_special_value(Widget w, char *ptr, char *resource_value, int enumlist);

/**************************************************
 *
 * Function: set_resource_value
 *
 *	toplevel function - set the resource value of
 *	the input resource name.
 *
 **************************************************/
int
set_resource_value(char *resource_name, char *resource_value)
{
	int 			status;
	Widget 		w;
	WSTRUCT 	*wptr;
	char 			*ptr;
	int				index;
	int 			enumlist;

	if (verbose > 6)
		printf("set_resource_value\n");

	/* init */
	enumlist = -999;
	index = -1;
	w = selected_widget;

  /* skip over the "XmN" prefix */
  ptr = resource_name+3;
	
	/* get the index for tsizes.h, and enumlist for rstruct.h */
	status = id_resource(ptr, &enumlist, &index);

	if (status == NOTOK){
		fprintf(stderr, "set_resource_value: problems getting resource id\n");
		return (status);
	};

	/* get the node in the list */
	wptr = widget_ptr(w);

	/* record/re-record the resource */
	re_record_resource(wptr, ptr, resource_value, enumlist);

	if (enumlist == -999){

		set_std_value(w, ptr, resource_value, index, enumlist);

	} else if (enumlist >=0) {

		set_enum_value(w, ptr, resource_value, enumlist);

	} else if (enumlist < 0){

		set_special_value(w, ptr, resource_value, enumlist);
	};

	XtUnmanageChild(w);
	XtManageChild(w);

	return (OK);

}
/**************************************************
 *
 *	Function: set_std_value
 *
 **************************************************/
static void
set_std_value(Widget w, char *ptr, char *resource_value, int index, int enumlist)
{
	Arg	arg[2];
	int	i;

	i=0;

	/* get resource value */
	switch (index){

		/* DATA itself */

		/*	char	*/
		case 0:		
			XtSetArg(arg[i], ptr, (char)(atoi(resource_value)));i++;
			XtSetValues(w, arg, i);

			break;

		/*	short	*/
		case 7: case 23:		
			XtSetArg(arg[i], ptr, (short)(atoi(resource_value)));i++;
			XtSetValues(w, arg, i);
			break;

		/* 	int */
		case 22:
			XtSetArg(arg[i], ptr, atoi(resource_value));i++;
			XtSetValues(w, arg, i);
			break;  

		/* 	long	*/
		case 9: case 10: case 11: case 13: case 17: case 18: case 20:
			XtSetArg(arg[i], ptr, atol(resource_value));i++;
			XtSetValues(w, arg, i);
			break;  

		/*	unsigned int */
		case 1: case 24:	
			XtSetArg(arg[0], ptr, (unsigned int)(atoi(resource_value)));i++;
			XtSetValues(w, arg, i);
			break;

		/*	unsigned long	*/
		case 2: case 4: case 6: case 12:	
			XtSetArg(arg[i], ptr, (unsigned long)(atol(resource_value)));i++;
			XtSetValues(w, arg, i);
			break;

		/*	unsigned short */
		case 3:
			XtSetArg(arg[i], ptr, (unsigned short)(atoi(resource_value)));i++;
			XtSetValues(w, arg, i);
			break;

		/* pointer to the DATA */

		/* char* XmString */
		case 8:	

			/* XmSTRING */
			XtSetArg(arg[i], ptr, (char *)resource_value);i++;
			XtSetValues(w, arg, i);
			break; 
		
		/* void*	- userData */
		case 19:

			break; 

		/*	unsigned char* - most are to XmString	*/
		case 15:

			XtSetArg(arg[i], ptr, resource_value);i++;
			XtSetValues(w, arg, i);
			break; 

		default:

			fprintf(stderr,"Error in get_std_value\n");
	};

}
/**************************************************
 *
 *	Function: set_enum_value
 *
 **************************************************/
static void
set_enum_value(Widget w, char *ptr, char *resource_value, int enumlist)
{
	Arg				args[1];
	int				number;

	number = get_enum_number(&enumlist, resource_value);

	if (number == -1){
		fprintf(stdout, "Cannot get enum type for: %s\t%s\n", ptr, resource_value);
	}else {

		XtSetArg(args[0], ptr, number);
		XtSetValues(w, args, 1);

	};

	if (verbose >6){

		printf("set_enum_value - resource_name: (%s)\n", ptr);
		printf("\t resource_value: (%s)\n", resource_value);
		printf("\t enumlist: (%d)\n", enumlist);
		printf("\t set_enum_value - number: (%d)\n", number);
		printf("\t widget name: (%s)\n", XtName(w));

	};

}
/**************************************************
 *
 * Function:	set_special_value
 *
 **************************************************/
static void
set_special_value(Widget w, char *ptr, char *resource_value, int enumlist)
{
	Arg				arg[2];
	Pixel			pixel;
	Widget		wres;
	XmString	xm;
	XmFontList fontlist;

	/* set resource value */
	switch (enumlist){

		/* PIXEL */
		case -1:
			pixel = get_pixel(resource_value);
			XtSetArg(arg[0], ptr, pixel);
			XtSetValues(w, arg, 1);
			break;

		/* any widget */
		case -2:

			/* get the instance (Widget) */
			wres = widget_instance(resource_value);
			
			/* set the resource */
			XtSetArg(arg[0], ptr, wres);
			XtSetValues(w, arg, 1);
			break;

		/* XmString */
		case -3:

			/* already been converted to ascii string; convert back to XmString */

			xm = XmStringCreateSimple(resource_value);

			/* set the resource */
			XtSetArg(arg[0], ptr, xm);
			XtSetValues(w, arg, 1);
			XmStringFree(xm);

			break;

		/* fontlist */
		case -4:

			if (verbose >6)
				printf("setting font\n");

			fontlist = get_fontlist(w, resource_value);

			/* set the resource */
			XtSetArg(arg[0], ptr, fontlist);
			XtSetValues(w, arg, 1);

			XmFontListFree(fontlist);

			break;

		/* sibling - XmForm constraint */
		case -5:

			/* get the instance (Widget) */
			wres = widget_instance(resource_value);
			
			/* set the resource */
			XtSetArg(arg[0], ptr, wres);
			XtSetValues(w, arg, 1);

			break;

		/* Not implemented yet */
		case -100:

			break;

		default:

			fprintf(stderr,"Error in set_special_value\n");
	};

}
