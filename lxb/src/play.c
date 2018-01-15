/**************************************************
 * File: play.c
 *
 *	Create a "real" GUI for "play mode".
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/
/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h> 
#include <X11/Xmu/Editres.h>
#include "lxb.h"
#include "data.h"
#include "cvt_resvalue.h"
#include "cfunctions.h"
#include "play.h"
#include "TopShell.h"

/* local prototypes */
static int
make_childwidget(WSTRUCT *wptr);
static Widget
get_play_parent(int key);
static Widget
get_play_sibling(Widget w);

/* local variables */
static Widget playshell = NULL;

/**************************************************
 * Function: show_playgui
 **************************************************/
void
show_playgui()
{
	XtSetMappedWhenManaged(playshell, True);
}
/**************************************************
 * Function: destroy_playgui
 **************************************************/
void
destroy_playgui()
{
	if (playshell != NULL){
		XtDestroyWidget(playshell);
		playshell = NULL;
	};
}
/**************************************************
 *
 * Function: create_playgui
 *
 **************************************************/
int
create_playgui()
{
	WSTRUCT *wptr;
	int 		i;
	Arg 		arg[MAX_ARGS];
	RES 		*rptr;
	int			status;
	Arg			*arglist;

	if (verbose >5)
		printf("create_playgui\n");

	/* first record the current geometry of the appShell */
	record_last_appshell_resources();

	/* Make the shell widget first */
	wptr = top_ptr;
	
	/* get the resources */
	arglist = arg;
	i=0;
	if (wptr->resptr != NULL){

		/* get the recorded resources */
		rptr = wptr->resptr;
		while (rptr != NULL){

			status = convert_value(arglist, rptr->name, rptr->value);
			if (status == NOTOK){
				fprintf(stderr, "Problems in create_playgui\n");
				return(NOTOK);
			};
			i++; arglist++;
			rptr = rptr->next;
		};
	};

	/* make the shell widget and set it's resources */
	XtSetArg(arg[i], XmNmwmFunctions, MWM_FUNC_RESIZE|MWM_FUNC_MOVE|MWM_FUNC_MINIMIZE|MWM_FUNC_MAXIMIZE);i++;
	XtSetArg(arg[i], XmNdeleteResponse, XmDO_NOTHING);i++; 
	XtSetArg(arg[i], XmNmappedWhenManaged, False);i++; 
	playshell = XtCreatePopupShell("playshell", topLevelShellWidgetClass, shell, arg, i);
	XtManageChild(playshell);

  /* to debug with editres */
  XtAddEventHandler(playshell, (EventMask)0, True, _XEditResCheckMessages, NULL);       

	/* for connecting the "play" widget heirarchy */
	wptr->other_instance = playshell;

	/* Now go down the list and make all the child widgets */
	wptr = wptr->last;
	while (wptr != NULL){
		status = make_childwidget(wptr);
		if (status != OK){
			fprintf(stderr, "Problems in create_playgui in making child widget\n");
			break;
		};
		wptr = wptr->last;
	};

	return (OK);
}
/**************************************************
 * Function: make_childwidget
 *
 *	Cannot use the parent in the linked list else we 
 *	get the playgui created in the built gui
 *
 **************************************************/
static int
make_childwidget(WSTRUCT *wptr)
{
	Arg 				arg[MAX_ARGS];
	int 				i;
	WidgetClass wclass;
	RES 				*rptr;
	int					status;
	ArgList			arglist;
	Widget			parent, child;

	if (verbose >5)
		printf("make_childwidget\n");

	/* get Intrinsic's class */
	wclass = get_widgetclass(wptr->class);

	/* set the recorded resources */
	if (verbose >5)
		printf("  Setting resources:\n");

	i=0;
	arglist = arg;
	if (wptr->resptr != NULL){

		rptr = wptr->resptr;
		while (rptr != NULL){

			if (verbose >5)
				printf("    Resource: %s  value: %s\n", rptr->name, rptr->value);

				status = convert_value(arglist, rptr->name, rptr->value);
				if (!status){
					fprintf(stderr, "Problems in make_childwidget\n");
					return (NOTOK);
				}; 

				/* kludge for XmForm children */
				/* convert_value works for load in of save file because it 
					searchs the linked list being built. It does not work here
					because the linked list searched id the "built" GUI list,
					and the wrong widget id would be returned for the input
					widget name. We need the ptr->other instance widget id,
					if being the "play" widget id. sigh. clear as mud.
				*/

				if (rptr->enumlist == -5){

					/* must get play sibling widget, not build widget */
					arglist->value = (XtArgVal)get_play_sibling((Widget)arglist->value);
				};

			i++; arglist++;
			rptr = rptr->next;
		};
	};

  /* get the LIST'S parent widget */
  parent = get_play_parent(wptr->parent);

	if (verbose > 5)
		printf("Create Widget:  %s\n", wptr->appname);

	child = NULL;
	if (wptr->create_function[0] == 0){

		/* check to see if the widget is managed */
		if (wptr->managed == True){

			child = XtCreateManagedWidget(wptr->appname, wclass, parent, arg, i);

		} else {

				/* unmanaged widget */
				child = XtCreateWidget(wptr->appname, wclass, parent, arg, i);
		};

	} else {

		child = create_function(wptr->create_function, parent, wptr->appname, arg, i);

		if (child == NULL){

			fprintf(stderr, "make_childwidget: NULL child (%s)\n", wptr->appname);
			return (NOTOK);
		};

		if (wptr->managed == True)
			XtManageChild(child);

	};                                                                           

	/* for "play" widget heirarchy */
	wptr->other_instance = child;

	return (OK);
}
/**************************************************
 *
 *  Function: get_play_sibling
 *
 *	Get the play widget instance, not the build instance, 
 *	which does not exist in this mode/tree
 *
 *	w: the build tree widget
 *
 **************************************************/
static Widget
get_play_sibling(Widget w)
{
  Widget sibling = NULL;
  WSTRUCT *ptr;
  Boolean found = False;

  ptr = top_ptr;
  while (ptr != NULL) {

		if (ptr->instance == w){
      found = True;
      sibling = ptr->other_instance;
      break;
    };

    ptr = ptr->last;
  };

  if (!found)
    fprintf(stderr, "get_play_sibling: cannot get play widget of build widget (%s)\n", XtName(w));

  return (sibling);
}                           
/**************************************************
 *
 *  Function: get_play_parent
 *
 *	Same as get_parent_widget except uses the other_instance
 *	field.
 *
 **************************************************/
static Widget
get_play_parent(int key)
{
  Widget parent = NULL;
  WSTRUCT *ptr;
  Boolean found = False;

  parent = NULL;
  ptr = top_ptr;
  while (ptr != NULL) {

    if (key == ptr->key){
      found = True;
      parent = ptr->other_instance;
      break;
    };

    ptr = ptr->last;
  };

  if (!found)
    fprintf(stderr, "get_play_parent: cannot find parent widget for key: %d\n", key);

  return (parent);
}                           
