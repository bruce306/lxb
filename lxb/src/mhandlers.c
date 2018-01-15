/**************************************************
*
* File: mhandler.c - mouse handlers
*
*    Copyright (C) 1997  Bruce Parkin 
*
* NOTE: work needs to be done on this model/code 
*
*		A better model that would work would be to
*		use rubber banding, then at MB release traverse
*		up and down widget hierarchy till all set.
*		Should use XtMakeGeomtryRequest...
*
**************************************************/

/* include files */
#include <stdio.h>
#include <X11/IntrinsicP.h>
#include <Xm/Xm.h>
#include <Xm/Frame.h>
#include <Xm/RowColumn.h>
#include "lxb.h"
#include "select.h"
#include "misc.h"
#include "data.h"
#include "recres.h"
#include "ResourceEd.h"
#include "mhandlers.h"

/* local static vars */
/* note: unsigned shorts can't be negative? */
static int pointerx= 0;
static int pointery= 0;
static int rootx= 0;
static int rooty= 0;
static int originx = 0;
static int originy = 0;
static int width = 0;
static int height = 0;

/* event handlers */
static void
press_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag);
static void
release_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag);
static void
move_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag);
static void
resize_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag);

/***********************************************************
 *
 * Function: press_handler - either mb1 or mb2 was pressed
 *
 **********************************************************/
static void
press_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag)
{
	XButtonEvent *xb;
	Arg args[5];
	Dimension wi,he;
	Boolean ss;
	Window win;

	if (verbose >6)
		printf("called press handler\n");

	xb = (XButtonEvent*)event;

	if (xb->button == Button1) {

		/* Here we SELECT a widget with MB1, perhaps begin a move */

		/* get data for MOVE; world of the parent window , get x,y coords of origin */
		rootx = xb->x_root;
		rooty = xb->y_root;

		/* XmFrames are weird - if parent, get the origin of Frame */
		if (XtClass((XtParent(w))) == xmFrameWidgetClass)
			ss = XTranslateCoordinates(XtDisplay(w), XtWindow(w), XtWindow( XtParent(XtParent(w)) ), 
											0, 0, &originx, &originy, &win);
		else
			ss = XTranslateCoordinates(XtDisplay(w), XtWindow(w), XtWindow(XtParent(w)), 
											0, 0, &originx, &originy, &win);

		/* saves repaint */
		if (w != selected_widget){
			unselect(selected_widget);
			select_widget(w);
		};

		/* actively grab the pointer for a move */
		XtGrabPointer(w, True, ButtonMotionMask, GrabModeAsync, GrabModeAsync, XtWindow(w), None, CurrentTime);

	};

	if (xb->button == Button2) {

		/* Here we begin a RESIZE of a widget */

		/* get data for RESIZE with MB2 */
		pointerx = xb->x;
		pointery = xb->y;

		XtSetArg(args[0], XmNwidth, &wi);
		XtSetArg(args[1], XmNheight, &he);
		XtGetValues(w, args, 2);

		width = (int)wi;
		height = (int)he;

	};

}
/*************************************************************
 *
 * Function: release_handler - either mb1 or mb2 was released
 *
 ************************************************************/
