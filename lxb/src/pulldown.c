/**************************************************
 * File: pulldown.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/MenuShell.h>

#include "lxb.h"
#include "data.h"
#include "recres.h"
#include "select.h"
#include "mhandlers.h"
#include "populate.h"

#include "menushell.h"
#include "pulldown.h"

/**************************************************
 *
 * Function: create_pulldown
 *
 *	Only for Menubars for now. Parent of the pulldown
 *	must be the Menubar's associated MenuShell.
 *
 **************************************************/
Widget
menubar_pulldown(Widget menushell)
{
	Widget 			pulldown;
	char 				all[100];
	char 				number[5];
	WSTRUCT 		*ptr;
	int 				counter;
	char 				*name;
	Arg					args[5];

	/* make the name unique */
	name = "pulldown_";
	counter = get_counter();
	sprintf(number, "%d", counter);
	strcpy(all, name);
	strcat(all, number);

	/* get the data structure - sets tree_ptr too */
	ptr = get_wstruct();

  /* specific resources */
  XtSetArg(args[0], XmNrowColumnType, XmMENU_PULLDOWN);
  record_resource(ptr, XmNrowColumnType, "XmMENU_PULLDOWN", 13);

  pulldown = XtCreateWidget(all, xmRowColumnWidgetClass, menushell, args, 1);
                              
	/* fill in the widget struct */
	ptr->key = counter;
	strcpy(ptr->appname, all);

	/* fill in the widget struct */
	ptr->instance = pulldown;

	ptr->managed = False;

	ptr->parent = get_parent_key(menushell);
	strcpy(ptr->class, get_widget_classname(pulldown));

	/* TBD */
	ptr->global = True;
	ptr->perm = True;
	ptr->fixed = True;

	install_select_handlers(ptr->instance);

	populate_wtree();
	unselect(selected_widget);
	select_widget(ptr->instance);
      
	return (pulldown);
}
