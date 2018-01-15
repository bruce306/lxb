/**************************************************
 * File: menushell.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>

#include "lxb.h"
#include "data.h"
#include "recres.h"
#include "populate.h"
#include "select.h"
#include "mhandlers.h"

#include "menushell.h"

/**************************************************
 *
 * Function: create_menushell
 *
 **************************************************/
Widget
create_menushell(Widget parent)
{
	Widget menushell;
	char all[100];
	char number[5];
	WSTRUCT *ptr;
	int counter;
	char *name;
	Arg		args[5];

	if (verbose >6)
		printf("create_menushell\n");

	/* make a string name for the class */
	name = "menushell_";

	counter = get_counter();

	/* make the name unique */
  sprintf(number, "%d", counter);
	strcpy(all, name);
	strcat(all, number);

	XtSetArg(args[0], XmNwidth, 1);
	XtSetArg(args[1], XmNheight, 1);

	menushell = XmCreateMenuShell(parent, all, args, 2);
    
	/* get the data structure - sets tree_ptr too */
	ptr = get_wstruct();

	record_resource(ptr, XmNwidth, "1", -999); 
	record_resource(ptr, XmNheight, "1", -999); 

	/* fill in the widget struct */
	ptr->key = counter;
	strcpy(ptr->appname, all);

	/* fill in the widget struct */
	ptr->instance = menushell;

	ptr->parent = get_parent_key(parent);
	strcpy(ptr->class, get_widget_classname(menushell));

	/* TBD */
	ptr->global = True;
	ptr->perm = True;
	ptr->fixed = True;
	ptr->sel = False;

	strcpy(ptr->create_function, "XmCreateMenuShell");

	populate_wtree();
	unselect(selected_widget);
	select_widget(ptr->instance);      

	return (menushell);
}
