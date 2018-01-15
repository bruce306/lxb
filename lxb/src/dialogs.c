/**************************************************
*
* File: dialogs.c
*
*    Copyright (C) 1995  Bruce Parkin 
*
**************************************************/

/* include files */
#include <Xm/Xm.h>
#include <Xm/MessageB.h>
#include <Xm/BulletinB.h>
#include <Xm/SelectioB.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <stdio.h>
#include "lxb.h"
#include "save.h"
#include "open.h"
#include "play.h"
#include "recreate.h"
#include "delete.h"
#include "ResourceEd.h"
#include "about.h"
#include "populate.h"
#include "dialogs.h"
#include "Pallet.h"

static void
save_callback(Widget w, XtPointer client_data, XtPointer call_data);

static void
play_callback(Widget w, XtPointer client_data, XtPointer call_data);

static void
new_callback(Widget w, XtPointer client_data, XtPointer call_data);
static void
open_callback(Widget w, XtPointer client_data, XtPointer call_data);

/* local prototypes */
static Widget new_dialog = NULL;
static Widget play_dialog = NULL;
static Widget open_dialog = NULL;
static Widget dialog = NULL;

/*************************************************************
* 
* Function: play_callback 
*
*		Called when the "Build Mode" button is pressed on the
*		"Play Mode" dialog
*
*************************************************************/
static void
play_callback(Widget w, XtPointer client_data, XtPointer call_data)
{    

	/* get rid of the play GUI */
	destroy_playgui();

	/* show the main controls and widget pallet */
	XtMapWidget(shell);

	/* show the GUI being built */
	XtMapWidget(appShell);

	/* put back the resource editor if it was hidden */
	redisplay_resed_editor();

	/* put back the widget pallet */
	show_pallet();

}
/*************************************************************
* 
* Function: open_callback 
*
*		Gets the save filename from the OPEN dialog.
*		Called when a CR is done.
* 
*************************************************************/
static void
open_callback(Widget w, XtPointer client_data, XtPointer call_data)
{    
	XmString xms;
	XmSelectionBoxCallbackStruct *ptr;
	char *name;
	int status;
	char buf[100];
	Arg args[3];

	ptr = (XmSelectionBoxCallbackStruct *)call_data;
	xms = ptr->value;
	XmStringGetLtoR(xms, XmSTRING_DEFAULT_CHARSET, &name);

	if (name[0] != '\0') {

		/* remove old GUI */
		free_gui_list();

		/* set the savefile name */
		XtFree(savefile_name);
		savefile_name = XtNewString(name);
		XtFree(name);

		/* title in main window bar */
		strcpy(buf, "LXB - Application Save File: ");
		strcat(buf, savefile_name);

		XtSetArg(args[0], XmNtitle, buf);
		XtSetValues(shell, args, 1);

		status = open_gui();
		if (status == OK){

			/* build all the widgets and change resources */
			status = recreate_gui();   
		};

		populate_wtree();

		clear_resource_editor();
	};

}
/*************************************************************
* 
* Function: new_callback 
*
*		Gets the NEW application name from the dialog.
*		Called when a CR is done.
* 
*************************************************************/
static void
new_callback(Widget w, XtPointer client_data, XtPointer call_data)
{    
	XmString xms;
	XmSelectionBoxCallbackStruct *ptr;
	char *name;
	char buf[100];
	Arg args[3];

	ptr = (XmSelectionBoxCallbackStruct *)call_data;
	xms = ptr->value;
	XmStringGetLtoR(xms, XmSTRING_DEFAULT_CHARSET, &name);

	if (name[0] != '\0') {

		/* remove old GUI */
		free_gui_list();

		/* set new appname */
		XtFree(application_name);
		application_name = name;

		/* set the default savefile name */
		XtFree(savefile_name);
		strcpy(buf, name);
		strcat(buf, ".lxb");
		savefile_name = XtNewString(buf);

		/* title in main window bar */
		strcpy(buf, "LXB - Application Save File: ");
		strcat(buf, savefile_name);

		XtSetArg(args[0], XmNtitle, buf);
		XtSetValues(shell, args, 1);

		populate_wtree();
	};

	XtFree(name);
}
/***************************************************************************
 *
 *	Function: display_playmode_dialog
 *
 *		Popup a dialog when in play mode that allows the user to go back to
 *		build mode.
 *
 **************************************************************************/
