/***************************************************
 *
 * File: get_resvalue.c
 *
 *    Copyright (C) 1997  Bruce Parkin 
 *
 *	Just get the resource value. Apply special 
 *	processing or conversion or lookup to it
 *	before it is displayed.
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>

#include "lxb.h"
#include "misc.h"
#include "fonts.h"
#include "data.h"
#include "color.h"
#include "id_resource.h"
#include "get_resvalue.h"

/* local prototypes */
static char *
get_std_value(Widget w, char *buf, char *ptr, int index);

static char *
get_enum_value(Widget w, char *buf, char *ptr, int *enumlist, int index);

static char *
get_special_value(Widget w, char *ptr, int *enumlist);

/*****************************************************************************
*
* Function: get_resource_value - given the resource name (ie, "XmNwidth")
*		get the value of it from the selected_widget.
*
*	Also return the "enumlist"
*
*****************************************************************************/
char *
get_resource_value(char *resource_name, int *enumlist)
{
  int     status;
  char    *resource_value;
  char    *buf;
  Widget  w;
  int     index;
  char    *ptr;

  /* TBD: change all this */
  buf = XtMalloc(100);
  *enumlist = -999;
  w = selected_widget;

  /* skip over the "XmN" prefix */
  ptr = resource_name+3;

  /* get the index for tsizes.h, and enumlist for rstruct.h */
  status = id_resource(ptr, enumlist, &index);

  if (status == NOTOK){
    fprintf(stderr, "get_resource_value: problems getting resource id\n");
		XtFree(buf);
    return (NULL);
  };

  if (*enumlist == -999){

    resource_value = get_std_value(w, buf, ptr, index);
  } else if (*enumlist >=0) {

    resource_value = get_enum_value(w, buf, ptr, enumlist, index);
  } else if (*enumlist < 0){

		XtFree(buf);
    resource_value = get_special_value(w, ptr, enumlist);
  };

	if (verbose >6)
		printf("    Resource Name: (%s)  Resource Value: (%s)\n", resource_name, resource_value);

  return (resource_value);            
}
/**************************************************
 *
 * Function: get_std_value
 *
 **************************************************/
static char *
get_std_value(Widget w, char *buf, char *ptr, int index)
{
	Arg				arg[1];
	XmString	xm;

	char 						Char;
	short						Short;
	int							Int;
	long						Long;
	unsigned short	unsignedShort;
	unsigned int  	unsignedInt;
	unsigned long 	unsignedLong;
	char 						*charPtr;
	unsigned char 	*unsignedCharPtr;

	/* get resource value */
	switch (index){

		/* DATA itself */

		/*	char - Boolean */
		case 0:		
			XtSetArg(arg[0], ptr, &Char);
			XtGetValues(w, arg, 1);
			if (Char == 0)
				sprintf(buf,"False");
			else
				sprintf(buf,"True");
			break;

		/*	short	*/
		case 7: case 23:		
			XtSetArg(arg[0], ptr, &Short);
			XtGetValues(w, arg, 1);
			sprintf(buf, "%d", Short);
			break;

		/* 	int  */
		case 22:
			XtSetArg(arg[0], ptr, &Int);
			XtGetValues(w, arg, 1);
			sprintf(buf, "%d", Int);
			break;  
		/* 	long	*/
		case 9: case 10: case 11: case 13: case 17: case 18: case 20:
			XtSetArg(arg[0], ptr, &Long);
			XtGetValues(w, arg, 1);
			sprintf(buf, "%ld", Long);
			break;  

		/*	unsigned int */
		case 1: case 24:	
			XtSetArg(arg[0], ptr, &unsignedInt);
			XtGetValues(w, arg, 1);
			sprintf(buf,"%u", unsignedInt);
			break;

		/*	unsigned long	*/
		case 2: case 4: case 6: case 12:	
			XtSetArg(arg[0], ptr, &unsignedLong);
			XtGetValues(w, arg, 1);
			sprintf(buf,"%lu", unsignedLong);
			break;

		/*	unsigned short */
		case 3:
			XtSetArg(arg[0], ptr, &unsignedShort);	
			XtGetValues(w, arg, 1);
			sprintf(buf,"%u", unsignedShort);
			break;

		/* pointer to the DATA */

		/*	char * - assume a NULL terminated string */
		case 8:							
			XtSetArg(arg[0], ptr, &charPtr);
			XtGetValues(w, arg, 1);
			XtFree(buf);
			buf = XtMalloc( (strlen(charPtr) + 1) );
	
			memset(buf, (strlen(charPtr) +1), 0);
			memcpy(buf, charPtr,  (strlen(charPtr) + 1));

			break; 
		
		/*	unsigned char * - most are to XmString	*/
		case 15:
			XtSetArg(arg[0], ptr, &unsignedCharPtr);
			XtGetValues(w, arg, 1);
			XtFree(buf);
		
			xm = XmStringCopy((XmString)unsignedCharPtr);
			XmStringGetLtoR(xm, XmSTRING_DEFAULT_CHARSET, &buf);
			XmStringFree(xm);
			break; 

		/* void * - XtPointer (used for userData, XtCallbackList) */
		case 19:
			XtFree(buf);
			buf = NULL;
			fprintf(stderr, "get_std_value: cannot get datatype for resource %s\n", ptr);
			break; 

		default:
			fprintf(stderr,"Error in get_std_resource\n");
			fprintf(stderr,"Problem in datatype conversion\n");
			XtFree(buf);
			buf = NULL;
	};	
	return (buf);
}
/********************************************************************************************
 *
 * Function: get_enum_value - Get the resource value if it is an enumerated type.
 *
 *	For some unknown reason Motif returns some resource types with a data type of
 *	"unsigned char" AND some with type of "int". However, all C "enumerated" types
 *	are of type int. 
 *
 *	Thus the type conversion. (Compare and try XmText's XmNeditMode and XmDrawingArea's
 *	XmNresizePolicy).
 *
 *	1) 	Get the resource value of type int or unsigned char (datatype size is 
 *		determined via index and tsizes.h).
 *
 *	2)	Convert the resource value to int.
 *	
 *	3)	Use the int value to return the corresponding enumerated value text string
 *		(ie, XmRESIZE_ANY.
 *
 *-------------------------------------------------------------------------------------------
 *
 *	w:			the widget
 *	ptr:		XmN*ptr - resource name
 *	enumlist: 	key into xenum.h
 *	index:		key into tsizes.h for datatype size
 *
 *	RETURNS:	the enumerated type string ("XmRESIZE_ANY")
 *
 ********************************************************************************************/
