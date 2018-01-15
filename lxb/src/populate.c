/********************************************************************
*
* File: populate.c - functions used to populate the wtree window
*
*	Copyright 1996  By Bruce Parkin
*
********************************************************************/

/* include files */
#include <stdio.h>

#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <X11/Xaw/Tree.h>

#include "lxb.h"
#include "data.h"
#include "color.h"
#include "select.h"
#include "Wtree.h"
#include "populate.h"

/* local data structures */
typedef struct _tstruct{
	Widget treenode;
	Widget treenode_parent;
	Widget actual;
	Widget actual_parent;
	struct _tstruct *next;
} TSTRUCT;

/* local variables */
static TSTRUCT *tree_top = NULL;
static Pixel ac;												/* armed color */
static Pixel bg;												/* unselected background color */
static Pixel tsc;												/* unselected top shadow color */
static Pixel bsc;												/* unselected bottom shadow color */

/* local prototypes */
static Widget
get_parent_node(Widget actual_parent);

static TSTRUCT *
get_wtree_node(Widget w);

static void
show_node_selected(Widget w);

static void
show_allnodes_unselected();

static void
node_callback(Widget w, XtPointer client_data, XtPointer call_data);

/**************************************************
*
* Function: populate_wtree - this will populate the
*		entire tree in one fell swoop.
* 
**************************************************/
void
populate_wtree()
{
	Widget treenode_parent;
	Arg args[5];
	TSTRUCT *a_ptr;
	WSTRUCT *ptr;
	int n;

	/* if it exists already it's old: free the list */
	while (tree_top != NULL) {

		XtDestroyWidget(tree_top->treenode);

		a_ptr = tree_top->next;
		XtFree((char *)tree_top);
		tree_top = a_ptr;
	};

	/* head of GUI linked list */
	ptr = top_ptr;

	/* 	Use the real hierarchy of widgets, not the one recorded in the GUI linked list...
		However, we are not using the actual widget name; but the one recorded in the list.
	*/

	/* get all actual widget instances and their actual parents; then create the node */
	while (ptr != NULL){

		a_ptr = (TSTRUCT *)XtMalloc(sizeof(TSTRUCT));
		memset(a_ptr, 0, sizeof(TSTRUCT));
	
		a_ptr->actual = ptr->instance;
		
		/* shell has parent of -1 */
		if (ptr->parent == -1)
			a_ptr->actual_parent = NULL;
		else 
			a_ptr->actual_parent = XtParent(ptr->instance);

		/* make the node in the tree */

		if (verbose >4)
			printf("Making node in tree for widget: %s\n", ptr->appname);

		a_ptr->treenode = XtCreateManagedWidget(ptr->appname, xmPushButtonWidgetClass, tree, args, 0);

		XtAddCallback(a_ptr->treenode, XmNactivateCallback, node_callback, NULL);

		a_ptr->next = tree_top;
		tree_top = a_ptr;

		ptr = ptr->last;
	};

	/* now set the parent of each node in the tree */
	a_ptr = tree_top;
	while (a_ptr != NULL){

		/* shell widget has no parent */
		if (a_ptr->actual_parent == NULL) {

			treenode_parent = NULL;
		} else {

			/* get the corresponding parent in the tree */
			treenode_parent = get_parent_node(a_ptr->actual_parent);

			if (treenode_parent == NULL)
				fprintf(stderr, "Could not find tree node parent of widget %s\n", XtName(a_ptr->actual));
		};

		if (treenode_parent != NULL){
			XtSetArg(args[0], XtNtreeParent, treenode_parent);
			XtSetValues(a_ptr->treenode, args, 1);
		};

		a_ptr = a_ptr->next;
	};

	/* insure buttons made */
	if (tree_top != NULL){

		/* force a re-layout of the tree */
		XawTreeForceLayout(tree);

		/* get the resource values needed to graphically select */
		n=0;
		XtSetArg(args[n], XmNbackground, &bg);n++;
		XtSetArg(args[n], XmNarmColor, &ac);n++;
		XtSetArg(args[n], XmNtopShadowColor, &tsc);n++;
		XtSetArg(args[n], XmNbottomShadowColor, &bsc);n++;
		XtGetValues(tree_top->treenode, args, n);
	};

}
/**************************************************
 *
 *  Function: get_parent_node
 *
 *	Inputs:
 *		actual_parent is the widget in the GUI 
 *
 *	Returns the tree_node widget of the actual parent
 *
 **************************************************/
