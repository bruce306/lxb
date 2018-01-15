/**************************************************
*
* File: selected.c
*
*    Copyright (C) 1997  Bruce Parkin 
*
**************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <Xm/List.h>

#include "lxb.h"
#include "ResourceEd.h"
#include "CallbackEd.h"
#include "show_options.h"
#include "show_res.h"

#include "get_resvalue.h"
#include "set_resvalue.h"
#include "selected.h"

/**************************************************
 *
 * Function: set_selected_resource
 *
 *	called to set the selected resource's value -
 *	equal to that in the text input field.
 *
 **************************************************/
void
set_selected_resource(Widget w)
{
	char 					*resource_value;
	char 					*resource_name;
	Arg 					args[2];
	XmStringTable	xms;
	int						status;

	if ((resource_type == RESOURCES) || (resource_type == CONSTRAINTS)) {

		/* get the selected resource name */
		XtSetArg(args[0], XmNselectedItems, &xms);
		XtGetValues(name_list, args, 1);

		if (xms == NULL){

			/* no resource name selected */
			return;
		};

		XmStringGetLtoR(*xms, XmSTRING_DEFAULT_CHARSET, &resource_name);

		/* get the desired resource value to change to */
		resource_value = XmTextGetString(value_text);

		/* TBD check value */
		if (resource_value != NULL){

			status = set_resource_value(resource_name, resource_value);

			if (status != OK){

				fprintf(stderr, "set_selected_resource: problems in doing it for: (%s)  (%s)\n", 
												resource_name, resource_value); 
			};

		};
	};
}
/*************************************************************************************
 *
 * Function: get_selected_resource
 *
 * 	called when a resource type (ie, XmNwidth) in the top "resource name" list is 
 *	selected with a mouse click.
 *
 *	(gets the selected resource type's value, and 
 *	any enumerated list that goes with it, or any
 *	associated special list (ie, colornames from rgb.txt) )
 *
 ************************************************************************************/
void
get_selected_resource(Widget w, XtPointer call_data)
{
	XmString 	item;
	char 			*resource_name;
	char 			*resource_value;
	int				enumlist;

	XmListCallbackStruct *xl;

	/* clear out the enum list widget */
	XmListDeleteAllItems(value_list);

	/* clear out the resource value text widget */
	XmTextSetString(value_text, "");

	xl = (XmListCallbackStruct *)call_data;
	item = xl->item;

	/* get the resource name ("XmNwidth") */
	XmStringGetLtoR(item, XmSTRING_DEFAULT_CHARSET, &resource_name);

	/* put up the Callback editor */
	if (resource_type == CALLBACKS) {
		display_called(w, resource_name);
		return;
	};

	/* get the value for the resource of the selected_widget and "enumlist" */
	resource_value = get_resource_value(resource_name, &enumlist);		

	if (resource_value != NULL){

		/* got the resource value OK */
		XmTextFieldSetString(value_text, resource_value);
		XmTextFieldSetInsertionPosition(value_text, strlen(resource_value));

		/* if there is an enumerated list, or conversions on the options, show them */
		if (enumlist != -999)
			show_options(resource_name, resource_value, &enumlist);

		XtFree(resource_value);

	} else {

		if (enumlist == -5){

			show_options(resource_name, resource_value, &enumlist);

		} else if (enumlist == -100){

			XmTextSetString(value_text, "TBD");

		} else {

			/* ERROR */
			XmTextSetString(value_text, "UNKNOWN: TBD or ERROR");
		};

	};

}
