/***************************************************
 * File: cvt_resvalue.c
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
#include "cvt_resvalue.h"

/* local prototypes */
static int
redo_std_value(ArgList arg, char *ptr, char *resource_value, int index);

static int
redo_enum_value(ArgList arg, char *ptr, char *resource_value, int enumlist);

static int
redo_special_value(ArgList arg, char *ptr, char *resource_value, int enumlist);

/**************************************************
 *
 * Function: convert_value
 *
 *	Convert a resource value datatype in string format to the actual type. 
 *
 *	Load all in an arg (increment of the Arg array is done up 1 level
 *
 *	Used in "recreating" the stored GUI read from it's *.lxb file.
 *
 **************************************************/
int
convert_value(ArgList arg, char *resource_name, char *resource_value)
{
	int				index;
	int 			enumlist;
	int				status;

	if (verbose >8)
		printf("convert_value: %s  %s\n", resource_name, resource_value);

  /* get the index for tsizes.h, and enumlist for rstruct.h */
	/* resource name is already stripped of "XmN" */
  status = id_resource(resource_name, &enumlist, &index);

  if (status == NOTOK){
		fprintf(stderr,"convert_value: error trying to id resource: (%s)\n", resource_name);
    return (status);
  };

  if (enumlist == -999){

		status = redo_std_value(arg, resource_name, resource_value, index);

  } else if (enumlist >=0) {

		status = redo_enum_value(arg, resource_name, resource_value, enumlist);

  } else if (enumlist < 0){

		status = redo_special_value(arg, resource_name, resource_value, enumlist);

  };

	if (status == NOTOK)
		fprintf(stderr, "convert_value: error in attempting to redo resource\n");

  return (status);             
}
/**************************************************
 *
 * Function:	redo_std_value
 *
 *	"ptr" is the resource name without the "XmN"
 *
 **************************************************/
static int
redo_std_value(ArgList arg, char *ptr, char *resource_value, int index)
{

	/* get resource value */
	switch (index){

		/* DATA itself */

		/*	char	*/
		case 0:		

			XtSetArg(*arg, ptr, (char)(atoi(resource_value)));
			break;

		/*	short	*/
		case 7: case 23:		

			XtSetArg(*arg, ptr, (short)(atoi(resource_value)));
			break;

		/*	int */
		case 22:

			XtSetArg(*arg, ptr, atoi(resource_value));
			break;

		/* 	long	*/
		case 9: case 10: case 11: case 13: case 17: case 18: case 20: case 21:

			XtSetArg(*arg, ptr, atol(resource_value));
			break;  

		/*	unsigned int */
		case 1: case 24:	

			XtSetArg(*arg, ptr, (unsigned int)(atoi(resource_value)));
			break;

		/*	unsigned long	*/
		case 2: case 4: case 6: case 12:	

			XtSetArg(*arg, ptr, (unsigned long)(atol(resource_value)));
			break;

		/*	unsigned short */
		case 3:

			XtSetArg(*arg, ptr, (unsigned short)(atoi(resource_value)));
			break;

		/* pointer to the DATA */

		/* char* String */
		case 8:	

			/* ascii String */
			XtSetArg(*arg, ptr, resource_value);
			break; 
			
		/* void*	- userData */
		case 19:

			break; 

		/*	unsigned char* - most are to XmString	*/
		case 15:

			XtSetArg(*arg, ptr, resource_value);
			break; 

		default:

			fprintf(stderr,"convert_value: error in index (%d)\n", index);
			return (NOTOK);
	};

	return (OK);
}
/**************************************************
 *
 * Function:	redo_enum_value
 *
 *	"ptr" is the resource name without the "XmN"
 *
 **************************************************/
static int
redo_enum_value(ArgList arg, char *ptr, char *resource_value, int enumlist)
{
	int				number;

	number = get_enum_number(&enumlist, resource_value);

	if (number == -1){

		fprintf(stdout, "Cannot get enum type for resource: XmN%s  value: %s  enumlist: %d\n", ptr, resource_value, enumlist);
		return (NOTOK);

	}else 

		XtSetArg(*arg, ptr, number);

	return (OK);
}
/**************************************************
 *
 * Function:	redo_special_value
 *
 *	"ptr" is the resource name without the "XmN"
 *
 *	All resource values are stored as Strings in the
 *	"save" file. They must be converted.
 *
 **************************************************/
static int
redo_special_value(ArgList arg, char *ptr, char *resource_value, int enumlist)
{
	Pixel			pixel;
	Widget		wres;
	XmString	xm;
	XmFontList fontlist;

	if (verbose >8)
		printf("redo_special_value\n");

	/* set resource value */
	switch (enumlist){

		/* PIXEL */
		case -1:
			pixel = get_pixel(resource_value);
			XtSetArg(*arg, ptr, pixel);

			break;

		/* any resource (ie, XmWIDGET for Form) widget */
		case -2:

			/* the resource value here is the app-widget name */

			/* get the instance (Widget) */
			wres = widget_instance(resource_value);
			
			/* set the resource */
			XtSetArg(*arg, ptr, wres);
			break;

		/* XmString */
		case -3:

			/* resource value is ascii - convert back to XmString type */
			xm = XmStringCreateSimple(resource_value);

			/* set the resource */
			XtSetArg(*arg, ptr, xm); 		/* OOPS! memory leak */
			break;

		/* fontlist */
		case -4:

			fontlist = get_fontlist(shell, resource_value);
			XtSetArg(*arg, ptr, fontlist);

			break;

    case -5:

      /* get the instance (Widget) */
      wres = widget_instance(resource_value);

      /* set the resource */
      XtSetArg(*arg, ptr, wres);
      break;         

		default:

			fprintf(stderr,"Error in set_special_value\n");
			fprintf(stdout, "Cannot get special type for: %s\t%s\n", ptr, resource_value);
			return (NOTOK);

	};

	return(OK);

}
