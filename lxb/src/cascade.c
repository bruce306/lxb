/**************************************************
 * File: cascade.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/CascadeB.h>

#include "lxb.h"
#include "data.h"
#include "select.h"
#include "mhandlers.h"
#include "recres.h"
#include "populate.h"
#include "delete.h"

#include "menushell.h"
#include "pulldown.h"
#include "cascade.h"

/* local prototypes */
static Widget
menubar_cascade_button(Widget parent);
static Widget
pulldown_cascade_button(Widget parent);

static void
destroy_callback(Widget w, XtPointer client_data, XtPointer call_data);     

/*************************************************************
*
* Function: destroy_callback
*
*	Called when the cascade button is destroyed - by the user 
*	"Deleting" the widget. 
*
*	This mechanism is used to also "Delete" the associated Pulldown
*	(XmNsubMenuID), it'c child widgets, and it's MenuShell if no
*	more Pulldown children.
*
*
*************************************************************/
static void
destroy_callback(Widget w, XtPointer client_data, XtPointer call_data)
{            

	Widget pulldown;
	Widget menushell;
	Arg args[3];
	int num;

	/* get the pulldown associated with the cascade button */
	XtSetArg(args[0], XmNsubMenuId, &pulldown);
	XtGetValues(w, args, 1);

	/* get the menushell and number of it's children */
	menushell = XtParent(pulldown);
	XtSetArg(args[0], XmNnumChildren, &num);
	XtGetValues(menushell, args, 1);

	/* if only one child, it's the pulldown, delete all */
	if (num ==1){

		/* delete it and all descendents */
		delete_widget(menushell, True);

	} else {

		/* delete only the pulldown; must leave the menushell */
		delete_widget(pulldown, True);

	};

	/* update the widget hier. display window */
	populate_wtree();

}
/**************************************************
 *
 * Function: pulldown_cascade_button
 *
 *	parent is pulldown
 *
 **************************************************/
static Widget
pulldown_cascade_button(Widget parent)
{
	return (NULL);
}
/**************************************************
 *
 * Function: create_cascade_button
 *
 *	parent is menubar or pulldown
 *	parent_type:	XmMENU_BAR, XmPULLDOWN
 *
 **************************************************/
Widget
create_cascade_button(Widget parent, unsigned char parent_type)
{
	Widget button;

	if (parent_type == XmMENU_BAR) {

		button = menubar_cascade_button(parent);

	} else if (parent_type == XmMENU_PULLDOWN) {

		button = pulldown_cascade_button(parent);

	};

	return (button);
}
/**************************************************
 *
 * Function: menubar_cascade_button
 *
 *	parent is menubar
 *
 **************************************************/
static Widget
menubar_cascade_button(Widget parent)
{
	Arg 				args[10];
	int 				n;
	Widget 			button;
	Widget 			pulldown;
	Widget 			menushell;
	char 				*name;
	char 				all[100];
	char 				number[5];
	WidgetClass wclass;
	WSTRUCT 		*ptr;
	int 				counter;
	char 				*pulldown_name;
	WidgetList 	widgetlist;
	WidgetList	wlist;
	int					num;

	/* get any other cascade children of the parent (menubar) */

	XtSetArg(args[0], XmNnumChildren, &num);
	XtSetArg(args[1], XmNchildren, &widgetlist);
	XtGetValues(parent, args, 2);

	/* if any other cascade, get their pulldowns; parent = MenuShell */
	pulldown = NULL;
	wlist = widgetlist;

	for (n=0; n<num; n++){

		if (XtClass(*wlist) == xmCascadeButtonWidgetClass){
			XtSetArg(args[0], XmNsubMenuId, &pulldown);
			XtGetValues((*wlist), args, 1);
			break;
		};
		wlist++;
	};

	if (pulldown == NULL) {

		/* make the first MenuShell */
    menushell = create_menushell(parent); 

	} else {

		/* MenuShell already exists */
		menushell = XtParent(pulldown);
	};

	/* make the pulldown for this cascade button */
	pulldown = menubar_pulldown(menushell);

	/* get Intrinsic's class */
	wclass = xmCascadeButtonWidgetClass;

	/* make a string name for the class */
	name = choose_default_name(wclass);
	if (name == NULL){
		fprintf(stderr, "menubar_cascade_button: Cannot get default name\n");
		return (NULL);
	};

	counter = get_counter();

	/* make the name unique */
  sprintf(number, "%d", counter);
	strcpy(all, name);
	strcat(all, number);

	/* get the data structure - sets tree_ptr too */
	ptr = get_wstruct();

	ptr->key = counter;

	/* set some universal resources */
	n=0;
	XtSetArg(args[n], XmNtraversalOn, False);n++;
	XtSetArg(args[n], XmNnavigationType, XmNONE);n++;
	XtSetArg(args[n], XmNsubMenuId, pulldown);n++;

	/* make the widget */
	button = XtCreateWidget(all, wclass, parent, args, n);

	/* add the destroy callback */
	XtAddCallback(button, XmNdestroyCallback, destroy_callback, NULL);                    

	/* fill in the widget struct */
	strcpy(ptr->appname, all);
	ptr->instance = button;

	/* pointer to parent */
	ptr->parent = get_parent_key(parent);

	/* record the widget class */
	strcpy(ptr->class, get_widget_classname(button));

	/* TBD */
	ptr->global = True;

	/* record resources for Cascade Button */
	pulldown_name = widget_name(pulldown);

	record_resource(ptr, XmNsubMenuId, pulldown_name, -2);

	XtManageChild(button);

	install_select_handlers(button);
	return (button);
}
