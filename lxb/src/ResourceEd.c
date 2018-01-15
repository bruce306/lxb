/**********************************************************************************
*
* 	File: resed.c - Builds the GUI for the resource editor and serves as the 
*			master header file for associated src files.
*
*		Copyright (C) 1997  Bruce Parkin 
*
*********************************************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <X11/Xmu/Editres.h>      
#include <Xm/Frame.h>
#include <Xm/RowColumn.h>
#include <Xm/Separator.h>
#include <Xm/List.h>
#include <Xm/Form.h>
#include <Xm/DrawingA.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <Xm/TextF.h>
#include <Xm/ToggleB.h>
#include <Xm/PushB.h>
#include <Xm/Label.h>
#include <X11/Shell.h>

#include "lxb.h"
#include "forms.h"
#include "util.h"
#include "data.h"
#include "selected.h"
#include "show_res.h"
#include "TextObject.h"
#include "populate.h"
#include "select.h"

#include "ResourceEd.h"

/* global variables */
int	resource_type = RESOURCES;
char *resource_name = "";				/* selected resource from list */

Widget  name_list;
Widget  value_list;
Widget  value_text;
Widget  current_name;
Widget  current_class;    
Widget  local_button;    
Widget  global_button;    

/* local prototypes */
static int
set_current_class(Widget w);
static int
set_current_name(Widget w);
static int
set_widget_scope(Widget w);

static Boolean
SetWidgetName(Widget w, char *txt);

static void
ok_callback(Widget w, XtPointer client_data, XtPointer call_data);

static void
scope_callback(Widget w, XtPointer client_data, XtPointer call_data);

/* local variables */
static Widget editor_shell = NULL;
static Boolean resed_displayed = False; 	/* indicates if it is currently popped up */
static Widget current_edit = NULL;

/**************************************************
 *
 * Function: make_resource_editor
 *
 * make the resource editor 
 *
 **************************************************/
