/**************************************************
 *
 * File: TopShell.c
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
#include "recres.h"
#include "end_program.h"
#include "save.h"
#include "TopShell.h"

/* local functions */
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
	XtAddTimeOut(120000, save_tmpfile_timer, NULL);      
}
/**************************************************
 *
 * Function: record_last_appshell_resources
 *
 **************************************************/
void
record_last_appshell_resources()
{
	Arg args[10];
  Position  x,y;
  Dimension wi, he;
  char  geometry[50];
  char  tmp[10];

	/* app shell */
	XtSetArg(args[0], XmNwidth, &wi);
	XtSetArg(args[1], XmNheight, &he);
	XtSetArg(args[2], XmNx, &x);
	XtSetArg(args[3], XmNy, &y);
	XtGetValues(top_ptr->instance, args, 4);

	/* make the .geometry resource */
	sprintf(tmp, "%u", wi);
	strcpy(geometry, tmp);
	strcat(geometry, "x");
	sprintf(tmp, "%u", he);
	strcat(geometry, tmp);

	strcat(geometry, "+");
	sprintf(tmp, "%u", x);
	strcat(geometry, tmp);
	strcat(geometry, "+");
	sprintf(tmp, "%u", y);
	strcat(geometry, tmp);
																													 
	re_record_resource(top_ptr, "geometry", geometry, -999);
}
/**************************************************
 *
 * Function: make_appshell
 *
 *	Make the toplevel shell for the GUI being built
 *	(the application shell).
 *
 **************************************************/
Widget
make_appshell()
{
	Arg args[10];
	int n;
	WSTRUCT *ptr;

	ptr = get_wstruct();

	/* make the appShell widget */
	n=0;
	XtSetArg(args[n], XmNdeleteResponse, XmDO_NOTHING);n++;
	XtSetArg(args[n], XmNmwmFunctions, 
										MWM_FUNC_RESIZE|MWM_FUNC_MOVE|MWM_FUNC_MINIMIZE|MWM_FUNC_MAXIMIZE);n++;


	ptr->instance= XtCreatePopupShell("topLevelShell", topLevelShellWidgetClass, shell, args, n);

	/* have to do this here or Linux/fvwm does not allow the shell to resize of child can't @@??!! */
	XtManageChild(ptr->instance);

	/* to debug with editres */
	XtAddEventHandler(ptr->instance, (EventMask)0, True, _XEditResCheckMessages, NULL);

	install_select_handlers(ptr->instance);

	/* fill in the widget struct */
	ptr->parent = -1;
	ptr->key = 0;

	strcpy(ptr->appname, "topLevelShell");
	strcpy(ptr->class, "topLevelShellWidgetClass");

	record_last_appshell_resources();
	appShell = ptr->instance;

	/* turn on autosave file */
	XtAddTimeOut(120000, save_tmpfile_timer, NULL);      

	return (ptr->instance);
}
