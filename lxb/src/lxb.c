/***************************************************************************
*
* File: lxb.c - Linux X Builder
*
*    Copyright (C) 1997-2002  Bruce Parkin 
*
*	History:
*
*		1/2018 Version 6
*		5/?/02 Version 0.51	
*		3/1/97 Version 0.5	
*		6/1/96 Version 0.4
*		3/1/96 Version 0.3	
*
***************************************************************************/

#include <X11/StringDefs.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MwmUtil.h>
#include <X11/Xmu/Editres.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>    
#include <time.h>
#include <dirent.h>
#include <errno.h>

#include "lxb.h"
#include "fallbacks.h"
#include "version.h"
#include "top.h"
#include "Pallet.h"
#include "ResourceEd.h"
#include "translations.h"

/* global flags and variables */
int 		verbose 					= 0;
char 		*version 					= LXB_VERSION; 
Widget 	selected_widget 	= NULL;   
char 		*savefile_name		= NULL;
char 		*application_name = NULL;

/* global linked list of application widget data */
WSTRUCT *tree_ptr 				= NULL;					/* bottom of linked list */
WSTRUCT *top_ptr 					= NULL;				/* top of linked list */

/* global main lxb shell widget */
Widget 	shell 						= NULL;

XtAppContext appcontext;

/* global toplevel shell of application being built */
Widget 	appShell 					= NULL;

/* local prototypes */
static
int cmdline_options(int argc, char *argv[]);

/**************************************************
 * Funcion: cmdline_options
 **************************************************/
static
int cmdline_options(int argc, char *argv[])
{
	int i;
	int status = 0;

	i=1;
	while (i < argc){
		if ( (strcmp(argv[i], "-V") == 0) ){

			/* print version of lxb */
			fprintf(stderr, "\n\n    lxb (ALPHA version %s): an X/Motif GUI Builder\n\n", version); 
			status = 1;

		} else if ( (strcmp(argv[i], "-v") == 0) ){

			/* verbose level for debugging */
			i++;
			if (i<argc){

				verbose = atoi(argv[i]);
			  printf("verbose level changed to: %d\n", verbose);
				i++;
			};

		} else {

			/* output command line options */
			printf("Unknown argument: %s\n", argv[i]);
			printf("Options:\n");
			printf("  -V      :  print version of lxb\n\n");
			status = 1;
		};
		i++;
	};

	return (status);
}
/**************************************************
 * Funcion: main
 **************************************************/
int 
main(int argc, char **argv)
{
	Arg args[5];
	char title[124];
	int n;
	int status;

	/* get command line options */
	status = cmdline_options(argc, argv);
	shell = NULL;

	if (status == 0){

		/* Initialize toolkit and parse command line options. */
		shell = XtVaAppInitialize(&appcontext,
						  "Lxb",
						  NULL,
						  0,
						  &argc,
						  argv,
						  fallbacks,
						  NULL);


		/* to debug with editres */
		XtAddEventHandler(shell, (EventMask)0, True, _XEditResCheckMessages, NULL);

		application_name = XtNewString("lxbApp");
		savefile_name = XtNewString("lxbApp.lxb");

		/* title in main window bar */
		strcpy(title, "LXB - Application Save File: ");
		strcat(title, savefile_name);

		n=0;
		XtSetArg(args[n], XmNtitle, title);n++;
		XtSetArg(args[n], XmNiconName, "lxb");n++;
		XtSetValues(shell, args, n);

		/* build the 3 main GUI windows */
		build_gui(shell);

		build_resource_editor(shell);

		build_pallet(shell);

		XtRealizeWidget(shell);

		add_noop_action();
		XtAppMainLoop(appcontext);
	};
}
