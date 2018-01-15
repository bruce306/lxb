/**************************************************
 *
 * File: delete.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "select.h"
#include "data.h"
#include "children.h"
#include "delete.h"

static void
delete_primitive_widget(Widget w, WSTRUCT *wptr);

static void 
relink(WSTRUCT *wptr);

static void 
free_resource_list(WSTRUCT *wptr);

/*************************************************************************
*
*	Function:	delete_widget - Delete the input widget.
*
*		Override is True if the "perm" flag is to be disregarded
*		and the widget always deleted.
*	
*		This is called when: 
*
*		1) 	The user presses the delete button and a widget
*			 	is "Selected" (the one that is to be deleted).
*				Override is False in this case.
*
*		2)	Programatically, when sub-parts of Menus are to be deleted
*				(Specifically, when the cascade button is deleted by the user,
*				a Destroy callback will call this function to also delete the
*				associated Pulldown, and possibly the MenuShell.
* 
**************************************************************************/
void 
delete_widget(Widget w, Boolean override)
{
	WSTRUCT *wptr;
	int i;
	WidgetList allkids;
	Widget *kidptr;
	int no_allkids;

	/* get the node in the linked list */
	wptr = widget_ptr(w);

	/* if one of the "hidden" widgets" forget it */
	if (wptr->perm == True){
		
		if (!override){
			fprintf(stderr, "Cannot delete this widget %s\n", XtName(w));
			return;
		};
	};

	/* unselect the widget - won't be if this fuction called programatically */
	if (selected_widget == w)
		unselect(w);

	/* can only if have children if subclass of Composite */
	if (!XtIsComposite(w)){
		delete_primitive_widget(w, wptr);
		return;
	};

	/* get all children */
	allkids = get_children(w, &no_allkids);

	kidptr = allkids;

	if (verbose >3)
		printf("delete widget=================\n");

	/* delete all children */
	for (i=0; i<no_allkids; i++){

		if (verbose >3){
			printf("widget child:	%s\n", XtName(*kidptr));
		};

		wptr = widget_ptr(*kidptr);

		/* kludge for now; some composites like XmScale */
		if (wptr != NULL){

			/* remove node and relink list */
			relink(wptr);

			/* free resource list */
			free_resource_list(wptr);

			/* free node */
			XtFree((char *)(wptr));

		};

		kidptr++;
	};

	if (verbose >3){
		printf("widget:	%s\n", XtName(w));
	};

	/* do the widget itself */
	wptr = widget_ptr(w);

	/* remove node and relink list */
	relink(wptr);

	/* free resource list */
	free_resource_list(wptr);

	/* free node */
	XtFree((char *)(wptr));

	/* Destroy the widget instance and it's children */
	XtDestroyWidget(w);

	XtFree((char *)allkids);

}
/**************************************************
 *
 *	Function:	delete_primitive_widget
 *
 *	Delete the selected XmPrimitive widget.
 * 
 **************************************************/
static void
delete_primitive_widget(Widget w, WSTRUCT *wptr)
{

	/* simple - just delete this one widget */
	
	/* remove node and relink list */
	relink(wptr);

	/* free resource list */
	free_resource_list(wptr);

	/* Destroy the widget instance and it's children */
	XtDestroyWidget(w);

	XtFree((char *)wptr);

}
/**************************************************
 *
 *	Function:	free_gui_list
 *
 *	Free the linked list containing all gui info:
 *	widgets, and their resources. Also destroy the
 *	widgets and GUI itself.
 *
 *	Called prior to opening another save file or 
 *	starting a new application.
 *
 **************************************************/
void 
free_gui_list()
{
	WSTRUCT *top;
	RES			*rptr;
	CALL		*cptr;

	/* unselect & deactivate  widget */
	unselect(selected_widget);

	/* NULL out the status area appname */

	/* free all widgets; start at main parent */
	while (top_ptr != NULL){

		/* free widget node's resources */
		while (top_ptr->resptr != NULL){

			rptr = top_ptr->resptr->next;
			XtFree((char *)top_ptr->resptr);
			top_ptr->resptr = rptr;
		};

		/* free the widget node's callback list */
		while (top_ptr->callptr != NULL){

			cptr = top_ptr->callptr->next;
			XtFree((char *)top_ptr->callptr);
			top_ptr->callptr = cptr;
		};

		/* Destroy the application, shell and children */
		XtDestroyWidget(top_ptr->instance);

		/* get next in list */
		top = top_ptr->last;

		/* free current node in list */
		XtFree((char *)top_ptr);
	
		/* reset top of list to next in list */
		top_ptr = top;
	};

	top_ptr = NULL;
	tree_ptr = NULL;

	appShell = NULL;
}
/**************************************************
 *
 *	Function:	free_resource_list
 *
 *	free the allocated memory of the resource list
 * 
 **************************************************/
static void 
free_resource_list(WSTRUCT *wptr)
{
	RES	*rptr;
	RES	*nxt;

	rptr = wptr->resptr;
	
	while (rptr != NULL){

		nxt = rptr->next;
		XtFree((char *)rptr);
		rptr = nxt;
	};

}
/**************************************************
 *
 *	Function:	relink
 *
 *	remove input node, relink the nodes around it
 * 
 **************************************************/
static void 
relink(WSTRUCT *wptr)
{

	/* check for only one widget */
	if ( (wptr->next == NULL) && (wptr->last == NULL) ){

		appShell = NULL;

		/* no relink required */
		top_ptr = NULL;
		tree_ptr = NULL;
		return;
	};

	/* check for head */
	if (wptr->next == NULL) {

		appShell = NULL;

		/* head of list */
		top_ptr = wptr->last;
		wptr->last->next = NULL;
		return;
	};

	/* check for tail */
	if (wptr->last == NULL) {

		/* tail of list */
		tree_ptr = wptr->next;
		wptr->next->last = NULL;
		return;
	};

	/* must be interior node */

	/* head side */
	wptr->next->last = wptr->last;

	/* tail side */
	wptr->last->next = wptr->next;
	
}