static void
release_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag)
{
	XButtonEvent *xb;
	Arg args[5];
	Dimension wi,he;
	Position x, y;
	Boolean ss;
	Window win;
	WSTRUCT *wptr;
	char number[10]; 
	Widget tmpw;
  WidgetList  widgetlist;          
	int n;

	if (verbose >6)
		printf("called release handler\n");

	xb = (XButtonEvent*)event;

	if (xb->button == Button1) {

		/* Here we STOP MOVING a widget with MB1 */

		XtUngrabPointer(selected_widget, CurrentTime);

		tmpw = selected_widget;

		/* XmFrames are weird */
		if (XtClass(XtParent(selected_widget)) == xmFrameWidgetClass){
			tmpw = XtParent(w);
		};
		
		/* record the change in resource values for a "MOVE" */
		wptr = widget_ptr(tmpw);

		/* get the real move - sometimes parents restrict move - buggy math */
		XtSetArg(args[0], XmNx, &x);
		XtSetArg(args[1], XmNy, &y);
		XtGetValues(tmpw, args, 2);    

		/* convert to string */
		sprintf(number, "%d", x);
    re_record_resource(wptr, XmNx, number, -999);

		/* convert to string */
		sprintf(number, "%d", y);
    re_record_resource(wptr, XmNy, number, -999);     

	} else if (xb->button == Button2) {

		/* Here we STOP RESIZING a widget */

		/* Frames need to allow child to set size because it is the 
       only container widget that cannot be kept from resizing */

		w = selected_widget;

		if (XtClass(w) == xmFrameWidgetClass){

			/* get the child of the frame */
			XtSetArg(args[1], XmNchildren, &widgetlist);
			XtGetValues(w, args, 2);    
			w = *widgetlist;
		};

		XtSetArg(args[0], XmNwidth, &width);
		XtSetArg(args[1], XmNheight, &height);
		XtGetValues(w, args, 2);    

		/* record the change in resource values for a "RESIZE" */
		wptr = widget_ptr(w);

		/* convert to string */
		sprintf(number, "%d", width);
		re_record_resource(wptr, XmNwidth, number, -999);

		/* convert to string */
		sprintf(number, "%d", height);
		re_record_resource(wptr, XmNheight, number, -999);     

	};
}
/********************************************************************
*
* Function: move_handler - called when MB1 is pressed and the pointer 
*		is moved.
*
*	MB1 MOVE USES: originx, originy, rootx, rooty,
*
********************************************************************/
static void
move_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag)
{
	Arg args[5];
	int xdelta = 0;
	int ydelta = 0;
	XMotionEvent *xm = (XMotionEvent*)event;
	XButtonEvent *xb;
	WSTRUCT *wptr;

	if (verbose >6)
		printf("called move handler\n");

	if (w != selected_widget)
		return;

	/* if parent is Frame, move it, not child */
	if (XtClass(XtParent(w)) == xmFrameWidgetClass) 
		w = XtParent(w);

	/* if all resources are fixed, don't allow movement */
	wptr = widget_ptr(w);
	if (wptr->fixed == True)
		return;

	xb = (XButtonEvent*)event;
	if (xb->type == MotionNotify) {

		XtSetArg(args[0], XmNx, (Position)originx);
		XtSetArg(args[1], XmNy, (Position)originy);
		XtSetValues(w, args, 2);

/*
		XtMoveWidget(w, (Position)originx, (Position)originy);

*/
		xdelta = xm->x_root - rootx;
		ydelta = xm->y_root - rooty;
		rootx = xm->x_root;
		rooty = xm->y_root;

		originx = originx + xdelta;
		originy = originy + ydelta;

		if (originx < 0)
			originx = 0;
		if (originy < 0)
			originy = 0;
	};
}
/**********************************************************
*
* Function: resize_handler - called when mb2 is pressed
*		and the pointer is MOVED.
*
*	MB2 RESIZE USES: pointerx, pointery, width, height
*
**********************************************************/
static void
resize_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *flag)
{
	XMotionEvent *xm;
	Arg args[5];

	if (verbose >6)
		printf("called resize handler\n");

	if (w != selected_widget)
		return;

	/* helps user if we don't allow resize widgets inside of RowColumns */
	if (XtClass(XtParent(w)) == xmRowColumnWidgetClass)
		return;

	xm = (XMotionEvent*)event;

	if (xm->type == MotionNotify){

/*
		XtMakeResizeRequest(w, (Dimension)width, (Dimension)height, NULL, NULL);
		XtResizeWidget(w, (Dimension)width, (Dimension)height, border_width);
*/

		XtSetArg(args[0], XmNwidth, (Dimension)width);
		XtSetArg(args[1], XmNheight, (Dimension)height);
		XtSetValues(w, args, 2);

		width = width + (xm->x-pointerx);
		height = height + (xm->y-pointery);

		pointerx = xm->x;
		pointery = xm->y;

		if (width < 1)
			width = 1;
		if (height < 1)
			height = 1;

	};
}
/**************************************************
*
* Function: install_select_handlers - given to all
*	instantiated widgets for now
*
**************************************************/
void
install_select_handlers(Widget w)
{
  XtAddEventHandler(w, ButtonPressMask, True, press_handler, NULL);
  XtAddEventHandler(w, ButtonReleaseMask, True, release_handler, NULL);
  XtAddEventHandler(w, Button1MotionMask, True, move_handler, NULL);
  XtAddEventHandler(w, Button2MotionMask, True, resize_handler, NULL);
}
/**************************************************
 *
 * Function: uninstall_select_handlers
 *
 **************************************************/
void
uninstall_select_handlers(Widget w)
{
  XtRemoveEventHandler(w, XtAllEvents, True, press_handler, NULL);
  XtRemoveEventHandler(w, XtAllEvents, True, release_handler, NULL);
  XtRemoveEventHandler(w, XtAllEvents, True, move_handler, NULL);
  XtRemoveEventHandler(w, XtAllEvents, True, resize_handler, NULL);
}