static Widget
get_parent_node(Widget actual_parent)
{
  Widget tree_parent;
  TSTRUCT *ptr;
  Boolean found = False;

  tree_parent = NULL;
  ptr = tree_top;
  while (ptr != NULL) {

    if (actual_parent == ptr->actual){
      found = True;
      tree_parent = ptr->treenode;
      break;
    };

    ptr = ptr->next;
  };

  if (!found)
    fprintf(stderr, "get_parent_node: cannot find tree node for: %s\n", XtName(actual_parent));

  return (tree_parent);
}                                         

/************************************************************************************
 *
 *  Function: node_callback
 *
 *		Called when a node in the tree is clicked on in order to "Select" the 
 *		corresponding widget in the GUI application being built.
 *
 ************************************************************************************/
static void
node_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
	TSTRUCT *ptr;
	Widget gui_widget;

	/* unselect all nodes */
	unselect_wtree_node();

	/* get the GUI widget to select */
  ptr = tree_top;
  while (ptr != NULL) {

    if (ptr->treenode == w){
      gui_widget = ptr->actual;
      break;
    };
    ptr = ptr->next;
  };

	/* do the "Select" */
	unselect(selected_widget);
	select_widget(gui_widget);

	/* change the appearence of the button to show it's "Selected" */
	show_node_selected(w);

}
/******************************************************************
*
* Function: unselect_wtree_node
* 
******************************************************************/
void
unselect_wtree_node()
{
	show_allnodes_unselected();
}
/******************************************************************
*
* Function: select_wtree_node
* 
* 	Widget w is the actual widget in the GUI being built
* 	When it is "Selected" via mb1 then this function is called
*		to "Select" the corresponding node in the tree.
* 
******************************************************************/
int
select_wtree_node(Widget w)
{
	TSTRUCT *node = NULL;
	int status = OK;

	/* get the node */
	node = get_wtree_node(w);
	if (node == NULL){
		fprintf(stderr,"(select_wtree_node): could not select node in tree\n");
		return (NOTOK);
	};

	/* show all nodes unselected */
	show_allnodes_unselected();

	/* show node is selected */
	show_node_selected(node->treenode);

	return (status);
}
/******************************************************************
*
* Function: show_node_selected
* 
* 	This does the graphic stuff to make the node in the tree
*		obvious that it represents the selected widget.
* 
* 	w is the node in the tree.
* 
******************************************************************/
static void
show_node_selected(Widget w)
{
	int n;
	Arg args[7];

	if (verbose >4)
			printf("Changing node to selected: (%s)\n", XtName(w));

	n=0;
	XtSetArg(args[n], XmNbackground, ac);n++;
	XtSetArg(args[n], XmNtopShadowColor, bsc);n++;
	XtSetArg(args[n], XmNbottomShadowColor, tsc);n++;
	XtSetArg(args[n], XmNborderWidth, 1);n++;
	XtSetValues(w, args, n);

}
/******************************************************************
*
* Function: show_allnodes_unselected
* 
* 	This does the graphic stuff to make the node in the tree
*		obvious that it represents the selected widget.
* 
******************************************************************/
static void
show_allnodes_unselected()
{
	int n;
	Arg args[7];
	TSTRUCT *ptr;

	ptr = tree_top;
	while (ptr != NULL){

		if (verbose >4)
				printf("Changing nodes to unselected: (%s)\n", XtName(ptr->treenode));

		n=0;
		XtSetArg(args[n], XmNbackground, bg);n++;
		XtSetArg(args[n], XmNtopShadowColor, tsc);n++;
		XtSetArg(args[n], XmNbottomShadowColor, bsc);n++;
		XtSetArg(args[n], XmNborderWidth, 0);n++;
		XtSetValues(ptr->treenode, args, n);

		ptr = ptr->next;
	};

}
/******************************************************************
*
* Function: get_node_widget
* 
* 	Widget w is the actual widget in the GUI being built.
*	 	Returned is the corresponding node in the tree.

* 	When it is "Selected" via mb1 then this function is called
*		to "Select" the corresponding node in the tree.
* 
******************************************************************/
static TSTRUCT *
get_wtree_node(Widget w)
{
	TSTRUCT *ptr;
	TSTRUCT *node = NULL;

	if (verbose >4)
		printf("Searching for tree node of widget (%s)\n", XtName(w));

	/* get the node of the actual GUI widget */
	ptr = tree_top;
	while (ptr != NULL){

		if (ptr->actual == w) {
			node = ptr;
			break;
		};
		ptr = ptr->next;
	};

	if (node == NULL){
		printf("ERROR (get_wtree_node): didn't find tree node of widget: %s\n", XtName(w));
		return (node);
	};

	return (node);
}
