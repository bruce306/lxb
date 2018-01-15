/**********************************************************************************
 *
 * File: children.c - get all children of a given widget
 *
 *		Using the Xt mechanism to get all children does not work for menus. The parent
 *		of a MenuShell is the menubar, but it is not listed as it's child with the
 *		Intrinsics.
 *
 *		So we have to use our own linked list of GUI information.
 * 
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **********************************************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "children.h"
#include "data.h"

/**********************************************************************************
 *
 *	Function:	get_children - use the LXB linked list.
 *		This can only be used on widgets with children NOT created autmatically,
 *		since in that case they will not be in the list.
 *
 * 	Inputs:
 *		widget	:	widget to get all children of
 *		
 *	Returns all the children, and the number.
 * 
 *******************************************************************************/
WidgetList
get_children(Widget widget, int *no_allkids)
{
	int i;
	int num;
	Widget tbd_list[100];
	int no_tbd;
	Widget *wptr;
	WidgetList newkids;
	Widget *allkids;

	WSTRUCT *ptr;
	int parent_key;
	int start;

	/* initialize */
	allkids = NULL;
	*no_allkids = 0;

	tbd_list[0] = widget;
	no_tbd = 1;

	/* do till all widgets checked */
	while (no_tbd != 0){

		no_tbd--;

		parent_key = (widget_ptr(tbd_list[no_tbd]))->key;
		num = 0;
		start = no_tbd;

		/* can only if have children if subclass of Composite */
		if (XtIsSubclass(widget, compositeWidgetClass)){

			/* get all immediate children */
			ptr = top_ptr;
			while (ptr !=NULL){

				if (ptr->parent == parent_key){

					/* add the children to the list to be checked for kids */
					tbd_list[no_tbd] = ptr->instance;

					no_tbd++;
					num++;
				};
		
				ptr = ptr->last;
			};
		};

		/* if any children add them to the list */ 
		if (num != 0) {

			/* add the children to the list of all children of the input widget */
			newkids = (Widget *)XtMalloc(sizeof(Widget) * (*no_allkids + num));

			/* copy old list of all kids onto new list of all kids */
			for (i=0; i<*no_allkids; i++)
				newkids[i] = allkids[i];

			/* append the newfound kids */
			for (i=*no_allkids; i<*no_allkids + num; i++){
				newkids[i] = tbd_list[start];
				start++;
			};

			/* make newkids all kids */
			XtFree((char *)allkids);
			allkids = newkids;

			/* new number of all children */
			*no_allkids = *no_allkids + num;
		};
	};

	if (verbose >3){
		printf("\nNo of children: (%d)  of widget: %s\n", *no_allkids, XtName(widget));
		wptr = allkids;
		for (i=0; i<*no_allkids; i++){
			printf("    Child: %s\n", XtName(*wptr));
			wptr++;
		};
		printf("\n");
	};

	return(allkids);

}
/**********************************************************************************
 *
 *	Function:	get_xchildren - get all the descendents of the widget. 
 *		Uses the "XmNchildren" resource. Does not work for menus (see above).
 *		
 *		This is useful for getting all children of a composite that were made
 *		automagically by X (XmScale, ScrolledText, etc). 
 *
 * 	Inputs:
 *		widget	:	widget to get all children of
 *		
 *	Returns all the children, and the number.
 * 
 *******************************************************************************/
WidgetList
get_xchildren(Widget widget, int *no_allkids)
{
	Arg args[3];
	int i;
	WidgetList children;
	int num;
	Widget tbd_list[100];
	int no_tbd;
	Widget *wptr;
	WidgetList newkids;
	Widget *allkids;

	/* initialize */
	allkids = NULL;
	*no_allkids = 0;

	tbd_list[0] = widget;
	no_tbd = 1;

	/* do till all widgets checked */
	while (no_tbd != 0){

		no_tbd--;

		if (verbose >3)
			printf("getting children of: (%s)\n", XtName(tbd_list[no_tbd]));

		/* can only if have children if subclass of Composite */
		num = 0;
		if (XtIsSubclass(widget, compositeWidgetClass)){

			/* get children */
			XtSetArg(args[0], XmNnumChildren, &num);
			XtSetArg(args[1], XmNchildren, &children);
			XtGetValues(tbd_list[no_tbd], args, 2);           
		};

		if (verbose >3)
			printf("number of children found: (%d)\n", num);

		/* if any children add them to the lists */ 
		if (num != 0) {

			wptr = children;

			/* add the children to the list to be checked for kids */
			for (i=no_tbd; i<no_tbd + num; i++){

				tbd_list[i] = *wptr;
				wptr++;
			};

			/* new number of widgets to check */
			no_tbd = no_tbd + num;

			/* add the children to the list of all children of the input widget */
			newkids = (Widget *)XtMalloc(sizeof(Widget) * (*no_allkids + num));

			/* copy old list of all kids onto new list of all kids */
			for (i=0; i<*no_allkids; i++){
				newkids[i] = allkids[i];
			};

			/* append the newfound kids */
			wptr = children;
			for (i=*no_allkids; i<*no_allkids + num; i++){

				newkids[i] = *wptr;
				wptr++;
			};

			/* make newkids all kids */
			XtFree((char *)allkids);
			allkids = newkids;

			/* new number of all children */
			*no_allkids = *no_allkids + num;
		};
	};

	if (verbose >3){
		printf("\nNo of children: (%d)  of widget: %s\n", *no_allkids, XtName(widget));
		wptr = allkids;
		for (i=0; i<*no_allkids; i++){
			printf("    Child: %s\n", XtName(*wptr));
			wptr++;
		};
		printf("\n");
	};

	return(allkids);

}
