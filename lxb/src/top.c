/**************************************************
 *
 * File: top.c - GUI code for main area
 *
 *    Copyright (C) 1995-2002  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/Separator.h>
#include <Xm/ScrolledW.h>
#include <Xm/Frame.h>
#include <Xm/Text.h>
#include "forms.h"
#include "Wtree.h"
#include "menu.h"
#include "select.h"
#include "top.h"
#include "lxb.h"

/* local variables */
static Widget msg_area;

static void
deselect_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag);

/**************************************************
 *
 * Function: output_message - write error, warning,
 *      or informational message to Message Area.
 *
 *  The clever thing about this function (that I copied
 *  from someone else) is that it can be used to take
 *  almost any datatype input and convert it to string
 *  for output in a Label field. Like a "printf" function.
 *
 *  Thanks to Philip Marsh for converting this to
 *  use stdarg.h
 *
 **************************************************/
void
output_message(const char *fmt, ...)
{
        char msgbuf[250];
        va_list ap;
        static XmTextPosition wpr_position = 0;

        va_start(ap,fmt);

        vsprintf(msgbuf, fmt, ap);

        va_end(ap);

        XmTextInsert(msg_area, wpr_position, msgbuf);
        wpr_position += strlen(msgbuf);
        XtVaSetValues(msg_area, XmNcursorPosition, wpr_position, NULL);
        XmTextShowPosition(msg_area, wpr_position);

}
/**************************************************
 *
 * Function: build_gui
 *
 * parent is the "shell" widget
 *
 **************************************************/
void 
build_gui(Widget parent)
{
	Widget main_window, menubar, wtree_area, status_area;
	Widget sep, sc;
	Widget right_child;
	Widget frame;
	Arg args[12];
	int n;

	/* create the main window */
	main_window = XtCreateManagedWidget ("main_window", xmFormWidgetClass, parent, args, 0);  

	/* create the menubar */
	menubar = build_menu(main_window);


	/* area for names of application, selected and active widgets */
/*
	if (verbose >0)
		printf("make status area\n");
	status_area = build_status_area(main_window);
*/

	XtSetArg(args[0], XmNshadowThickness, 5);
	sep = XtCreateManagedWidget ("sep", xmSeparatorWidgetClass, main_window, args, 1);  

	/* display of widgets in gui being built */
	wtree_area = build_wtree_area(main_window, &right_child);


	XtAddEventHandler(tree, ButtonPressMask|ButtonReleaseMask, True, deselect_handler, NULL);

	
	/* message output area */
	XtSetArg(args[0], XmNshadowType, XmSHADOW_OUT);
	XtSetArg(args[1], XmNshadowThickness, 3);       
	frame = XtCreateManagedWidget("frame", xmFrameWidgetClass, right_child, args, 2);

	n=0;
	XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT);n++;
	XtSetArg(args[n], XmNscrollHorizontal, False);n++;
	XtSetArg(args[n], XmNcursorPositionVisible, False);n++;
	XtSetArg(args[n], XmNautoShowCursorPosition, True);n++;
	XtSetArg(args[n], XmNblinkRate, 0);n++;
	XtSetArg(args[n], XmNwordWrap, True);n++;
	XtSetArg(args[n], XmNhighlightThickness, 0);n++;
	XtSetArg(args[n], XmNeditable, False);n++;
	XtSetArg(args[n], XmNverifyBell, False);n++;
	msg_area = XmCreateScrolledText(frame, "msg_area", args, n);
	XtManageChild(msg_area);

	LxbSetConstraints (frame,
										XmATTACH_FORM, XmATTACH_FORM, XmATTACH_FORM, XmATTACH_FORM,
										right_child, right_child, right_child, right_child);

	/* arrange objects in main window form */

	/* top, bottom, left, right */
	LxbSetConstraints (menubar,
										XmATTACH_FORM, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
										main_window, NULL, main_window, main_window);

	/* top, bottom, left, right */
/*
	LxbSetConstraints (status_area,
										XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
										menubar, NULL, main_window, main_window);

	LxbSetConstraints (sep,
										XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
										menubar, NULL, main_window, main_window);
*/

	/* top, bottom, left, right */
	LxbSetConstraints (wtree_area,
										XmATTACH_WIDGET, XmATTACH_FORM, XmATTACH_FORM, XmATTACH_FORM,
										menubar, main_window, main_window, main_window);

	output_message("\n\n\n\nWelcome to lxb.");
}

/******************************************************************
*
* Function: So that when the user clicks MB1 on the wtree display
*   area all widgets become unselected. Not really needed, but
*   fills an intuitive need of mine...
*
******************************************************************/
static void
deselect_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag)
{
	unselect(selected_widget);
}           
