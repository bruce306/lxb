/**************************************************
*
* File: callbacks.c
*
*    Copyright (C) 1997  Bruce Parkin 
*
**************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "data.h"
#include "callbacks.h"

/* local functions */
static void
record_new_callback(WSTRUCT *ptr, char *callback_type, char *callback_name);

/**************************************************
 *
 * Function: get_callback - get the function name
 *	of callback type if in list; else return NULL,
 *
 **************************************************/
char *
get_callback(char *callback_type)
{
	CALL *cptr;
	Boolean found;
	WSTRUCT *ptr;
	char *function_name = NULL;

	found = False;
	ptr = widget_ptr(selected_widget);

	cptr = ptr->callptr;

	while (cptr != NULL){
		
		if ( (strcmp(callback_type, cptr->name) == 0) ){
		
			function_name = XtNewString(cptr->function);

			found = True;
			break;
		};
		cptr = cptr->next;
	};

	return (function_name);
}
/**************************************************
 *
 * Function: remove_callback - delete the callback
 *	from the list for the widget - do it the simple
 *	way: set to NULL.
 *
 **************************************************/
void
remove_callback(char *callback_type)
{
	CALL *cptr;
	WSTRUCT *ptr;

	ptr = widget_ptr(selected_widget);
	cptr = ptr->callptr;

	while (cptr != NULL){
		
		if ( (strcmp(callback_type, cptr->name) == 0) ){

			memset(cptr->name, 0, 50);
			memset(cptr->function, 0, 50);
			break;
		};
		cptr = cptr->next;
	};

}
/**************************************************
 *
 * Function: record_callback
 *
 *	Find if the callback has been recorded already,
 *	and if so change only it's value in the list;
 *	else call "record_new_callback".
 *
 **************************************************/
void
record_callback(char *callback_type, char *callback_name)
{
	CALL *cptr;
	Boolean found;
	WSTRUCT *ptr;

	found = False;

	ptr = widget_ptr(selected_widget);

	cptr = ptr->callptr;

	while (cptr != NULL){
		
		if ( (strcmp(callback_type, cptr->name) == 0) ){
		
			found = True;
			
			/* replace with new values */
			strcpy(cptr->function, callback_name);

			break;
		};
		cptr = cptr->next;
	};

	if (!found)
		record_new_callback(ptr, callback_type, callback_name);
}
/**************************************************
 *
 * Function: record_new_callback
 *
 *	NOTE:	all you have to do is start with the "ptr->resptr"
 *				(which points to a type CALL with member "next")
 *				and walk down the rptr->next until it's "NULL",
 *				and you will have all the nodes.
 *
 **************************************************/
static void
record_new_callback(WSTRUCT *ptr, char *callback_type, char *callback_name)
{
	CALL *cptr;

	cptr = (CALL *)XtMalloc(sizeof(CALL));
	memset(cptr, 0, sizeof(CALL));
	
	strcpy(cptr->name, callback_type);
	strcpy(cptr->function, callback_name);
	
	cptr->next = ptr->callptr;
	ptr->callptr = cptr;
}