void
build_resource_editor(Widget parent)
{
	Arg args[10];
	int i;
	XmString	cancel;
	XmString	xm;
	XmString	set;
	Widget sep;
	Widget rowcol;
	Widget button;
	Widget bull_b;
	Widget cancel_button;
	Widget set_button;
	Widget label;
	Widget editor_form;
	Widget value_frame;
	Widget value_drawa;
	Widget value_label;
	Widget txtobj;
	Widget rbox, frame;
	Widget w, scope;

	i=0;
	XtSetArg(args[i], XmNallowShellResize, True);i++;
	XtSetArg(args[i], XmNdeleteResponse, XmDO_NOTHING);i++;
	XtSetArg(args[i], XmNmwmFunctions,
										MWM_FUNC_RESIZE|MWM_FUNC_MOVE|MWM_FUNC_MINIMIZE|MWM_FUNC_MAXIMIZE);i++;
	XtSetArg(args[i], XmNtitle, "LXB Resource Editor");i++;
	XtSetArg(args[i], XmNiconName, "ResEd");i++;

	editor_shell = XtCreatePopupShell("editor_shell", topLevelShellWidgetClass, parent, args, i);

	/* to debug with editres */
	XtAddEventHandler(editor_shell, (EventMask)0, True, _XEditResCheckMessages, NULL);

	editor_form= XtCreateManagedWidget("editor_form", xmFormWidgetClass, editor_shell, NULL, 0);

	/* widget name display/entry field */
	txtobj = new_text_object(editor_form, 0,0, "Widget Name: ", 0, 25, SetWidgetName, &current_name);

	/* Class of current widget */
	xm= XmStringCreateSimple("Widget Class: ");
	i=0;
	XtSetArg(args[i], XmNlabelString, xm);i++;
	XtSetArg(args[i], XmNalignment, XmALIGNMENT_BEGINNING);i++;
	XtSetArg(args[i], XmNlabelString, xm);i++;
	current_class = XtCreateManagedWidget("current_class", xmLabelWidgetClass, editor_form, args, i);

	XmStringFree(xm);

	i=0;
	xm= XmStringCreateSimple("Scope: ");
	XtSetArg(args[i], XmNlabelString, xm);i++;
	XtSetArg(args[i], XmNalignment, XmALIGNMENT_BEGINNING);i++;
	XtSetArg(args[i], XmNwidth, 100);i++;
	XtSetArg(args[i], XmNrecomputeSize, False);i++;
	scope = XtCreateManagedWidget("scope_label", xmLabelWidgetClass, editor_form, args, i);
	XmStringFree(xm);

	/* RadioBox for local/global variable indicator */
	i=0;
	XtSetArg(args[i], XmNshadowType, XmSHADOW_OUT);i++;
	XtSetArg(args[i], XmNshadowThickness, 2);i++;
	frame = XtCreateManagedWidget("frame", xmFrameWidgetClass, editor_form, args, i);

	i=0;
	XtSetArg(args[i], XmNorientation, XmHORIZONTAL);i++;
	XtSetArg(args[i], XmNentryAlignment, XmALIGNMENT_CENTER);i++;
	XtSetArg(args[i], XmNradioBehavior, True);i++;
	rbox = XtCreateManagedWidget("rbox", xmRowColumnWidgetClass, frame, args, i);

	i=0;
	xm= XmStringCreateSimple("Local");
	XtSetArg(args[i], XmNlabelString, xm);i++;
	XtSetArg(args[i], XmNhighlightThickness, 0);i++;
	local_button = XtCreateManagedWidget("local", xmToggleButtonWidgetClass, rbox, args, i);
	XmStringFree(xm);

	XtAddCallback(local_button, XmNarmCallback, scope_callback, NULL);

	i=0;
	xm= XmStringCreateSimple("Global");
	XtSetArg(args[i], XmNhighlightThickness, 0);i++;
	XtSetArg(args[i], XmNlabelString, xm);i++;
	global_button = XtCreateManagedWidget("global", xmToggleButtonWidgetClass, rbox, args, i);
	XmStringFree(xm);

	XtAddCallback(global_button, XmNarmCallback, scope_callback, NULL);

	/* list for names of all resources for widget */
	i=0;
	XtSetArg(args[i], XmNvisibleItemCount, 20);i++;
	XtSetArg(args[i], XmNselectionPolicy, XmSINGLE_SELECT);i++;
	name_list = XmCreateScrolledList(editor_form, "name_list", args, i);
	XtManageChild(name_list);

	/* called when a resource NAME is clicked on */
	XtAddCallback(name_list, XmNsingleSelectionCallback, selection_callback, NULL);

	cancel = XmStringCreateSimple("");
	i=0;
	XtSetArg(args[i], XmNlabelString, cancel);i++;
	XtSetArg(args[i], XmNalignment, XmALIGNMENT_BEGINNING);i++;
	XtSetArg(args[i], XmNlabelString, cancel);i++;
	value_label= XtCreateManagedWidget("value_label", xmLabelWidgetClass, editor_form, args, i);

	XmStringFree(cancel);

	i=0;
	XtSetArg(args[i], XmNshadowType, XmSHADOW_IN);i++;
	value_frame = XtCreateManagedWidget("value_frame", xmFrameWidgetClass, editor_form, args, i);

	i=0;
	XtSetArg(args[i], XmNmarginHeight, 0);i++;
	XtSetArg(args[i], XmNmarginWidth, 0);i++;
	value_drawa= XtCreateManagedWidget("value_drawa", xmDrawingAreaWidgetClass, value_frame, args, i);

	/* label for value input field */
	xm= XmStringCreateSimple("Value: ");
	i=0;
	XtSetArg(args[i], XmNy, 10);i++;
	XtSetArg(args[i], XmNlabelString, xm);i++;
	XtSetArg(args[i], XmNalignment, XmALIGNMENT_BEGINNING);i++;
	label = XtCreateManagedWidget("value_label", xmLabelWidgetClass, value_drawa, args, i);

	XmStringFree(xm);

	/* text input field for resource value */
	XtSetArg(args[0], XmNcolumns, 25);
	XtSetArg(args[1], XmNx, 50);
	value_text = XtCreateManagedWidget("txtField", xmTextFieldWidgetClass, value_drawa, args, 2);
	XtAddCallback(value_text, XmNactivateCallback, ok_callback, NULL);

  xm = XmStringCreateSimple("OK");
  XtSetArg(args[0], XmNlabelString, xm);
	XtSetArg(args[1], XmNx, 275);
	XtSetArg(args[2], XmNy, 5);
  button = XtCreateManagedWidget("ok", xmPushButtonWidgetClass, value_drawa, args, 3);     
	XmStringFree(xm);
	XtAddCallback(button, XmNactivateCallback, ok_callback, NULL);

	/* the list of possible new resource values, located below text input field */
	i=0;
	XtSetArg(args[i], XmNvisibleItemCount, 3);i++;
	XtSetArg(args[i], XmNscrollBarDisplayPolicy, XmSTATIC);i++;
	XtSetArg(args[i], XmNselectionPolicy, XmSINGLE_SELECT);i++;
	value_list = XmCreateScrolledList(editor_form, "value_list", args, i);
	XtManageChild(value_list);

	XtAddCallback(value_list, XmNsingleSelectionCallback, values_selection_callback, NULL);

	/* area for 3 buttons to show callback, constraint, or resource editor */
	i=0;
	XtSetArg(args[i], XmNorientation, XmHORIZONTAL);i++;
	XtSetArg(args[i], XmNpacking, XmPACK_COLUMN);i++;
	XtSetArg(args[i], XmNentryAlignment, XmALIGNMENT_CENTER);i++;
	rowcol = XtCreateManagedWidget("rowcol", xmRowColumnWidgetClass, editor_form, args, i);

	/* button to bring up callbacks editor */
	xm = XmStringCreateSimple("Callbacks");
	i=0;
	XtSetArg(args[i], XmNlabelString, xm);i++;
	button = XtCreateManagedWidget("call_button", xmPushButtonWidgetClass, rowcol, args, i);

	XtAddCallback(button, XmNactivateCallback, call_callback, NULL);
	XmStringFree(xm);

	/* button to bring up constraints editor */
	xm = XmStringCreateSimple("Constraints");
	i=0;
	XtSetArg(args[i], XmNlabelString, xm);i++;
	button = XtCreateManagedWidget("constr_button", xmPushButtonWidgetClass, rowcol, args, i);

	XtAddCallback(button, XmNactivateCallback, constr_callback, NULL);
	XmStringFree(xm);

	/* button to show resources */
	xm = XmStringCreateSimple("Resources");
	i=0;
	XtSetArg(args[i], XmNlabelString, xm);i++;
	button = XtCreateManagedWidget("res_button", xmPushButtonWidgetClass, rowcol, args, i);

	XtAddCallback(button, XmNactivateCallback, res_callback, NULL);
	XmStringFree(xm);

	/* top, bottom, left, right */
	LxbSetConstraints (txtobj,
					XmATTACH_FORM, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
					editor_form, NULL, editor_form, editor_form);

	/* top, bottom, left, right */
	LxbSetOffsets(txtobj, 5, 0, 0, 0);

	LxbSetConstraints (current_class,
					XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
					txtobj, NULL, editor_form, editor_form);

	/* top, bottom, left, right */
	LxbSetOffsets(current_class, 10, 0, 2, 0);

	/* top, bottom, left, right */
	LxbSetConstraints (scope,
					XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_NONE,
					current_class, NULL, editor_form, NULL);

	/* top, bottom, left, right */
	LxbSetOffsets(scope, 20, 0, 2, 0);

	/* top, bottom, left, right */
	LxbSetConstraints (frame,
					XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_WIDGET, XmATTACH_NONE,
					current_class, NULL, scope, NULL);

	/* top, bottom, left, right */
	LxbSetOffsets(frame, 15, 0, 0, 0);

	LxbSetConstraints (XtParent(name_list),
					XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
					frame, NULL, editor_form, editor_form);

	/* top, bottom, left, right */
	LxbSetOffsets(XtParent(name_list), 10, 0, 0, 0);

	/* top, bottom, left, right */
	LxbSetConstraints (value_label,
					XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
					XtParent(name_list), NULL, editor_form, editor_form);

	/* top, bottom, left, right */
	LxbSetConstraints (value_frame,
					XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
					value_label, NULL, editor_form, editor_form);

	/* top, bottom, left, right */
	LxbSetConstraints (XtParent(value_list),
					XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
					value_frame, NULL, editor_form, editor_form);

	/* top, bottom, left, right */
	LxbSetConstraints (rowcol,
					XmATTACH_WIDGET, XmATTACH_FORM, XmATTACH_FORM, XmATTACH_FORM,
					XtParent(value_list), editor_form, editor_form, editor_form);

	XtManageChild(editor_shell);
	XtPopup(editor_shell, XtGrabNone);

	resed_displayed = True;
}
/**************************************************
*
* Function: 
*
**************************************************/
static Boolean
SetWidgetName(Widget w, char *txt)
{
	Boolean status = 1;

	if (selected_widget != NULL){

		status = change_widget_name(selected_widget, txt);
		if (status == 1){

			/* change the name in the WH display */
			populate_wtree();

			/* reselect the selected widget */
			select_widget(selected_widget);
		};

	};

	return (status);
}
/**************************************************
*
* Function: 
*
**************************************************/
static void
ok_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	set_selected_resource(selected_widget);
}
/**************************************************
*
* Function: 
*
**************************************************/
static void
scope_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	WSTRUCT *wptr;

	if (selected_widget == NULL)
		return;

	wptr = widget_ptr(selected_widget); 
	if (wptr == NULL)

		fprintf(stderr, "Cannot set scope: internal error\n");

	else {

		if (!strcmp(XtName(w), "global"))

			wptr->global = True;

		else

			wptr->global = False;
	};
}
/**************************************************
 *	Function:	display_resed_editor
 *
 *	For play mode only.
 *
 **************************************************/
