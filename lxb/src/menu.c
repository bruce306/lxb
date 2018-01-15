/**************************************************
*
* File: menu.c - menu creation functions for lxb's
*	menubar in the main GUI.
*
*    Copyright (C) 1997  Bruce Parkin 
*
 **************************************************/

/* include files */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <Xm/Xm.h>
#include <Xm/MessageB.h>
#include <Xm/ToggleB.h>
#include "lxb.h"
#include "delete.h"
#include "ResourceEd.h"
#include "play.h"
#include "Pallet.h"
#include "code.h"
#include "dialogs.h"
#include "save.h"
#include "open.h"
#include "recreate.h"
#include "diag.h"
#include "populate.h"
#include "children.h"
#include "mhandlers.h"

#include "menu.h"

/* local function prototypes */
static void 
help_callback(Widget w, XtPointer client_data, XtPointer call_data);
static void 
file_callback(Widget w, XtPointer client_data, XtPointer call_data);
static void 
edit_callback(Widget w, XtPointer client_data, XtPointer call_data);
static void 
options_callback(Widget w, XtPointer client_data, XtPointer call_data);

static void 
diag_callback(Widget w, XtPointer client_data, XtPointer call_data);

/* local static vars */
static Widget menubar;

/*********************************************************************************
 *
 * Function: file_callback - functions called when the buttons in the
 *	"Files" menu is pressed.
 *
 */
static void 
file_callback(Widget w, XtPointer client_data, XtPointer call_data)
{

	long item_no = (long)client_data;

	int status = OK;
	char buf[100];
	int n;
	Arg args[10];

	if (item_no == 0){

		/* start New application */

    /* remove old GUI */
    free_gui_list();

    /* set new appname */
    XtFree(application_name);
    XtFree(savefile_name);     

    /* simplify later name changes by always using malloc */
    application_name = XtNewString("lxbApp");
    savefile_name = XtNewString("lxbApp.lxb");

    /* title in main window bar */
    strcpy(buf, "LXB - Application Save File: ");
    strcat(buf, savefile_name);

    n=0;
    XtSetArg(args[n], XmNtitle, buf);n++;
    XtSetArg(args[n], XmNiconName, "lxb");n++;
    XtSetValues(shell, args, n);                           

    populate_wtree();

		clear_resource_editor();

	} else if (item_no == 1){

		/* "Open": open existing application */
		display_open_dialog();

	}else if (item_no == 2){

		/* save the GUI */
		status = save_gui(True);

	}else if (item_no == 3){

			/* save as something else than current */
			display_saveas_dialog(shell);

	}else if (item_no == 4){

		/*  "Quit"   */
		exit(0);
	};

}
/*************************************************************
 *
 * diag_callback
 *
 *	Diagnostics callback - for development purposes
 *
 */
static void 
diag_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	long item_no = (long)client_data;

	if (item_no == 0){

		/* dump the widget heirarchy to stdout */
		diag_widget_tree();

	} else if (item_no == 1){

		/* dump the resources for the selected_widget to stdout) */
		diag_resource_list(selected_widget);

	};

}
/*************************************************************
 *
 * options_callback
 *
 */
static void 
options_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	int status;
	long item_no = (long)client_data;

	if (item_no == 0){

		if (appShell != NULL){

				status = create_playgui();
				if (status == OK){

					/* hide the resource editor */
					hide_resed_editor();

					/* hide the widget pallet */
					hide_pallet();

					/* hide the application GUI being built */
					XtUnmapWidget(appShell);
	
					/* hide the main window */
					XtUnmapWidget(shell);

					/* put up a dialog*/
					display_playmode_dialog();

					/* build the play GUI */
					show_playgui();
				};
		};

	} else if (item_no == 1){


		/* Code the GUI */
		code();

	} else if (item_no == 2){

		printf("TBD\n");
	};
}
/*************************************************************
 *
 * edit_callback -
 *
 */
static void
edit_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
        long item_no = (long)client_data;
        XmToggleButtonCallbackStruct *xmt = (XmToggleButtonCallbackStruct *)call_data;

        /* Destroy the widget tree */
        if (item_no == 0){

                delete_widget(selected_widget, False);

                /* fill in the tree widget with nodes */
                populate_wtree();

        } else if (item_no == 1){

        };

}
/*************************************************************
 *
 * help_callback
 *
 */
static void
help_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
        long item_no = (long)client_data;

        if (item_no == 0)

                display_about_lxb(shell);

        else {

                build_help_gui(shell);
        };
}
/*************************************************************************************
 *
 * Function: windows_callback
 *
 *************************************************************************************/
static void
windows_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
        long item_no = (long)client_data;

        printf("TBD\n");
}
/**************************************************
 *
 * Function: build_menu
 *
 * parent is the "main window", an XmForm
 *
 **************************************************/
