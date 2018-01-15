/************************************************************
*
* File: data.c - fuctions to extract data, pointers to, etc
*		from the master linked list of GUI being built.
*
*    Copyright (C)  1997  Bruce Parkin 
*
************************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/ToggleB.h>
#include <Xm/ArrowB.h>
#include <Xm/Separator.h>
#include <Xm/DrawnB.h>
#include <Xm/Scale.h>
#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/TextF.h>
#include <Xm/Text.h>
#include <Xm/DrawingA.h>
#include <Xm/CascadeB.h>
#include <Xm/MenuShell.h>
#include <Xm/ScrolledW.h>
#include <Xm/List.h>
#include <Xm/ScrollBar.h>
#include <X11/Shell.h>

#include "lxb.h"
#include "data.h"

/* static vars */
static int counter = 1;     /* appshell is "0" */

/**************************************************
 *
 *	Function: change_widget_name 
 *
 **************************************************/
int
change_widget_name(Widget w, char *newname)
{
	WSTRUCT *ptr;
	Boolean found = False;

	/* get the node in the linked list */
	ptr = tree_ptr;
	while (ptr != NULL) {
		if (w == ptr->instance){
			found = True;
			break;
		};
		ptr = ptr->next;
	};

	if (!found){
		fprintf(stderr, "Widget (%s) not found in linked list\n", XtName(w));
		return (0);
	};

	strcpy(ptr->appname, newname);
	return (1);
}	
/*******************************************************
*
*  Function: get_counter - this retrieves the number
*		suffixed onto the widget names to make them unique
*
********************************************************/
int
get_counter()
{
  counter++;
  return (counter-1);
}                                                          
/**************************************************
 *
 *	Function:	adjust_parent
 *
 *	Used mainly too allow an "active" widget of
 *	type Cascade Button, and although not the parent,
 *	allow the other widgets in the menu to be "selected"
 *
 *	Input is the "active widget"
 *
 **************************************************/
Widget
adjust_parent(Widget act_w)
{
	Widget pulldown;
	Arg args[3];
	
	if (XtClass(act_w) == xmCascadeButtonWidgetClass){

		/* get the pulldown associated with the Cascade button,
		 * which is the real parent of the other widgets in the
		 * menu
		 */

		XtSetArg(args[0], XmNsubMenuId, &pulldown);
		XtGetValues(act_w, args, 1);

		return (pulldown);

	};

	return (act_w);

}
/**************************************************
 *
 *	Function: get_parent_widget
 *
 **************************************************/
Widget
get_parent_widget(int key)
{
	Widget parent_widget;
	WSTRUCT *ptr;
	Boolean found = False;

	parent_widget = NULL;
	ptr = top_ptr;
	while (ptr != NULL) {

		if (key == ptr->key){
			found = True;
			parent_widget = ptr->instance;
			break;
		};

		ptr = ptr->last;
	};

	if (!found)
		fprintf(stderr, "get_parent_widget: cannot find parent widget for key: %d\n", key);

	return (parent_widget);
}	
/**************************************************
 *
 *	Function: get_parent_key
 *
 **************************************************/
int
get_parent_key(Widget w)
{
	WSTRUCT *ptr;
	int key;
	Boolean found = False;

	key = -1;
	ptr = tree_ptr;
	while (ptr != NULL) {
	
		if (w == ptr->instance){
			found = True;
			key = ptr->key;
			break;
		};

		ptr = ptr->next;
	};

	if (!found)
		fprintf(stderr, "get_parent_key: cannot find parent key for widget (%s)\n", XtName(w));

	return (key);
}	
/**************************************************
 *
 * Function: get_wstruct
 *
 *	Create and do some initialization of a node in
 *	the linked list.
 *
 **************************************************/
WSTRUCT * 
get_wstruct()
{
  WSTRUCT *ptr;

  /* make a new node */
  ptr = XtNew(WSTRUCT);
  memset(ptr, 0, sizeof(WSTRUCT));

	/* except for the first node */
	if (tree_ptr != NULL)
		tree_ptr->last = ptr;
	else

		/* top of the linked list */
		top_ptr = ptr;

  ptr->next = tree_ptr;

	/* bottom of the linked list */
  tree_ptr = ptr;

	tree_ptr->last = NULL;

	/* defaults to True */
	ptr->managed = True;
	ptr->perm = False;
	ptr->fixed = False;
	ptr->sel= True;
	ptr->global = True;

  return (ptr);
}                                                       
/**************************************************
 *
 *	Function: widget_instance
 *
 *	returns the widget instance given the appname for
 *	the widget (not the Xt name).
 *
 **************************************************/