static char *
get_enum_value(Widget w, char *buf, char *ptr, int *enumlist, int index)
{
	Arg	arg[3];
	int 			Int;
	unsigned char 	UnsignedChar;
	char			Char;

	if (verbose >6)
		printf("get_enum_value: resource name: XmN%s  enumlist: %d  index: %d\n", ptr, *enumlist, index);

	/* get resource value */
	switch (index){

		/*	char - Boolean */
		case 0:		
			XtSetArg(arg[0], ptr, &Char);
			XtGetValues(w, arg, 1);
			if (Char == 0)
				sprintf(buf,"False");
			else
				sprintf(buf,"True");
			break;

        /*  int  */
        case 22:
            XtSetArg(arg[0], ptr, &Int);
            XtGetValues(w, arg, 1);
            sprintf(buf, "%d", Int);
            break;

		/* unsigned char */
		case 24:
			XtSetArg(arg[0], ptr, &UnsignedChar);
            XtGetValues(w, arg, 1);
			Int = (int)UnsignedChar;
			break;
	};

	buf = get_enum_type(enumlist, &Int, buf);
	return (buf);
}
/**************************************************************************
*
* Function: get_special_value
*
*	Get the value for a resource that needs some
*	conversion or extra processing. (ie, widget names,
*	colornames, fonts...)
*
*	Inputs:
*		w:		the selected widget
*		ptr:	the resource name, minus "XmN"
*
*	Returns:
*		the resource value
*
***************************************************************************/
static char *
get_special_value(Widget w, char *ptr, int *enumlist)
{
	Arg							arg[2];
	char 						*tmp;
	unsigned long 	unsignedLong;
	Widget					wres;
	XmString				xm;
	char *buf;
  WidgetList  widgetlist;         
	Widget			*wp;
	int 				num;

	buf = XtMalloc(100);

	/* get resource value */
	switch (*enumlist){

		/*	PIXEL: unsigned long	TBD - will not work with diff colormaps and displays */
		case -1: 
			XtSetArg(arg[0], ptr, &unsignedLong);
			XtGetValues(w, arg, 1);

			tmp = get_pixel_color(unsignedLong);
			strcpy(buf, tmp);
			break;

		/* widget - ie, XmNcancelButton */
		case -2:

			/* get the widget instance */
			XtSetArg(arg[0], ptr, &wres);
			XtGetValues(w, arg, 1);

			if (wres == NULL){
				XtFree(buf);
				buf = NULL;
			} else {

				/* get the name of the widget - list, not Xt */
				tmp = widget_name(wres);
				strcpy(buf, tmp);
			};

			break;   

		/* an XmString */
		case -3:

			/* get the XmString */
			XtSetArg(arg[0], ptr, &xm);
			XtGetValues(w, arg, 1);

			/* get the ascii string from it */
			XmStringGetLtoR(xm, XmSTRING_DEFAULT_CHARSET, &buf);
			break;

		/* Fonts */
		case -4:

			/* not implemented yet */
			tmp = get_font_name(w);
			strcpy(buf, tmp);
			break;

		/* sibling widget - parent is XmForm */
		case -5:

			/* get the widget instance */
			XtSetArg(arg[0], ptr, &wres);
			XtGetValues(w, arg, 1);

			if (wres == NULL){

				XtFree(buf);
				buf = NULL;

			} else {

				/* get the name of the widget - list, not Xt */
				tmp = widget_name(wres);
				strcpy(buf, tmp);
			};

			break;

		/* not implemented yet */
		case -100:
			XtFree(buf);
			buf = NULL;
			break;

		default:
			fprintf(stderr, "Problems in get_special_value\n");
			XtFree(buf);
			buf = NULL;
	};	
	return (buf);
}