Widget
build_menu(Widget parent)
{
	Widget widget, pulldown;
	XmString file, edit, options, help, quit, new, open, save;
	XmString cut;
	XmString compile, xm1, diagnostics, xm;
	Arg args[3];

	/* Create the MenuBar */
	file = XmStringCreateSimple("File");
	edit= XmStringCreateSimple("Edit");
	options = XmStringCreateSimple("Options");
	diagnostics = XmStringCreateSimple("Diagnostics");
	xm = XmStringCreateSimple("Windows");
	help = XmStringCreateSimple("Help");

	menubar = XmVaCreateSimpleMenuBar(parent, "menubar",
								XmVaCASCADEBUTTON, file, 'F',
								XmVaCASCADEBUTTON, edit, 'E',
								XmVaCASCADEBUTTON, options, 'O',
								XmVaCASCADEBUTTON, diagnostics, 'D',
								XmVaCASCADEBUTTON, xm, 'W',
								XmVaCASCADEBUTTON, help, 'H',
								NULL);

	XmStringFree(file);
	XmStringFree(xm);
	XmStringFree(edit);
	XmStringFree(options);
	XmStringFree(diagnostics);

	/* Tell the menubar which button is the help menu  */
	if ( (widget = XtNameToWidget(menubar, "button_5") ))
			XtVaSetValues(menubar, XmNmenuHelpWidget, widget, NULL);

	/* First menu is the File menu -- callback is file_callback() */
	new = XmStringCreateSimple("New");
	open = XmStringCreateSimple("Open");
	save = XmStringCreateSimple("Save");
	xm = XmStringCreateSimple("Save As..");

	quit = XmStringCreateSimple("Quit");

	pulldown = XmVaCreateSimplePulldownMenu(menubar, "file_menu", 0, file_callback,
							XmVaPUSHBUTTON, new, 'N', NULL, NULL, 
							XmVaPUSHBUTTON, open, 'O', NULL, NULL, 
							XmVaPUSHBUTTON, save, 'S', NULL, NULL, 
							XmVaPUSHBUTTON, xm, 'A', NULL, NULL, 
							XmVaPUSHBUTTON, quit, 'Q', NULL, NULL, 
							NULL);

	XmStringFree(new);
	XmStringFree(open);
	XmStringFree(save);
	XmStringFree(xm);
	XmStringFree(quit);

	cut = XmStringCreateSimple("Delete Widget");

	/* Second menu is the Edit menu -- callback is edit_callback() */
	pulldown = XmVaCreateSimplePulldownMenu(menubar, "edit_menu", 1, edit_callback,
						XmVaPUSHBUTTON, cut, 'D', NULL, NULL, 
						NULL);

	XmStringFree(cut);

	compile = XmStringCreateSimple("Code");
	new = XmStringCreateSimple("Play Mode");
	xm = XmStringCreateSimple("Application Name..");

	/* Third menu is the Options menu -- callback is options_callback() */
	XmVaCreateSimplePulldownMenu(menubar, "options_menu", 2, options_callback,
							XmVaPUSHBUTTON, new, 'P', NULL, NULL,
							XmVaPUSHBUTTON, compile, 'C', NULL, NULL,
							XmVaPUSHBUTTON, xm, 'A', NULL, NULL,
							NULL);

	XmStringFree(compile);
	XmStringFree(new);
	XmStringFree(xm);

	/* 4th menu is the Diagnostics menu */
	xm= XmStringCreateSimple("Dump Widget Tree");
	xm1= XmStringCreateSimple("Selected Widget Resources");

	pulldown = XmVaCreateSimplePulldownMenu(menubar, "diagonostics_menu", 3, diag_callback,
							XmVaPUSHBUTTON, xm, 'D', NULL, NULL, 
							XmVaPUSHBUTTON, xm1, 'S', NULL, NULL, 
							NULL);

	XmStringFree(xm);
	XmStringFree(xm1);

	/* 5th menu is the Windows menu */
	xm1= XmStringCreateSimple("Resource Editor");
	xm= XmStringCreateSimple("Widget Pallet");

	pulldown = XmVaCreateSimplePulldownMenu(menubar, "windows_menu", 4, windows_callback,
							XmVaPUSHBUTTON, xm1, 'R', NULL, NULL, 
							XmVaPUSHBUTTON, xm, 'W', NULL, NULL, 
							NULL);
	XmStringFree(xm1);
	XmStringFree(xm);

	xm = XmStringCreateSimple("About");

	/* Third menu is the Help menu -- callback is help_callback() */
	XmVaCreateSimplePulldownMenu(menubar, "help_menu", 5, help_callback,
							XmVaPUSHBUTTON, xm, 'A', NULL, NULL, 
							XmVaPUSHBUTTON, help, 'H', NULL, NULL, 
							NULL);

	XmStringFree(help); 
	XmStringFree(xm); 

	XtManageChild(menubar);
	return (menubar);
}