Widget
widget_instance(char *name)
{
	WSTRUCT *ptr;

	ptr = tree_ptr;
	while (ptr != NULL) {
	
		if ( (strcmp(name, ptr->appname) == 0) ){
			break;
		};

		ptr = ptr->next;
	};

	return (ptr->instance);
}	
/**************************************************
 *
 *	widget_name:	returns the name of the widget 
 *					instance not from the Intrinsics
 *					but from the linked list.
 *
 *	TBD: should return a XtNewString (char *)
 *
 **************************************************/
char *
widget_name(Widget w)
{
	WSTRUCT *ptr;
	char *name;

	name = NULL;

	/* get the name */
	ptr = top_ptr;

	while (ptr != NULL) {

		if (w == ptr->instance){
			name = ptr->appname;
			break;
		};

		ptr = ptr->last;
	};

	if (name == NULL){ 
			fprintf(stderr, "Cannot get widget name from widget value\n"); 
	};

	return (name);
}	
/**************************************************
 *
 *	Function: widget_ptr
 *
 *	returns the ptr to the widget in the list
 *
 **************************************************/
WSTRUCT *
widget_ptr(Widget w)
{
	WSTRUCT *ptr;
	Boolean found = False;

	ptr = tree_ptr;
	while (ptr != NULL) {
	
		if (w == ptr->instance){
			found = True;
			break;
		};

		ptr = ptr->next;
	};

	if (!found)
		fprintf(stderr, "Widget (%s) not found in linked list\n", XtName(w));

	return (ptr);
}	
/**************************************************
 *
 *	Function: get_widget_classname
 *
 *	returns the string name of the widget class
 *
 **************************************************/
char *
get_widget_classname(Widget w)
{
	char *ptr;
	WidgetClass wclass;

	wclass = XtClass(w);

	ptr = NULL;

	if (wclass == xmFrameWidgetClass){

		ptr = XtNewString("xmFrameWidgetClass");

	} else if (wclass == xmScrollBarWidgetClass){

		ptr = XtNewString("xmScrollBarWidgetClass");

	} else if (wclass == xmListWidgetClass){

		ptr = XtNewString("xmListWidgetClass");

	} else if (wclass == xmScrolledWindowWidgetClass){

		ptr = XtNewString("xmScrolledWindowWidgetClass");

	} else if (wclass == xmCascadeButtonWidgetClass){

		ptr = XtNewString("xmCascadeButtonWidgetClass");

	} else if (wclass == xmDrawingAreaWidgetClass){

		ptr = XtNewString("xmDrawingAreaWidgetClass");

	} else if (wclass == xmFormWidgetClass){

		ptr = XtNewString("xmFormWidgetClass");

	} else if (wclass == xmBulletinBoardWidgetClass){

		ptr = XtNewString("xmBulletinBoardWidgetClass");

	} else if (wclass == xmRowColumnWidgetClass){

		ptr = XtNewString("xmRowColumnWidgetClass");

	} else if (wclass == xmLabelWidgetClass){

		ptr = XtNewString("xmLabelWidgetClass");

	} else if (wclass == xmTextWidgetClass){

		ptr = XtNewString("xmTextWidgetClass");

	} else if (wclass == xmTextFieldWidgetClass){

		ptr = XtNewString("xmTextFieldWidgetClass");

	} else if (wclass == xmScaleWidgetClass){

		ptr = XtNewString("xmScaleWidgetClass");

	} else if (wclass == xmArrowButtonWidgetClass){

		ptr = XtNewString("xmArrowButtonWidgetClass");

	} else if (wclass == xmToggleButtonWidgetClass){

		ptr = XtNewString("xmToggleButtonWidgetClass");

	} else if (wclass == xmPushButtonWidgetClass){

		ptr = XtNewString("xmPushButtonWidgetClass");

	} else if (wclass == xmSeparatorWidgetClass){

		ptr = XtNewString("xmSeparatorWidgetClass");

	} else if (wclass == applicationShellWidgetClass){

		ptr = XtNewString("applicationShellWidgetClass");

	} else if (wclass == topLevelShellWidgetClass){

		ptr = XtNewString("topLevelShellWidgetClass");

	} else if (wclass == xmMenuShellWidgetClass){

		ptr = XtNewString("xmMenuShellWidgetClass");

	/* kluge for composite widgets with automagic children */

	} else if (XtClass(XtParent(w)) == xmScrolledWindowWidgetClass){

		ptr = XtNewString("ScrolledWindowChildClass");

	} else if (XtClass(XtParent(w)) == xmScaleWidgetClass){

		ptr = XtNewString("ScaleChildClass");

	}else {

		fprintf(stderr, "get_widget_classname: Unknown widget class for widget: %s\n", XtName(w));
	};

	return (ptr);
}	
/**************************************************
 *
 * Function: choose_default_name
 *
 **************************************************/
