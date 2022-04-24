/******************************************************************************
*
* File: text_object.c - utility functions used in the creation of text objects.
*
*		A text object is an instance of a TextField and 2 PushButtons in a
*		RowColumn container widget. Initially, only the text field is visable. 
*		As soon as any text is entered or modified in the field, an "OK" button
*		and a "Cancel" button appears. When the user is done, either the OK button
*		or the Cancel button is pressed.
*
*		The Cancel button will restore the original text and cause both buttons to 
*		dissappear. If the "OK" button is pressed the the user-provided function 
*		is first called	(see the header file for the prototype description). If it
*		returns True the altered text remains and both buttons dissappear; else
*		nothing happens.
*
******************************************************************************/

/* include files */
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/DrawingA.h>
#include <Xm/TextF.h>

#include "text_object.h"

/* Dynamic allocated, since many objects created. Should
	maybe use a linked list, but no need since never destroyed
	Keep private, hidden from user.
*/
typedef struct _textobj{
	Widget text_widget;
	Widget ok;
	Widget cancel;
	char *txt;
	UserProc user_proc;
} TEXT_OBJECT;

/* local prototypes */
static void
cancel_callback(Widget w, XtPointer client_data, XtPointer call_data);
static void
ok_callback(Widget w, XtPointer client_data, XtPointer call_data);
static void
modify_callback(Widget w, XtPointer client_data, XtPointer call_data);

/**************************************************************************
*
* Function: set_textstring - utility function which displays text in the
*		textfield widget and places the insert cursor at the end.
*
*	Inputs:
*		w:		the text widget
*		txt:	the text
*
**************************************************************************/
void
set_textstring(Widget w, char *txt)
{
	XmTextSetString(w, txt);
	XmTextFieldSetInsertionPosition(w, strlen(txt));
}
/***************************************************************************
*
* Function: new_text_object - create a new instance of a text entry field,
*		an OK button, & a Cancel button in a container widget.
*
*	Inputs: 
*		parent:		parent widget
*		x, y:			position of container in parent (ignored depending on parent)
*		columns:	width in characters of text entry field (font from app-defaults)
*		proc:			function called when OK button pushed (prototype in header file)
*		text_widget:	returned value of text widget.
*	
*	Returns: function returns value of the container widget. Also text widget.
*
***************************************************************************/
Widget
new_text_object(Widget parent, Position x, Position y, int columns, UserProc proc, Widget *text_widget)
{
	Widget rowColumn;
	Arg args[6];
	XmString xms;

	TEXT_OBJECT *obj;

	obj = (TEXT_OBJECT *)XtMalloc(sizeof(TEXT_OBJECT));
 	memset(obj, 0, sizeof(TEXT_OBJECT));

	obj->user_proc = proc; 

	XtSetArg(args[0], XmNorientation, XmHORIZONTAL);   
	XtSetArg(args[1], XmNx, x);   
	XtSetArg(args[2], XmNy, y);   
	rowColumn = XtCreateManagedWidget("TextObject", xmRowColumnWidgetClass, parent, args, 3);

	XtSetArg(args[0], XmNcolumns, columns);   
	obj->text_widget = XtCreateManagedWidget("textField", xmTextFieldWidgetClass, rowColumn, args, 1);

	XtAddCallback(obj->text_widget, XmNmodifyVerifyCallback, modify_callback, obj);
	XtAddCallback(obj->text_widget, XmNactivateCallback, ok_callback, obj);

	xms = XmStringCreateSimple("OK");
	XtSetArg(args[0], XmNlabelString, xms);
	XtSetArg(args[1], XmNmappedWhenManaged, False);
	obj->ok = XtCreateManagedWidget("ok", xmPushButtonWidgetClass, rowColumn, args, 2);

	XtAddCallback(obj->ok, XmNactivateCallback, ok_callback, obj);

	XmStringFree(xms);

	xms = XmStringCreateSimple("Cancel");
	XtSetArg(args[0], XmNlabelString, xms);
	XtSetArg(args[1], XmNmappedWhenManaged, False);
	obj->cancel = XtCreateManagedWidget("cancel", xmPushButtonWidgetClass, rowColumn, args, 2);

	XtAddCallback(obj->cancel, XmNactivateCallback, cancel_callback, obj);

	XmStringFree(xms);

	*text_widget = obj->text_widget;
	return(rowColumn);
}
/**********************************************************************
*
* Function: cancel_callback - called when the cancel button is pressed
*		to restore the original value to the text field and unmap the OK
*		and Cancel buttons.
*
***********************************************************************/
static void
cancel_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	TEXT_OBJECT *obj = (TEXT_OBJECT *)client_data;

	XtUnmapWidget(obj->ok);
	XtUnmapWidget(obj->cancel);

	set_textstring(obj->text_widget, obj->txt);

	XtFree(obj->txt);
	obj->txt = NULL;
}
/***********************************************************************
*
* Function: ok_callback - called when the OK button is pressed.
*
*	This calls the user provided function with the current value of the
*	text from the text field; then if it returns True unmaps the OK and 
*	cancel buttons.
*
***********************************************************************/
static void
ok_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	TEXT_OBJECT *obj = (TEXT_OBJECT *)client_data;
	char *x;
	Boolean status;

	if (obj->user_proc != NULL){
		x = XmTextFieldGetString(obj->text_widget);
		status = (*obj->user_proc)(obj->text_widget, x);
		XtFree(x);
	};

	if (status == True){
		XtUnmapWidget(obj->ok);
		XtUnmapWidget(obj->cancel);
		XtFree(obj->txt);
		obj->txt = NULL;
	};
}
/**********************************************************************
*
* Function: modify_callback - called before the text in the text widget
*		is changed. Called for both when user types and XmTextSetString is 
*		used (the later is ignored here).
*		
*		First time user modifies text this will map the OK and cancel 
*		buttons and store a value of the original text string before 
*		modification.
*
***********************************************************************/
static void
modify_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	char *ptr;
	int len;
	XmTextBlock block;
	TEXT_OBJECT *obj = (TEXT_OBJECT *)client_data;
	XmAnyCallbackStruct *xm = (XmAnyCallbackStruct *)call_data;

	/* event field is NULL if program set the text string */
	/* we do not want OK and Cancel buttons unless user changes text */
	if (xm->event != NULL){


		if (obj->txt == NULL){
			obj->txt = XmTextFieldGetString(w);
			XtMapWidget(obj->ok);
			XtMapWidget(obj->cancel);
		};

	}else {

		/* called by program */

		/* can't do this the very first time */
		if (XtIsRealized(w)){

			XtUnmapWidget(obj->ok);
			XtUnmapWidget(obj->cancel);

		};

		/* free existing text in object, if any */
		XtFree(obj->txt);
		obj->txt = NULL;

/*
			block = ((XmTextBlock )((XmTextVerifyCallbackStruct *)call_data)->text);
			ptr = block->ptr;
			len = block->length+1;

			obj->txt = XtMalloc(len);
			memcpy(obj->txt, ptr, len-1);
			obj->txt[len] = '\0';
*/

	};
}
