/*************************************************************
*
* File: create_composite.c - create composite widgets.
*
*		For XmScale, XmScrolledWindow; those widgets with 
*		automagically created child widgets.
*
*    Copyright (C) 1995  Bruce Parkin 
*
************************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/Scale.h>
#include <Xm/ScrolledW.h>

#include "lxb.h"
#include "data.h"
#include "mhandlers.h"
#include "end_program.h"
#include "select.h"
#include "children.h"
#include "recres.h"

#include "create_composite.h"

/********************************************************************
*
* Function: create_composite
*
*		For XmScale and XmScrolledWindow only so far.
* 
*		In the case of XmScrolledWindow assume NOT for
*		ScrolledList or ScrolledText - there are other
*		functions called for this.
*
********************************************************************/
Widget
create_composite(Widget parent, WidgetClass wclass)
{
	Arg args[10];
	int n;
	Widget w;
	char *name;
	char all[100];
	char number[5];
	WSTRUCT *ptr;
  WidgetList allkids;
  Widget *kidptr;
  int no_allkids;    

	/* make a string name for the class */
	name = choose_default_name(wclass);

	/* get the data structure - sets tree_ptr too */
	ptr = get_wstruct();
	ptr->key = get_counter();

	/* make the name unique */
  sprintf(number, "%d", ptr->key);
	strcpy(all, name);
	strcat(all, number);

	/* set resources per class */
	n=0;

	if (wclass == xmScaleWidgetClass){

		/* set some arbitrary size for usability sake */
		XtSetArg(args[n], XmNheight, 60);n++;
		XtSetArg(args[n], XmNwidth, 10);n++;

		record_resource(ptr, XmNheight, "60", -999);
		record_resource(ptr, XmNwidth, "10", -999);

	} else if (wclass == xmScrolledWindowWidgetClass){

		/* assume not a ScrolledList or ScrolledText */

		/* set some arbitrary size for usability sake */
		XtSetArg(args[n], XmNheight, 60);n++;
		XtSetArg(args[n], XmNwidth, 60);n++;
		XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC);n++;

		record_resource(ptr, XmNheight, "60", -999);
		record_resource(ptr, XmNwidth, "60", -999);
		record_resource(ptr, XmNscrollingPolicy, "XmAUTOMATIC", 14);

	};

	/* make the widget */
	w = XtCreateManagedWidget(all, wclass, parent, args, n);

	/* fill in the widget struct */
	strcpy(ptr->appname, all);
	ptr->instance = w;

	/* pointer to parent */
	ptr->parent = get_parent_key(parent);

	/* record the widget class */
	strcpy(ptr->class, get_widget_classname(w));

	install_select_handlers(w);

	/* get all the hidden children */
	allkids = get_xchildren(w, &no_allkids);

  kidptr = allkids;

	for (n=0; n<no_allkids; n++){

		if (verbose >4)
			printf("widget child: %s\n", XtName(*kidptr));

		/* get the data structure */
		ptr = get_wstruct();
		
		/* fill in the widget struct being consistant */
		ptr->key = get_counter();

		ptr->parent = get_parent_key(w);

		strcpy(ptr->appname, XtName(*kidptr));
		ptr->instance = *kidptr;
		strcpy(ptr->class, get_widget_classname(*kidptr));

		/* don't want lxb on load of save file to try and create these */
		strcpy(ptr->create_function, "EXISTING");
		
		/* or trying to manage them */
		ptr->managed = False;

		/* don't let the user delete them */
		ptr->perm = True;

		/* can't edit resources, either - not implemented */
		ptr->fixed = True;

		/* nor should they have select handlers installed: causes system crash */
		ptr->sel = False;

		kidptr++;
	};                                        

	return (w);
}
