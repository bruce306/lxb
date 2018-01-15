/**************************************************
*
* File: daig.c
*
*    Copyright (C) 1995  Bruce Parkin 
*
**************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "data.h"
#include "diag.h"

/**************************************************
 *
 *	Function: diag_misc
 *
 **************************************************/
void 
diag_misc(Widget w)
{
	Window root_return;
	Window parent_return;
	Window *children_return;
	Window *wptr;
	unsigned int nchildren_return;
	int i;
	char *name;
	Widget widg;
	int status;

	if (verbose >4)
		printf("diag_misc\n");

	status = XQueryTree(XtDisplay(shell), XtWindow(w), &root_return,
							&parent_return, &children_return, &nchildren_return);

	if (verbose >4){
		printf("no children: %d\n", nchildren_return);

		if (status == 0)
			printf("Query failed\n");
		else
			printf("Query succeeded\n");

	};

	wptr = children_return;
	for (i=0; i<nchildren_return; i++){

		widg = XtWindowToWidget(XtDisplay(shell), *wptr);
		name = XtName(widg);

		printf("%s\n", name);
		wptr++;
	};

	XFree(children_return);	

}
/**************************************************
 *
 *	Function: diag_widget_tree
 *
 *	Print the widget heirarchy.
 *
 **************************************************/
void 
diag_widget_tree()
{
	WSTRUCT 	*ptr;

	ptr = top_ptr;

	while (ptr != NULL){

		printf("Widget:   %s\n", ptr->appname);
		printf("\tIndex:  %d\n", ptr->key);
		printf("\tClass:  %s\n", ptr->class);
		printf("\tParent: %d\n", ptr->parent);
		ptr = ptr->last;
	};
}
/**************************************************
 *
 *	Function: diag_resource_list
 *
 *	Print the widget's resources and Callabacks.
 *
 **************************************************/
void 
diag_resource_list(Widget w)
{
	WSTRUCT 	*wptr;
  RES       *rptr; 
  CALL      *cptr; 

	if (w == NULL){
		printf("Cannot output resources: no selected widget\n");
		return;
	};

	wptr = widget_ptr(w);

	printf("Widget: %s\n", wptr->appname);
	printf("  Edited Resources\n");

	if (wptr->resptr != NULL){

		rptr = wptr->resptr;
		while (rptr != NULL){

			printf("    %s  %s  %d\n", rptr->name, rptr->value, rptr->enumlist);
			rptr = rptr->next;
		};
	};                          

	printf("  Edited Callbacks\n");
	if (wptr->callptr != NULL){

		cptr = wptr->callptr;
		while (cptr != NULL){

			if (strlen(cptr->name) != 0)
				printf("    %s  %s\n", cptr->name, cptr->function);

			cptr = cptr->next;
		};
	};                          

}
