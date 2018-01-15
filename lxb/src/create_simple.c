/**************************************************
*
* File: create_simple.c - the simple non-troublesome widget 
*		creation functions.
*
*    Copyright (C) 1995  Bruce Parkin 
*
**************************************************/

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
#include <Xm/ScrolledW.h>
#include <Xm/ScrollBar.h>
#include <Xm/List.h>

#include "lxb.h"
#include "data.h"
#include "mhandlers.h"
#include "end_program.h"
#include "select.h"
#include "children.h"
#include "recres.h"
#include "create_simple.h"

/* local prototypes */
static void
init_widget(Widget parent, WSTRUCT *ptr, WidgetClass wclass, Arg args[], int *n);

/**************************************************
 *
 * Function: instantiate_widget
 *
 **************************************************/
Widget
instantiate_widget(Widget parent, XtPointer data)
{
	Arg args[10];
	int n;
	Widget w;
	char *name;
	char all[100];
	char number[5];
	WidgetClass wclass;
	WSTRUCT *ptr;

	/* get Intrinsic's class */
	wclass = (WidgetClass)data;

	/* get the data structure - sets tree_ptr too */
	ptr = get_wstruct();
	ptr->key = get_counter();

	/* make a string name for the class */
	name = choose_default_name(wclass);

	/* make the name unique */
  sprintf(number, "%d", ptr->key);
	strcpy(all, name);
	strcat(all, number);

	/* set widget specific resources */
	n=0;
	init_widget(parent, ptr, wclass, args, &n);

	/* make the widget */
	w = XtCreateManagedWidget(all, wclass, parent, args, n);

	/* fill in the widget struct */
	strcpy(ptr->appname, all);
	ptr->instance = w;

	/* pointer to parent */
	ptr->parent = get_parent_key(parent);

	/* record the widget class */
	strcpy(ptr->class, get_widget_classname(w));

	install_select_handlers(w);
	return (w);
}
/***********************************************************
 *
 * Function: init_widget
 *
 *	For those resources that must be set at creation time.
 *
 **********************************************************/
static void
init_widget(Widget parent, WSTRUCT *ptr, WidgetClass wclass, Arg args[], int *n)
{

	/* set some universal resources - want GUI same as insensitive */
	XtSetArg(args[*n], XmNtraversalOn, False);(*n)++;
	XtSetArg(args[*n], XmNnavigationType, XmNONE);(*n)++;

	if (wclass == xmFrameWidgetClass){

		XtSetArg(args[*n], XmNwidth, 60);(*n)++;
		XtSetArg(args[*n], XmNheight, 60);(*n)++;

		record_resource(ptr, XmNwidth, "60", -999);
		record_resource(ptr, XmNheight, "60", -999);

	} else if (wclass == xmListWidgetClass){

		XtSetArg(args[*n], XmNwidth, 60);(*n)++;
		XtSetArg(args[*n], XmNheight, 60);(*n)++;

		record_resource(ptr, XmNwidth, "60", -999);
		record_resource(ptr, XmNheight, "60", -999);

	} else if (wclass == xmDrawingAreaWidgetClass){

		XtSetArg(args[*n], XmNwidth, 60);(*n)++;
		XtSetArg(args[*n], XmNheight, 60);(*n)++;
		XtSetArg(args[*n], XmNresizePolicy, XmRESIZE_NONE);(*n)++;

		record_resource(ptr, XmNwidth, "60", -999);
		record_resource(ptr, XmNheight, "60", -999);
		record_resource(ptr, XmNresizePolicy, "XmRESIZE_NONE", 7);

	} else if (wclass == xmFormWidgetClass){

		XtSetArg(args[*n], XmNwidth, 60);(*n)++;
		XtSetArg(args[*n], XmNheight, 60);(*n)++;
		XtSetArg(args[*n], XmNresizePolicy, XmRESIZE_NONE);(*n)++;
		XtSetArg(args[*n], XmNrubberPositioning, False);(*n)++;

		record_resource(ptr, XmNwidth, "60", -999);
		record_resource(ptr, XmNheight, "60", -999);
		record_resource(ptr, XmNresizePolicy, "XmRESIZE_NONE", 7);
		record_resource(ptr, XmNrubberPositioning, "False", 12);

	} else if (wclass == xmBulletinBoardWidgetClass){

		XtSetArg(args[*n], XmNwidth, 60);(*n)++;
		XtSetArg(args[*n], XmNheight, 60);(*n)++;
		XtSetArg(args[*n], XmNnoResize, True);(*n)++;

		record_resource(ptr, XmNwidth, "60", -999);
		record_resource(ptr, XmNheight, "60", -999);
		record_resource(ptr, XmNnoResize, "True", 12);

	} else if (wclass == xmRowColumnWidgetClass){

		XtSetArg(args[*n], XmNheight, 30);(*n)++;
		XtSetArg(args[*n], XmNwidth, 60);(*n)++;
		record_resource(ptr, XmNheight, "30", -999);
		record_resource(ptr, XmNwidth, "60", -999);

	} else if (wclass == xmArrowButtonWidgetClass){

		XtSetArg(args[*n], XmNheight, 60);(*n)++;
		XtSetArg(args[*n], XmNwidth, 60);(*n)++;
		record_resource(ptr, XmNheight, "60", -999);
		record_resource(ptr, XmNwidth, "60", -999);

	} else if (wclass == xmLabelWidgetClass){
	} else if (wclass == xmTextFieldWidgetClass){
	} else if (wclass == xmTextWidgetClass){
	} else if (wclass == xmPushButtonWidgetClass){
	} else if (wclass == xmCascadeButtonWidgetClass){
	} else if (wclass == xmSeparatorWidgetClass){
	} else if (wclass == xmToggleButtonWidgetClass){
	} else if (wclass == xmScrollBarWidgetClass){

	} else {

			fprintf(stderr, "Unknown Widget class asked to be created\n");
	};

	/* set constraints required on some children (ARG!) */
	if (XtClass(parent) == xmFormWidgetClass){

		/* due to XmNrubberPosition on form parent */
		XtSetArg(args[*n], XmNtopAttachment, XmATTACH_FORM);(*n)++;
		XtSetArg(args[*n], XmNleftAttachment, XmATTACH_FORM);(*n)++;
		record_resource(ptr, XmNtopAttachment, "XmATTACH_FORM", 6);
		record_resource(ptr, XmNleftAttachment, "XmATTACH_FORM", 6);
	};

}