void 
display_playmode_dialog()
{
	Arg args[3];

	if (!play_dialog) {
		Widget child;
		XmString msg = XmStringCreateLtoR("Play Mode Engaged", XmSTRING_DEFAULT_CHARSET);
		XmString okmsg = XmStringCreateLtoR("Build Mode", XmSTRING_DEFAULT_CHARSET);

		XtSetArg(args[0], XmNmessageString, msg);
		XtSetArg(args[1], XmNokLabelString, okmsg);
		play_dialog = XmCreateInformationDialog(shell, "PlayMode", args, 2);
		XmStringFree(msg);
		XmStringFree(okmsg);

		XtSetArg(args[0], XmNtitle, "Play Mode");
		XtSetValues(XtParent(play_dialog), args, 1);
		
    XtAddCallback(play_dialog, XmNokCallback, play_callback, NULL);

		child = XmMessageBoxGetChild(play_dialog, XmDIALOG_CANCEL_BUTTON); 
		XtUnmanageChild(child);
		child = XmMessageBoxGetChild(play_dialog, XmDIALOG_HELP_BUTTON); 
		XtUnmanageChild(child);

	};
	XtManageChild(play_dialog);
}
/***************************************************************************
 *
 *	Function: display_new_dialog
 *
 *		Popup a dialog which requests the name to be used for the NEW application.
 *		This is called when the user presses a New button on the Files menu.
 *
 **************************************************************************/
void 
display_new_dialog()
{
	Arg args[3];

	if (!new_dialog) {
		XmString msg = XmStringCreateLtoR("New Application Name:", XmSTRING_DEFAULT_CHARSET);

		XtSetArg(args[0], XmNselectionLabelString, msg);

		new_dialog = XmCreatePromptDialog(shell, "Question", args, 1);
		XtSetArg(args[0], XmNtitle, "Question");
		XtSetValues(XtParent(new_dialog), args, 1);
		
		XmStringFree(msg);
    XtAddCallback(new_dialog, XmNokCallback, new_callback, NULL);

	};
	XtManageChild(new_dialog);
}
/***************************************************************************
 *
 *	Function: display_open_dialog
 *
 *		Popup a dialog which requests the name of an existing application.
 *		This is called when the user presses a New button on the Files menu.
 *
 **************************************************************************/
void 
display_open_dialog()
{
	Arg args[3];

	if (!open_dialog) {
		XmString msg = XmStringCreateLtoR("Open lxb Save file:", XmSTRING_DEFAULT_CHARSET);

		XtSetArg(args[0], XmNselectionLabelString, msg);

		open_dialog = XmCreatePromptDialog(shell, "Question", args, 1);

		XtSetArg(args[0], XmNtitle, "Question");
		XtSetValues(XtParent(open_dialog), args, 1);
		
		XmStringFree(msg);
    XtAddCallback(open_dialog, XmNokCallback, open_callback, NULL);

	};
	XtManageChild(open_dialog);
}
/*************************************************************
* 
*	Fucntion: overwrite_callback
*
*		Called for overwriting an existin Save file.
*
*************************************************************/
static void
save_callback(Widget w, XtPointer client_data, XtPointer call_data)
{    
	save_gui(True);
}
/***************************************************************************
 *
 * Function: display_save_dialog
 *
 *	Shows Dialog requesting whether or not to overwrite existing Save file
 *
 **************************************************************************/
void 
display_save_dialog(Widget w)
{
	Arg args[3];

	if (!dialog) {
		XmString msg = XmStringCreateLtoR("Overwrite existing save file?", XmSTRING_DEFAULT_CHARSET);

		XtSetArg(args[0], XmNmessageString, msg);
		dialog = XmCreateQuestionDialog(w, "Question", args, 1);

		XtSetArg(args[0], XmNtitle, "Question");
		XtSetValues(XtParent(dialog), args, 1);
		
		XmStringFree(msg);
    XtAddCallback(dialog, XmNokCallback, save_callback, NULL);

	};
	XtManageChild(dialog);
}
/**************************************************
 *
 * Function: build_help_gui
 *
 *	Dialog to display "help" for the user. 
 *
 *	Currently shows "TBD"...
 *
 **************************************************/
