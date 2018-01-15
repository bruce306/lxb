/*********************************************************************
* File: cscrolled.c - creation functions for scrolled windows
* 	(Text, List)
*
*    Copyright (C) 1995  Bruce Parkin 
*
*********************************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/ScrolledW.h>
#include <Xm/Text.h>
#include <Xm/List.h>

#include "lxb.h"
#include "data.h"
#include "select.h"
#include "mhandlers.h"
#include "recres.h"
#include "cscrolled.h"
#include "populate.h"

/* local prototypes */
static void
do_children(Widget scwindow, Widget mainchild);

/********************************************************************
 *
 *	Function: create_scrolled - this creates a scrolled
 *		text or list window heirarchy of widgets.
 *
 *******************************************************************/
int
create_scrolled(Widget parent, char *name)
{
  char all[100];
  char number[5];    
	WSTRUCT *ptr;
	Widget child;
	Arg args[12];
	int n;

	/* set some universal resources */
	n=0;
	XtSetArg(args[n], XmNtraversalOn, False);n++;
	XtSetArg(args[n], XmNnavigationType, XmNONE);n++;

	/** first create the Scrolled Window **/

  /* get the data structure */
  ptr = get_wstruct();
  ptr->key = get_counter();             
  ptr->global = True;

	strcpy(all, "scrolledWindow_");
	sprintf(number, "%d", ptr->key);
	strcat(all, number);  

  strcpy(ptr->appname, all);     
  ptr->parent = get_parent_key(parent);
  strcpy(ptr->class, "xmScrolledWindowWidgetClass");

	/* required resources */
	XtSetArg(args[n], XmNx, 0);n++;
	XtSetArg(args[n], XmNy, 0);n++;
	XtSetArg(args[n], XmNwidth, 60);n++;
	XtSetArg(args[n], XmNheight, 60);n++;
	XtSetArg(args[n], XmNscrollingPolicy, XmAPPLICATION_DEFINED);n++;
	XtSetArg(args[n], XmNvisualPolicy, XmVARIABLE);n++;
	XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmSTATIC);n++;
	XtSetArg(args[n], XmNshadowThickness, 0);n++;

	record_resource(ptr, XmNx, "0", -999);
	record_resource(ptr, XmNy, "0", -999);
	record_resource(ptr, XmNwidth, "60", -999);
	record_resource(ptr, XmNheight, "60", -999);        

	record_resource(ptr, XmNscrollingPolicy, "XmAPPLICATION_DEFINED", 14); 
	record_resource(ptr, XmNvisualPolicy, "XmVARIABLE", 18); 
	record_resource(ptr, XmNscrollBarDisplayPolicy, "XmSTATIC", 16); 
	record_resource(ptr, XmNshadowThickness, "0", -999);

  ptr->instance = XtCreateManagedWidget(all, xmScrolledWindowWidgetClass, parent, args, n);

  install_select_handlers(ptr->instance);

  populate_wtree();
  unselect(selected_widget);
  select_widget(ptr->instance);          

	/* new parent */
	parent = ptr->instance;

	/** create the child widget **/

	if (!strncmp(name, "ScL", 3)){

		/* scrolled list */

		/* get the data structure */
		ptr = get_wstruct();
		ptr->key = get_counter();             
		ptr->global = True;

		strcpy(all, "list_");
		sprintf(number, "%d", ptr->key);
		strcat(all, number);  

		strcpy(ptr->appname, all);
		ptr->parent = get_parent_key(parent);
		strcpy(ptr->class, "xmListWidgetClass");

		/* want multi-line widget */
		n=2;
		XtSetArg(args[n], XmNvisibleItemCount, 7);n++;
		record_resource(ptr, XmNvisibleItemCount, "7", -999); 

		/* make the widget */
		ptr->instance = XtCreateManagedWidget(all, xmListWidgetClass, parent, args, n);

	} else if (!strncmp(name, "ScT", 3)){

		/* scrolled text */

		/* get the data structure */
		ptr = get_wstruct();
		ptr->key = get_counter();             
		ptr->global = True;

		strcpy(all, "text_");
		sprintf(number, "%d", ptr->key);
		strcat(all, number);  

		strcpy(ptr->appname, all);
		ptr->parent = get_parent_key(parent);
		strcpy(ptr->class, "xmTextWidgetClass");

		/* want multi-line widget */
		n=2;
		XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);n++;
		XtSetArg(args[n], XmNwidth, 100);n++;
		XtSetArg(args[n], XmNheight, 100);n++;
		record_resource(ptr, XmNeditMode, "XmMULTI_LINE_EDIT", 15); 
		record_resource(ptr, XmNwidth, "100", -999); 
		record_resource(ptr, XmNheight, "100", -999); 

		/* make the widget */
		ptr->instance = XtCreateManagedWidget(all, xmTextWidgetClass, parent, args, n);

	} else {

		fprintf(stderr, "Unknown scrolled type: %s\n", name);
		return (NOTOK);
	};

	/* do the auto created children only */
	do_children(parent, ptr->instance);

	/* do the main child widget */
	install_select_handlers(ptr->instance);

  populate_wtree();
  unselect(selected_widget);
  select_widget(ptr->instance);          

	return (OK);
}

/**************************************************
 *
 * Function: do_children - take care of the child
 *	widgets created automatically for the Scrolled Window
 *	(the 2 scrollbars - the ClipWindow is not created...)
 *
 *	Skip the main child - already done.
 *
 **************************************************/
static void
do_children(Widget scwindow, Widget mainchild)
{
	Arg args[10];
	char *name;
	WidgetClass wclass;
	WSTRUCT *ptr;
	int num, i;
	WidgetList widgetlist, wlist;

	XtSetArg(args[0], XmNnumChildren, &num);
	XtSetArg(args[1], XmNchildren, &widgetlist);
	XtGetValues(scwindow, args, 2);

	wlist = widgetlist;

	/* do for all children */
	for (i=0; i<num; i++){

		if (*wlist == mainchild){

			/* skip the main child */
			wlist++;
			continue;
		};

		/* get Intrinsic's class */
		wclass = XtClass(*wlist);

		/* get the name of the created child widget */
		name = XtName(*wlist);

		/* get the data structure - sets linked list ptr too */
		ptr = get_wstruct();

		ptr->key = get_counter();

		/* fill in the widget struct */
		strcpy(ptr->appname, name);
		ptr->instance = *wlist;

		/* pointer to parent */
		ptr->parent = get_parent_key(scwindow);

		/* record the widget class */
		strcpy(ptr->class, get_widget_classname(*wlist));

		/* don't want lxb on load of save file to try and create these */
		strcpy(ptr->create_function, "EXISTING");
		
		/* or trying to manage them */
		ptr->managed = False;

		/* don't let the user delete them */
		ptr->perm = True;

		/* can't edit resources, either - not implemented */
		ptr->fixed = True;

		install_select_handlers(*wlist);
		wlist++;
	};
}
