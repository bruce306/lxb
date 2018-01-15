/**************************************************
*
* File: select.c
*
*    Copyright (C) 1997  Bruce Parkin 
*
**************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/cursorfont.h>
#include "lxb.h"
#include "data.h"
#include "populate.h"
#include "ResourceEd.h"
#include "select.h"

/* local variables */
static Cursor move_cursor;

/* local functions */
static void
enter_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag); 
static void
leave_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag);

/**************************************************
 *
 * Function: 
 *
 **************************************************/
void 
init_select_stuff(Widget w)
{
	move_cursor = XCreateFontCursor(XtDisplay(w), XC_crosshair);
}
/**************************************************
 *
 * Function: select
 *
 * w is the widget to make the "selected" one
 *
 **************************************************/
void 
select_widget(Widget w)
{
	Arg args[5];
	int status;

	if (verbose >6)
		printf("selecting widget:	%s\n", XtName(w));

	if (w == NULL)
		return;

	/* did this cause on Linux it would hang 50 here... */
	if (!XtIsShell(w)){
		XtSetArg(args[0], XmNborderWidth, 2);
		XtSetValues(w, args, 1);
	};

	selected_widget = w;
	status = select_wtree_node(w);
	if (status == NOTOK)
		fprintf(stderr, "(select_widget): could not select node in tree\n");

/*
  XtAddEventHandler(w, EnterWindowMask, True, enter_handler, NULL);
  XtAddEventHandler(w, LeaveWindowMask, True, leave_handler, NULL);
	XDefineCursor(XtDisplay(w), XtWindow(w), move_cursor);
*/

	init_resource_editor(w);
}
/**************************************************
 *
 * Function: unselect
 *
 * w is the widget to "unselect"
 *
 **************************************************/
void 
unselect(Widget w)
{
	Arg args[2];

	if (w == NULL)
		return;

	/* did this cause on Linux it would hang 50 here... */
	if (!XtIsShell(w)){
		XtSetArg(args[0], XmNborderWidth, 0);
		XtSetValues(selected_widget, args, 1);
	};

	unselect_wtree_node();
	selected_widget = NULL;
	clear_resource_editor();

/*
  XtRemoveEventHandler(w, XtAllEvents, True, enter_handler, NULL);  
  XtRemoveEventHandler(w, XtAllEvents, True, leave_handler, NULL);  
	XUndefineCursor(XtDisplay(w), XtWindow(w));
*/
}
/**************************************************
 *
 * Function: 
 *
 **************************************************/
static void
enter_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag)
{
  XButtonEvent *xb;
  Arg args[5];
  Window win;
  WSTRUCT *wptr;

	if (verbose >8)
    printf("called enter handler\n");        

}
/**************************************************
 *
 * Function: 
 *
 **************************************************/
static void
leave_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag)
{
  XButtonEvent *xb;
  Arg args[5];
  Window win;
  WSTRUCT *wptr;

	if (verbose >8)
    printf("called leave handler\n");        

}
