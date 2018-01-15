/**************************************************
*
* File: menubar.c
*
*    Copyright (C) 1997  Bruce Parkin 
*
**************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <Xm/ToggleB.h>
#include <Xm/Separator.h>
#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/CascadeB.h>

#include "lxb.h"
#include "data.h"
#include "select.h"
#include "mhandlers.h"
#include "recres.h"

#include "menushell.h"
#include "menubar.h"

/**************************************************
 *
 * Function: menubar
 *
 **************************************************/
Widget
create_menubar(Widget parent)
{
	Arg 			args[10];
	int 			n;
	char 			*name;
	char 			all[100];
	char 			number[5];
	WSTRUCT 	*ptr;
	int				counter;
	Widget 		menubar;

	/* make a string name for the widget */
	name = "menubar_";

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
  XtSetArg(args[n], XmNx, 0);n++;
  XtSetArg(args[n], XmNy, 0);n++;

	XtSetArg(args[n], XmNwidth, 100);n++;
	XtSetArg(args[n], XmNheight, 30);n++;

  record_resource(ptr, XmNwidth, "100", -999);
  record_resource(ptr, XmNheight, "30", -999);

	/* specific resources */
	XtSetArg(args[n], XmNrowColumnType, XmMENU_BAR);n++;
  record_resource(ptr, XmNrowColumnType, "XmMENU_BAR", 13);

  /* set constraints - on my version of Motif the Menubar would
		lose it's leftAttachment at times... ARG!!!! */
  if (XtClass(parent) == xmFormWidgetClass){

    /* due to XmNrubberPosition on form parent */
    XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);(n)++;
    XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);(n)++;
    record_resource(ptr, XmNtopAttachment, "XmATTACH_FORM", 6);
    record_resource(ptr, XmNleftAttachment, "XmATTACH_FORM", 6);
  };         

	/* make the menubar */
  menubar = XtCreateWidget(all, xmRowColumnWidgetClass, parent, args, n);

	/* fill in the widget struct */
	strcpy(ptr->appname, all);
	ptr->instance = menubar;

	/* pointer to parent */
	ptr->parent = get_parent_key(parent);

	/* record the widget class */
	strcpy(ptr->class, get_widget_classname(menubar));

	install_select_handlers(menubar);

	XtManageChild(menubar);
	return (menubar);
}
