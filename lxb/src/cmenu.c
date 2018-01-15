/**************************************************
 *
 * 	File: cmenu.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 *
 * 	This contains the first/Master function. It
 *	checks validity, and creates the required menu
 *	componants.
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/CascadeB.h>

#include "lxb.h"
#include "data.h"
#include "populate.h"
#include "select.h"
#include "pulldown.h"
#include "menubar.h"
#include "cascade.h"

#include "cmenu.h"

/* local prototypes */
static int
check_cascade_button(Widget *real_parent, unsigned char *parent_type);

/**************************************************
 *
 * Function: create_menu
 *
 *	icon names: "MenuBar" "MenuPB" "MenuCB" "MenuSep"
 *
 *	Parent is the "Selected" widget (TBD).
 *
 **************************************************/
int
create_menu(Widget parent, Widget icon)
{
	Widget w;
	char *name;
	int status;
	unsigned char parent_type;
	Widget real_parent;

	name = XtName(icon);
	status = OK;

	if ( (strcmp(name, "MenuBar") == 0) ) {
		
		w = create_menubar(parent);

  } else if ( (strcmp(name, "MenuCB") == 0) ) {

		status = check_cascade_button(&real_parent, &parent_type);
		if (status == OK){

			/* create the cascade button */
			w = create_cascade_button(parent, parent_type);
		};

	} else {
		fprintf(stderr, "create_menu: Not yet implemented.\n");
	};

	if (status != OK)
		fprintf(stderr, "ERROR (create_menu): menu creation failed\n");

	else {

		populate_wtree();
		unselect(selected_widget);
		select_widget(w);
	};

	return (status);
}
/**************************************************
 *
 * Function: check_cascade_button
 *
 *	On entrance, the desired cascade button is to be
 *	placed either in a "menubar" or a "pulldown", both
 *	who's real types are RowColumn.
 *
 **************************************************/
static int
check_cascade_button(Widget *real_parent, unsigned char *parent_type) 
{
	Arg args[3];
	Widget pulldown;

	if ( (XtClass(selected_widget) == xmRowColumnWidgetClass) ){

		/* Cascade button goes in a Menubar; the selected_widget is the real parent */
		*real_parent = selected_widget;
		*parent_type = XmMENU_BAR;

	} else {

		fprintf(stderr, "Error: Parent of Cascade button must be RowColumn (Menubar) \n");
		return (NOTOK);
	};

	return (OK);
}
