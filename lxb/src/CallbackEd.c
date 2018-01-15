/**************************************************
*
* File: CallbackEd.c - application source file
*
*		The GUI creation for the callback editor.
*
*		Originally created by lxb.
*
*    Copyright (C) 1997  Bruce Parkin
*
**************************************************/

/* include files */
#include <stdio.h>

#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/PushB.h>
#include <Xm/Separator.h>
#include <Xm/Label.h>
#include <Xm/TextF.h>
#include <Xm/DrawingA.h>
#include <X11/Shell.h>

#include "lxb.h"
#include "color.h"
#include "CallbackEd.h"
#include "callbacks.h"

/* local variables */
static Widget called_shell = NULL;
static Widget textF_5;
static Widget textF_4;

/* local functions */
static void
build_called(Widget parent);

static void
accept_callback(Widget w, XtPointer client_data, XtPointer call_data);    
static void
cancel_callback(Widget w, XtPointer client_data, XtPointer call_data);    
static void
delete_callback(Widget w, XtPointer client_data, XtPointer call_data);

/**************************************************
* Function: 
**************************************************/
static void
delete_callback(Widget w, XtPointer client_data, XtPointer call_data)
{ 
	char *ctype = XmTextFieldGetString(textF_5);

	remove_callback(ctype);
	XtFree(ctype);

	XmTextFieldSetString(textF_4, "");
}
/**************************************************
* Function: 
**************************************************/
static void
accept_callback(Widget w, XtPointer client_data, XtPointer call_data)
{ 
	char *cname = XmTextFieldGetString(textF_4);
	char *ctype = XmTextFieldGetString(textF_5);

	record_callback(ctype, cname);
	XtFree(ctype);
	XtFree(cname);
}
/**************************************************
* Function: 
**************************************************/
static void
cancel_callback(Widget w, XtPointer client_data, XtPointer call_data)
{ 
	XtPopdown(called_shell);
}
/**************************************************
* Function: display_called
**************************************************/
void
display_called(Widget parent, char *callback_type)
{
	Arg args[10];
	int i;
	char *function_name;

	if (called_shell == NULL) {

		i=0;
		XtSetArg(args[i], XmNallowShellResize, True);i++;
		XtSetArg(args[i], XmNdeleteResponse, XmDO_NOTHING);i++;
		XtSetArg(args[i], XmNmwmFunctions,
											MWM_FUNC_RESIZE|MWM_FUNC_MOVE|MWM_FUNC_MINIMIZE|MWM_FUNC_MAXIMIZE);i++;
		XtSetArg(args[i], XmNtitle, "Not Working Yet: Callback Editor");i++;
		XtSetArg(args[i], XmNiconName, "CallEd");i++;

		XtSetArg(args[i], XmNgeometry, "365x180+745+235");i++;

		called_shell = XtCreatePopupShell("called", topLevelShellWidgetClass, parent, args, i);
		build_called(called_shell);
	};

	/* see if name is set - get from list */
	function_name = get_callback(callback_type);

	if (function_name == NULL)
		XmTextFieldSetString(textF_4, "");
	else{

		XmTextFieldSetString(textF_4, function_name);
		XmTextFieldSetInsertionPosition(textF_4, strlen(function_name));
		XtFree(function_name);
	};
	
	XmTextFieldSetString(textF_5, callback_type);
	XtPopup(called_shell, XtGrabNone);
}
/**************************************************
* Function: build_called
**************************************************/
static void
build_called(Widget parent)
{
	Arg args[100];
	XmString xmstrings[10];
	XmFontList fontlist;
	Widget drawingArea_1;
	Widget label_2;
	Widget label_3;
	Widget pushButton_6;
	Widget pushButton_7;
	Widget pb;
	Widget separator_9;

	XtSetArg(args[0], XmNy, 0);
	XtSetArg(args[1], XmNx, 0);
	XtSetArg(args[2], XmNresizePolicy, XmRESIZE_NONE);
	XtSetArg(args[3], XmNheight, 60);
	XtSetArg(args[4], XmNwidth, 370);

	drawingArea_1 = XtCreateManagedWidget("drawingArea_1", xmDrawingAreaWidgetClass, 
																				parent, args, 5);

	xmstrings[0] = XmStringCreateSimple("Callback Name:");
	XtSetArg(args[0], XmNlabelString, xmstrings[0]);
	XtSetArg(args[1], XmNy, 78);
	XtSetArg(args[2], XmNx, 10);
	label_2 = XtCreateManagedWidget("label_2", xmLabelWidgetClass, drawingArea_1, args, 3);

	XmStringFree(xmstrings[0]);

	xmstrings[0] = XmStringCreateSimple("Callback Type:");
	XtSetArg(args[0], XmNlabelString, xmstrings[0]);
	XtSetArg(args[1], XmNy, 15);
	XtSetArg(args[2], XmNx, 10);
	label_3 = XtCreateManagedWidget("label_3", xmLabelWidgetClass, drawingArea_1, args, 3);

	XmStringFree(xmstrings[0]);

	XtSetArg(args[0], XmNy, 70);
	XtSetArg(args[1], XmNx, 118);
	XtSetArg(args[2], XmNcolumns, 25);
	textF_4 = XtCreateManagedWidget("textF_4", xmTextFieldWidgetClass, drawingArea_1, args, 2);

	XtSetArg(args[0], XmNhighlightThickness, 0);
	XtSetArg(args[1], XmNcursorPositionVisible, False);
	XtSetArg(args[2], XmNborderWidth, 0);
	XtSetArg(args[3], XmNsensitive, True);
	XtSetArg(args[4], XmNshadowThickness, 0);
	XtSetArg(args[5], XmNbackground, get_pixel("light gray"));
	XtSetArg(args[6], XmNeditable, False);
	XtSetArg(args[7], XmNy, 10);
	XtSetArg(args[8], XmNx, 120);
	XtSetArg(args[9], XmNcolumns, 25);
	textF_5 = XtCreateManagedWidget("textF_5", xmTextFieldWidgetClass, drawingArea_1, args, 9);

	xmstrings[0] = XmStringCreateSimple("Accept");
	XtSetArg(args[0], XmNlabelString, xmstrings[0]);
	XtSetArg(args[1], XmNy, 142);
	XtSetArg(args[2], XmNx, 10);
	pushButton_6 = XtCreateManagedWidget("pushButton_6", xmPushButtonWidgetClass, drawingArea_1, args, 3);

	XmStringFree(xmstrings[0]);

	XtAddCallback(pushButton_6, XmNactivateCallback, accept_callback, NULL);
  
	xmstrings[0] = XmStringCreateSimple("Delete");
	XtSetArg(args[0], XmNlabelString, xmstrings[0]);
	XtSetArg(args[1], XmNy, 142);
	XtSetArg(args[2], XmNx, 150);
	pb = XtCreateManagedWidget("pb", xmPushButtonWidgetClass, drawingArea_1, args, 3);

	XmStringFree(xmstrings[0]);
	XtAddCallback(pb, XmNactivateCallback, delete_callback, NULL);

	xmstrings[0] = XmStringCreateSimple("Dismiss");
	XtSetArg(args[0], XmNlabelString, xmstrings[0]);
	XtSetArg(args[1], XmNy, 142);
	XtSetArg(args[2], XmNx, 300);
	pushButton_7 = XtCreateManagedWidget("pushButton_7", xmPushButtonWidgetClass, drawingArea_1, args, 3);

	XmStringFree(xmstrings[0]);

	XtAddCallback(pushButton_7, XmNactivateCallback, cancel_callback, NULL);
  
	XtSetArg(args[0], XmNheight, 10);
	XtSetArg(args[1], XmNy, 121);
	XtSetArg(args[2], XmNx, 10);
	XtSetArg(args[3], XmNwidth, 340);
	separator_9 = XtCreateManagedWidget("separator_9", xmSeparatorWidgetClass, drawingArea_1, args, 4);

}