void
redisplay_resed_editor()
{
	if (resed_displayed == True)
		XtMapWidget(editor_shell);
}
/**************************************************
 *	Function:	hide_resed_editor
 *
 *	For play mode only.
 *
 **************************************************/
void
hide_resed_editor()
{
	if (resed_displayed == True)
		XtUnmapWidget(editor_shell);
}
/**********************************************************************
*
* Function: clear_resource_editor - remove all widget data
*
**********************************************************************/
void
clear_resource_editor()
{
	XmString xm;
	Arg args[5];

	/* clear widget name */
	XmTextSetString(current_name, "");
	XmTextFieldSetInsertionPosition(current_name, 0);	
	
	/* clear widget class */
	xm = XmStringCreateLtoR("Widget Class: ", XmSTRING_DEFAULT_CHARSET);
	XtSetArg (args[0], XmNlabelString, xm);
	XtSetValues(current_class, args, 1);
	XmStringFree (xm);

	/* clear the scope RadioBox */
	XmToggleButtonSetState(global_button, False, False);
	XmToggleButtonSetState(local_button, False, False);

  /* clear the lists */
  XmListDeleteAllItems(name_list);
  XmListDeleteAllItems(value_list);

  /* clear the text "value" widget */
  XmTextSetString(value_text, "");  

	/* no widget being edited */
	current_edit = NULL;
}
/**********************************************************************
*
* Function: init_resource_editor - init the resource editor with 
*		resources, name, and other data about the selected widget
*
*		w: the widget to be edited - the selected widget
*
**********************************************************************/
void
init_resource_editor(Widget w)
{
	int status;

	if (current_edit == w)
		
		/* current widget being edited - saves repaint */
		return;

	else {

		/* of selected widget */
		status = set_current_name(w);
		if (!status)
			fprintf(stderr, "Problems getting selected widget's name\n");
		
		/* of selected widget */
		status = set_current_class(w);
		if (!status)
			fprintf(stderr, "Problems getting selected widget's class\n");

		status = set_widget_scope(w);
		if (!status)
			fprintf(stderr, "Problems getting selected widget's scope\n");

		/* display standard resources in top list widget */
		if (status)
			show_resources();
		else
			fprintf(stderr, "Could not dispaly selected widget's resources\n");

		/* current widget being edited */
		current_edit = w;
	};
}
/**********************************************************************
*
* Function: show_resource_editor - show the resource editor window
*
*		w: the widget to be edited
*
**********************************************************************/
int
show_resource_editor(Widget w)
{
	int status;

	/* of selected widget */
	status = set_current_name(w);
	if (!status)
		fprintf(stderr, "Problems getting selected widget's name\n");
	
	/* of selected widget */
	status = set_current_class(w);
	if (!status)
		fprintf(stderr, "Problems getting selected widget's class\n");

	status = set_widget_scope(w);
	if (!status)
		fprintf(stderr, "Problems getting selected widget's scope\n");

	/* defaults to normal resources displayed in top list widget */
	show_resources();

	XtManageChild(editor_shell);

	resed_displayed = True;
	return (OK);
}
/**************************************************
 *
 *	Function: set_widget_scope
 *
 **************************************************/