char *
choose_default_name(WidgetClass wclass)
{
  char *name;

  if (wclass == xmFrameWidgetClass){
    name = "frame_";
  } else if (wclass == xmScrollBarWidgetClass){
    name = "scrollBar_";
  } else if (wclass == xmListWidgetClass){
    name = "list_";
  } else if (wclass == xmScrolledWindowWidgetClass){
    name = "scrolledWindow_";
  } else if (wclass == xmDrawingAreaWidgetClass){
    name = "drawingArea_";
  } else if (wclass == xmFormWidgetClass){
    name = "form_";
  } else if (wclass == xmBulletinBoardWidgetClass){
    name = "bulletinBoard_";
  } else if (wclass == xmRowColumnWidgetClass){
    name = "rowColumn_";
  } else if (wclass == xmLabelWidgetClass){
    name = "label_";
  } else if (wclass == xmTextWidgetClass){
    name = "text_";
  } else if (wclass == xmTextFieldWidgetClass){
    name = "textF_";
  } else if (wclass == xmScaleWidgetClass){
    name = "scale_";
  } else if (wclass == xmArrowButtonWidgetClass){
    name = "arrowButton_";
  } else if (wclass == xmToggleButtonWidgetClass){
    name = "toggleButton_";
  } else if (wclass == xmPushButtonWidgetClass){
    name = "pushButton_";
  } else if (wclass == xmCascadeButtonWidgetClass){
    name = "cascadeButton_";
  } else if (wclass == xmSeparatorWidgetClass){
    name = "separator_";
  } else if (wclass == applicationShellWidgetClass){
    name = "applicationShell_";
  } else if (wclass == topLevelShellWidgetClass){
    name = "topLevelShell_";
  } else {
		perror("choose_default_name: Unknown widget class");
		return (NULL);
  };

  return (name);
}                                                                               
/**************************************************
 *
 *	Function: get_widgetclass
 *
 *	returns the WidgetClass pointer from the string name
 *
 **************************************************/
WidgetClass
get_widgetclass(char *class)
{
	WidgetClass wclass = NULL;

	if ( (strcmp(class, "xmFrameWidgetClass") ==0) ){

		wclass = xmFrameWidgetClass;

	} else if ( (strcmp(class, "xmListWidgetClass") == 0)){

		wclass = xmListWidgetClass;

	} else if ( (strcmp(class, "xmScrolledWindowWidgetClass") == 0)){

		wclass = xmScrolledWindowWidgetClass;

	} else if ( (strcmp(class, "xmScrollBarWidgetClass") == 0)){

		wclass = xmScrollBarWidgetClass;

	} else if ( (strcmp(class, "xmMenuShellWidgetClass") ==0)){

		wclass = xmCascadeButtonWidgetClass;

	} else if ( (strcmp(class, "xmDrawingAreaWidgetClass") ==0)){

		wclass = xmDrawingAreaWidgetClass;

	} else if ( (strcmp(class, "xmFormWidgetClass") ==0)){

		wclass = xmFormWidgetClass;

	} else if ( (strcmp(class, "xmBulletinBoardWidgetClass") ==0)){

		wclass = xmBulletinBoardWidgetClass;

	} else if ( (strcmp(class, "xmRowColumnWidgetClass") ==0)){

		wclass = xmRowColumnWidgetClass;

	} else if ( (strcmp(class, "xmLabelWidgetClass") ==0)){

		wclass = xmLabelWidgetClass;

	} else if ( (strcmp(class, "xmTextWidgetClass") ==0)){

		wclass = xmTextWidgetClass;

	} else if ( (strcmp(class, "xmTextFieldWidgetClass") ==0)){

		wclass = xmTextFieldWidgetClass;

	} else if ( (strcmp(class, "xmScaleWidgetClass") ==0)){

		wclass = xmScaleWidgetClass;

	} else if ( (strcmp(class, "xmArrowButtonWidgetClass") ==0)){

		wclass = xmArrowButtonWidgetClass;

	} else if ( (strcmp(class, "xmToggleButtonWidgetClass") ==0)){

		wclass = xmToggleButtonWidgetClass;

	} else if ( (strcmp(class, "xmCascadeButtonWidgetClass") ==0)){

		wclass = xmCascadeButtonWidgetClass;

	} else if ( (strcmp(class, "xmPushButtonWidgetClass") ==0)){

		wclass = xmPushButtonWidgetClass;

	} else if ( (strcmp(class, "xmSeparatorWidgetClass") ==0)){

		wclass = xmSeparatorWidgetClass;

	} else if ( (strcmp(class, "applicationShellWidgetClass") ==0)){

		wclass = applicationShellWidgetClass;

	} else if ( (strcmp(class, "topLevelShellWidgetClass") ==0)){

		wclass = topLevelShellWidgetClass;

	} else if ( (strcmp(class, "ScrolledWindowChildClass") ==0)){

		/* ClipWindow, etc */

	} else if ( (strcmp(class, "ScaleChildClass") ==0)){

		/* XmScale children */

	}else {

		fprintf(stderr, "get_widgetclass: Unknown widget class (%s)\n", class);

	};

	return (wclass);
}	
