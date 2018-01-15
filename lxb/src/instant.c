/**************************************************
 *
 * File: instant.c
 *
 *    Copyright (C) 1997  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/MenuShell.h>
#include <Xm/ToggleB.h>
#include <Xm/Separator.h>
#include <Xm/DrawnB.h>
#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <Xm/DrawingA.h>
#include <Xm/Scale.h>
#include <Xm/ArrowB.h>
#include <Xm/CascadeB.h>
#include <Xm/ScrolledW.h>
#include <Xm/ScrollBar.h>
#include <Xm/List.h>

#include "lxb.h"
#include "data.h"
#include "TopShell.h"
#include "select.h"
#include "dialogs.h"
#include "populate.h"
#include "create_simple.h"
#include "create_composite.h"
#include "cscrolled.h"
#include "cmenu.h"
#include "instant.h"
#include "top.h"

/* local protypes */
static int
check_parent_legal(Widget w, Widget icon);
static int 
handle_complex(Widget parent, Widget icon);

/***************************************************************************************
*
* Function: call_instantiate - the toplevel function called when a widget icon is
*		pressed in the pallet. This in turn calls the appropriate creation/instantiation
*		function.
*
**************************************************************************************/
void
call_instantiate(Widget parent, Widget icon, XtPointer client_data)
{
	Widget child;
	int status;
	static Boolean first = True;

	status = OK;

	/* if top most widget then must first create a Shell widget */
	if (parent == NULL) {

		/* make Shell */
		parent = make_appshell();
	};

	/* check to see if the child can be added */
	status = check_parent_legal(parent, icon);
	if (status == OK){

		if (client_data != NULL){

			/* simple ones */
			child = instantiate_widget(parent, client_data);
			
			if (child == NULL){
				status = NOTOK;
			}else {

				if (first){

					/* Done this way because otherwise on Linux the shell and child screwed */
					first = False;
					XtManageChild(XtParent(child));
				};

				populate_wtree();
				unselect(parent);
				select_widget(child);
			};
		
		} else {

			status = handle_complex(parent, icon);
		};
	};

	if (status != OK)
		fprintf(stdout, "Instantiation of widget failed.\n");
}
/**************************************************
 *
 *	Function: check to see if the widget can have children,
 *		and the specific child.
 *
 *	w:	parent
 *	icon: childtype name widget
 *
 **************************************************/
static int
check_parent_legal(Widget w, Widget icon)
{
	int num;
	Arg args[5];
	char *childtype = XtName(icon);

	/* 1st check to see if shell */
	if (w == appShell){

		num=0;
		XtSetArg(args[0], XmNnumChildren, &num);
		XtGetValues(appShell, args, 1);
		if (num >0) {

				fprintf(stdout, "Only one child of the shell widget is allowed.\n");
				fprintf(stdout, "Instantiation of new widget failed.\n");
				return(NOTOK);
		} else {
			return (OK);
		};
	};

	/* frames can have only one child */
	if (XtClass(w) == xmFrameWidgetClass){

		XtSetArg(args[0], XmNnumChildren, &num);
		XtGetValues(w, args, 1);

		if (num >0){
			XBell(XtDisplay(w), 50);
			output_message("\nXmFrame widgets can only have one child");
			fprintf(stderr, "XmFrame widgets can only have one child");
			return (NOTOK);
		};
	};

	if (XtIsSubclass(w, xmPrimitiveWidgetClass)){   

		/* other primitives can't have children */
		fprintf(stderr, "Primitive widget cannot have children\n");

		return(NOTOK);

	} else if (XtIsSubclass(w, xmManagerWidgetClass)){   

		/* check for a few specific ones not legal */

		if ((XtClass(w) == xmScaleWidgetClass)){

			fprintf(stderr, "XmScale widget cannot have children\n");
			return(NOTOK);
		};

	} else if (XtClass(w) == xmMenuShellWidgetClass){

		/* MenuShells can only have RowColumns as children */
		if (strcmp(childtype, "RowCol")){
			
			fprintf(stderr, "Cannot add this type of child widget\n");
			return (NOTOK);
		};

	} else if (!strcmp(childtype, "MenuCB")){

		/* Cascade buttons can only have RowColumns as parents */
		if (XtClass(w) != xmRowColumnWidgetClass){

			fprintf(stderr, "Cannot add this type of child widget\n");
			return (NOTOK);
		};

	};
	return (OK);
}
/***************************************************************************************
 *
 * Function: handle_complex - deal with the more complex widgets
 *
 **************************************************************************************/
static int 
handle_complex(Widget parent, Widget icon)
{
	char *name;
	int status = OK;
	Widget w;

	/* the bothersome ones */
	name = XtName(icon);
	if (!strncmp("Menu", name, 4)){

		status = create_menu(parent, icon);

	} else if ( (strncmp("Scale", name, 4) == 0) ){

		/* composite widget with hidden children */
		w = create_composite(parent, xmScaleWidgetClass);

		populate_wtree();
		unselect(selected_widget);
		select_widget(w);

	} else if ( (strncmp("Scrl", name, 4) == 0) ){

		/* composite widget with hidden children */
		w = create_composite(parent, xmScrolledWindowWidgetClass);

		populate_wtree();
		unselect(selected_widget);
		select_widget(w);

	} else if ( (strncmp("Sc", name, 2) == 0) ){

		status = create_scrolled(selected_widget, name);
		populate_wtree();
	};

	if (status == NOTOK)
		fprintf(stderr, "ERROR: (handle_complex): widget creation failed\n");

	return(status);
}
