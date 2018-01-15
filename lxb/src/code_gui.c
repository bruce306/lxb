/**************************************************
*
* File: code_gui.c
*
*    Copyright (C) 1997  Bruce Parkin 
*
**************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "data.h"
#include "code_special.h"
#include "code_gui.h"

/**************************************************
 *
 * Function: code_gui
 *
 *	write the X widget creation code and the resource 
 *	new setting code.
 *
 **************************************************/
int
code_gui(FILE *file)
{
	WSTRUCT *ptr;
	char 		*class_name;
	Widget 	parent_widget;
	char 		*parent_name;
	RES 		*rptr;
	int 		n;

	/* skip the shell - already made */
	ptr = top_ptr->last;

	while (ptr != NULL){

		/* for scrolled window children */
		if (!strcmp("EXISTING", ptr->create_function)) {
			ptr = ptr->last;
			continue;
		};

		n=0;

		/* FIRST: the resources for the widget */
		rptr = ptr->resptr;
		while (rptr != NULL){

			/* see if special resource conversion code needs to be written */
			if ( (rptr->enumlist < 0) && (rptr->enumlist > -100) ){

				if (rptr->enumlist == -3){

					/* XmString */
					code_special_xmstring(file, rptr, n);

				} else if (rptr->enumlist == -1) {

					/* Colorname */
					code_special_colorname(file, top_ptr->appname, rptr, n);

				} else if (rptr->enumlist == -2) {

					/* Widget */
					code_special_widget(file, rptr, n);

				} else if (rptr->enumlist == -4){

					/* fontlist */
					code_special_fontlist(file, top_ptr->appname, rptr, n);

				} else if (rptr->enumlist == -5) {

					/* Form child sibling Widget */
					code_special_widget(file, rptr, n);

				}else {

					fprintf(stderr, "\ncode_gui: Unknown special resource: enumlist = %d\n", rptr->enumlist);
					fprintf(stderr, "    Resource: XmN%s  Value: %s\n", rptr->name, rptr->value);

				};

			} else {

				/* normal resource */
				fprintf(file, "\tXtSetArg(args[%d], XmN%s, %s);\n", n, rptr->name, rptr->value);
			};

			rptr = rptr->next;
			n++;
		};

		/* get some info on the widget */
		class_name = get_widget_classname(ptr->instance);
/*
		parent_widget = XtParent(ptr->instance);
*/
		parent_widget = get_parent_widget(ptr->parent);
		parent_name = widget_name(parent_widget);

		/* make the widget with it's changed resources */
		if (ptr->create_function[0] == 0){

			/* check to see if the widget is managed */
			if (ptr->managed == True){

				fprintf(file, "\t%s = XtCreateManagedWidget(\"%s\", %s, %s, args, %d);\n", 
								ptr->appname, ptr->appname, class_name, parent_name, n);
			} else {

				fprintf(file, "\t%s = XtCreateWidget(\"%s\", %s, %s, args, %d);\n", 
								ptr->appname, ptr->appname, class_name, parent_name, n);
			};

		} else {

			fprintf(file, "\t%s = %s(%s, \"%s\", args, %d);\n",
						ptr->appname, ptr->create_function, parent_name, ptr->appname, n);

			if (ptr->managed == True)
				fprintf(file, "\tXtManageChild(%s);\n", ptr->appname);

		};

		fprintf(file, "\n");

		/* code freeing special resources & internal data structures */
		code_special_free(file);

		XtFree(class_name);
		ptr = ptr->last;
	};

	return (OK);

}
/**************************************************
 *
 * Function: code_global_vars
 *
 **************************************************/
int
code_global_vars(FILE *file)
{
	WSTRUCT *ptr;

	fprintf(file, "/* global variables */\n");

	ptr = top_ptr;
	while (ptr != NULL){

		/* hack for ScrolledWindow children */
		if (strcmp(ptr->create_function, "EXISTING")){

			if (ptr->global == True)
				fprintf(file, "Widget %s;\n", ptr->appname);

		};

		ptr = ptr->last;
	};
	fprintf(file, "\n");

	return (OK);

}
/**************************************************
 *
 * Function: code_local_vars
 *
 **************************************************/
int
code_local_vars(FILE *file)
{
	WSTRUCT *ptr;

	ptr = top_ptr;
	while (ptr != NULL){

		/* hack for ScrolledWindow children */
		if (strcmp(ptr->create_function, "EXISTING")){

			if (ptr->global == False)
				fprintf(file, "\tWidget %s;\n", ptr->appname);

		};

		ptr = ptr->last;
	};
	fprintf(file, "\n");

	return (OK);

}