static int
set_widget_scope(Widget w)
{
	Arg args[3];
	WSTRUCT *wptr;
	int status = 1;

	wptr = widget_ptr(w); 

	if (wptr == NULL)

		status = 0;

	else {

		if (wptr->global)
	
			XmToggleButtonSetState(global_button, True, True);

		else

			XmToggleButtonSetState(local_button, True, True);

	};

	return (status);
}
/**************************************************
 *
 *	Function: set_current_class
 *
 **************************************************/
static int
set_current_class(Widget w)
{
	Arg args[3];
	XmString xmstr = NULL;
	char *name = NULL;
	int status = 0;
	char all[100];

	strcpy(all, "Widget Class:     ");
	name = get_widget_classname(w); 
	if (name != NULL){
		status = 1;
	} else {
		name = "";
	};

	strcat(all, name);

	xmstr = XmStringCreateLtoR(all, XmSTRING_DEFAULT_CHARSET);

	XtSetArg (args[0], XmNlabelString, xmstr);
	XtSetValues(current_class, args, 1);

	XmStringFree (xmstr);

	return (status);
}
/**************************************************
 *
 *	Function: set_current_name
 *
 **************************************************/
static int
set_current_name(Widget w)
{
	Arg args[3];
	char *name = NULL;
	int status = 0;

	name = widget_name(w); 
	if (name != NULL){
		status = 1;
	} else {
		name = "";
	};

	XmTextSetString(current_name, name);
	XmTextFieldSetInsertionPosition(current_name, strlen(name));	
	return (status);
}
