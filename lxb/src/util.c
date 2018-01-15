/**************************************************
*
* File: util.c
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
#include "show_calledit.h"
#include "show_res.h"
#include "selected.h"

#include "util.h"

/**************************************************
 *
 * Function: call_callback
 *
 *	Display the callbacks associated with this widget
 *
 **************************************************/
void
call_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	show_callbacks();
}
/**************************************************
 *
 * Function: res_callback
 *
 *	Display the standard resources associated with this widget
 *
 **************************************************/
void
res_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	show_resources();
}
/**************************************************
 *
 * Function: constr_callback
 *
 *	Display the constraint resources associated with this widget
 *
 **************************************************/
void
constr_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	show_constraints();
}
/**************************************************
 *
 * Function: values_selection_callback
 *
 *	string inserted in text widget when values list value selected
 *
 **************************************************/
void
values_selection_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	XmString 	item;
	char 			*value_name;
	XmListCallbackStruct *xl = (XmListCallbackStruct *)call_data;

	item = xl->item;

	/* get the resource name */
	XmStringGetLtoR(item, XmSTRING_DEFAULT_CHARSET, &value_name);

	/* write it in the text widget */
	XmTextFieldSetString(value_text, value_name);
	XmTextFieldSetInsertionPosition(value_text, strlen(value_name)); 

}
/**************************************************
 *
 * Function: set_callback
 *
 *	Called when the "Set Resource" button is pressed,
 *	to set the highlighted (selected) resource named
 *	in the List widget to the value present in the
 *	Text (widget) input field.
 *
 **************************************************/
void
set_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	set_selected_resource(w); 
}
/**************************************************
 *
 * Function: selection_callback
 *
 * Called when a standard resource name is clicked on
 * in the List widget containing all resources.
 *
 **************************************************/
void
selection_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	get_selected_resource(w, call_data);
}
