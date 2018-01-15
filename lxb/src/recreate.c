/**************************************************
*
* File: recreate.c
*
*    Copyright (C) 1997  Bruce Parkin 
*
**************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <X11/Xmu/Editres.h>
#include "lxb.h"
#include "data.h"
#include "color.h"
#include "mhandlers.h"
#include "cvt_resvalue.h"
#include "cfunctions.h"
#include "save.h"
#include "recreate.h"

/* local prototypes */
static int
make_widget(WSTRUCT *wptr);
static int
make_new_appshell(WSTRUCT *wptr, Arg args[], int i);

static void
save_tmpfile_timer(XtPointer client_data, XtIntervalId *id);
 
/**************************************************
 *
 * Function: save_tmpfile
 *
 **************************************************/
static void
save_tmpfile_timer(XtPointer client_data, XtIntervalId *id)
{
  save_tmp_gui();
  XtAppAddTimeOut(appcontext,120000, save_tmpfile_timer, NULL);
}                                                        
/**************************************************
 *
 * Function: recreate_gui
 *
 *
 *	NOTES: 1) shell widget - resources are recovered from
 *						the recorded resource list and XtSetArged
 *						for the process of rebuilding a "saved" file.
 *
 *						For producing code, the shell resources are
 *						put into the resource file.
 *
 *
 **************************************************/
int
recreate_gui()
{
	WSTRUCT *wptr;
	int 		i;
	Arg 		arg[MAX_ARGS];
	RES 		*rptr;
	int			status;
	Arg			*arglist;

	if (verbose >6)
		printf("recreate_gui\n");
	
	/* get the resources for the shell widget */
	wptr = top_ptr;
	arglist = arg;
	i=0;

	if (wptr->resptr != NULL){

		/* get the recorded resources */
		
		rptr = wptr->resptr;
		while (rptr != NULL){

			status = convert_value(arglist, rptr->name, rptr->value);
			if (status == NOTOK){
				fprintf(stderr, "Problems in recreate_gui\n");
				return(NOTOK);
			};
			i++; arglist++;
			
			rptr = rptr->next;
		};
	};

	/* make the shell widget and set it's resources */
	status = make_new_appshell(wptr, arg, i);

	/*-------------------------------------------------------------------------------*/

	/* go down the list and make all widgets */
	wptr = wptr->last;

	while (wptr != NULL){

		status = make_widget(wptr);

		if (status != OK){
			fprintf(stderr, "Error: (recreate_gui) - could not create child widget\n");
			return (NOTOK);
		};
		wptr = wptr->last;
	};

	/* install the event handlers */
	wptr = tree_ptr;
	while (wptr != NULL){

		if (wptr->sel)
			install_select_handlers(wptr->instance);
		wptr = wptr->next;
	};


	return (OK);
}
/**************************************************
 *
 * Function: make_widget
 *
 **************************************************/
static int
make_widget(WSTRUCT *wptr)
{
	Arg 				arg[MAX_ARGS];
	int 				i;
	Widget 			widget;
	WidgetClass wclass;
	RES 				*rptr;
	Widget 			parent_widget;
	int					status;
	ArgList			arglist;
	char 				*parent_name;

	if (verbose >6)
		printf("    make_widget: %s\n", wptr->appname);

	/* get Intrinsic's class */
	wclass = get_widgetclass(wptr->class);

	/* set the recorded resources */
	if (verbose >8)
		printf("    Setting resources:\n");

	i=0;
	arglist = arg;
	if (wptr->resptr != NULL){

		rptr = wptr->resptr;
		while (rptr != NULL){

			status = convert_value(arglist, rptr->name, rptr->value);
			if (!status){
				fprintf(stderr, "Problems in make_widget with resource: (%s) value: (%s)\n", rptr->name, rptr->value);
				i--;
			}; 

			i++; arglist++;

			rptr = rptr->next;
		};
	};

	/* add the universal resources so that this works for lxb */
	XtSetArg(arg[i], XmNtraversalOn, False);i++;
	XtSetArg(arg[i], XmNnavigationType, XmNONE);i++;  

	/* get parent widget */
	parent_widget = get_parent_widget(wptr->parent);
	parent_name = widget_name(parent_widget);  

	if (wptr->create_function[0] == '\0'){

		/* check to see if the widget is managed */
		if (wptr->managed == True){

			widget = XtCreateWidget(wptr->appname, wclass, parent_widget, arg, i);
			XtManageChild(widget);

		} else {

				/* unmanaged widget */
				widget = XtCreateWidget(wptr->appname, wclass, parent_widget, arg, i);
		};

	} else {

		widget = create_function(wptr->create_function, parent_widget, wptr->appname, arg, i);

		if (widget == NULL){

			fprintf(stderr, 
							"ERROR: (make_widget) Problem calling create function for  widget: (%s)  parent: (%s)\n", 
							wptr->appname, XtName(parent_widget));
			return (NOTOK);
		};


		if (wptr->managed == True)
			XtManageChild(widget);
	};                                                                           


	/* fill in the widget struct */
	wptr->instance = widget;

	return (OK);

}
/**************************************************
 *
 * Function: make_new_appshell
 *
 **************************************************/
static int
make_new_appshell(WSTRUCT *wptr, Arg args[], int i)
{
	if (verbose >6)
		printf("make_new_appshell\n");

	/* make the appShell widget */
	XtSetArg(args[i], XmNmwmFunctions, 
										MWM_FUNC_RESIZE|MWM_FUNC_MOVE|MWM_FUNC_MINIMIZE|MWM_FUNC_MAXIMIZE);i++;

	XtSetArg(args[i], XmNdeleteResponse, XmDO_NOTHING);i++; 

	appShell = XtCreatePopupShell("topLevelShell", topLevelShellWidgetClass, shell, args, i);
	XtManageChild(appShell);

  /* to debug with editres */
  XtAddEventHandler(appShell, (EventMask)0, True, _XEditResCheckMessages, NULL);

  install_select_handlers(appShell);   

	/* fill in struct */
	top_ptr->instance = appShell;
	top_ptr->parent = -1;
	top_ptr->key = 0;

  /* turn on autosave file */
  XtAppAddTimeOut(appcontext,120000, save_tmpfile_timer, NULL); 

	return (1);
}