void 
build_help_gui(Widget parent)
{
	static Widget dialog;
	Arg args[3];

	if (!dialog) {

			XmString msg = XmStringCreateLtoR("TBD", XmSTRING_DEFAULT_CHARSET);
			XtSetArg(args[0], XmNmessageString, msg);
			dialog = XmCreateInformationDialog(shell, "help_dialog", args, 1);

			XtSetArg(args[0], XmNtitle, "Question");
			XtSetValues(XtParent(dialog), args, 1);
	
			XmStringFree(msg);
	};
	XtManageChild(dialog);
}
/*************************************************************
*
*	Function: saveas_callback
 *
 ************************************************************/
static void
saveas_callback(Widget w, XtPointer client_data, XtPointer call_data)
{    
	XmString xm = ((XmSelectionBoxCallbackStruct *)call_data)->value;
	char *filename;

	XmStringGetLtoR(xm, XmSTRING_DEFAULT_CHARSET, &filename);

	XtFree(savefile_name);
	savefile_name = filename;

	save_gui(True);
}
/**************************************************
 *
 * Function: display_saveas_dialog
 *
 **************************************************/
void 
display_saveas_dialog(Widget w)
{
	static Widget dialog;

	if (!dialog) {
		Arg args[1];
		char buf[124];
		Widget txt;
		
		XmString msg = XmStringCreateLtoR("Save in File:", XmSTRING_DEFAULT_CHARSET);

		XtSetArg(args[0], XmNselectionLabelString, msg);

		dialog = XmCreatePromptDialog(w, "saveas_dialog", args, 1);
    XtAddCallback(dialog, XmNokCallback, saveas_callback, NULL);

		txt = XmSelectionBoxGetChild(dialog, XmDIALOG_TEXT);
		XmTextSetString(txt, savefile_name);
		XmTextFieldSetInsertionPosition(txt, strlen(savefile_name));     

	};
	XtManageChild(dialog);
}
/**************************************************
 *
 * Function: display_saveas_dialog
 *
 **************************************************/
void 
OLDdisplay_saveas_dialog(Widget w)
{
	static Widget dialog;

	if (!dialog) {
		Arg args[1];
		XmString msg = XmStringCreateLtoR("Save in File:", XmSTRING_DEFAULT_CHARSET);

		XtSetArg(args[0], XmNselectionLabelString, msg);

		dialog = XmCreatePromptDialog(w, "saveas_dialog", args, 1);
    XtAddCallback(dialog, XmNokCallback, saveas_callback, NULL);

	};
	XtManageChild(dialog);
}
/*************************************************************
*
*	Function: appname_callback
 *
 ************************************************************/
static void
appname_callback(Widget w, XtPointer client_data, XtPointer call_data)
{    
	XmString xm = ((XmSelectionBoxCallbackStruct *)call_data)->value;
	char *filename;

	XmStringGetLtoR(xm, XmSTRING_DEFAULT_CHARSET, &filename);
	
	XtFree(application_name);
	application_name = filename;
}
/**************************************************
 *
 * Function: display_appname_dialog
 *
 **************************************************/
void 
display_appname_dialog(Widget w)
{
	static Widget dialog;

	if (!dialog) {
		Arg args[1];
		XmString msg = XmStringCreateLtoR("New Application Name:", XmSTRING_DEFAULT_CHARSET);

		XtSetArg(args[0], XmNselectionLabelString, msg);

		dialog = XmCreatePromptDialog(w, "appname_dialog", args, 1);
    XtAddCallback(dialog, XmNokCallback, appname_callback, NULL);

	};
	XtManageChild(dialog);
}
/**************************************************
 *
 * Function: build_about_lxb
 *
 **************************************************/
void 
display_about_lxb(Widget parent)
{
	popup_about_dialog();
}
