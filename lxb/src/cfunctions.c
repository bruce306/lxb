/**************************************************
 * File: cfunctions.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include <Xm/ScrolledW.h>
#include <Xm/List.h>
#include <Xm/Text.h>

#include "lxb.h"
#include "cfunctions.h"

/**************************************************
 *
 *	Function: create_function
 *
 *	function_name:
 *		NULL:									this is not called.
 *		"XmCreateMenuShell":	XmCreateMenuShell
 *		"EXISTING":							already exists; get Widget id from parent
 *
 **************************************************/
Widget
create_function(char *function_name, Widget parent, char *widget_name, Arg args[], int n)
{
	Widget w;
  int i, num;
  WidgetList wlist;
	Arg wargs[3];
	Boolean found = False;

	w = NULL;

	if ( (strcmp(function_name, "XmCreateMenuShell") ==0) ){

		w = XmCreateMenuShell(parent, widget_name, args, n);

	}else if (!strcmp("EXISTING", function_name)){

		/* already exists; get Widget id from parent */			/* ie, scrolled window children */

		XtSetArg(wargs[0], XmNnumChildren, &num);
		XtSetArg(wargs[1], XmNchildren, &wlist);
		XtGetValues(parent, wargs, 2);      
		
		/* just get and return the already created Widget id */ 
		for (i=0; i<num; i++){

			if (!strcmp(widget_name, XtName(*wlist))){
				w = *wlist;
				found = True;
				break;
			};
			
			wlist++;
		};

		if (!found)
			fprintf(stderr, "Did not find created widget's id (%s)\n", widget_name);

	} else {

		fprintf(stderr, "call_create_function: Unknown create function: %s\n", function_name);

	};

	return (w);
}	
