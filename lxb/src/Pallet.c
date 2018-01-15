/***********************************************************************
 *
 * File: pallet.c - build the window that contains the widget pallet.
 *	In it are the button icons for each widget to instantiate.
 *
 *    Copyright (C) 1997  Bruce Parkin 
 *
 ******************************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/PushB.h>
#include <Xm/MenuShell.h>
#include <Xm/ToggleB.h>
#include <Xm/Separator.h>
#include <Xm/DrawnB.h>
#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <Xm/DrawingA.h>
#include <Xm/Scale.h>
#include <Xm/ArrowB.h>
#include <Xm/CascadeB.h>
#include <Xm/ScrolledW.h>
#include <Xm/ScrollBar.h>
#include <Xm/List.h>                  

#include "lxb.h"
#include "forms.h"
#include "instant.h"
#include "Pallet.h"

/* local prototypes */
static Widget
make_icon(Widget icon, char *name, String label, XtCallbackProc callback, XtPointer client_data);
static void
icon_callback(Widget w, XtPointer client_data, XtPointer call_data);       
static void
build_icons(Widget parent);

/* local variables */
static Boolean displayed = False;   /* indicates if it is currently popped up */
static Widget pallet_shell = NULL;

/**************************************************
 *
 * Function: build_pallet
 *
 * 	Build the main area for Widget icons. It consists of a
 *	scrolled window containing buttons (icons) of all widgets
 * 	that can be instatantiated.
 *
 * 	Parent is the main shell
 *
 **************************************************/
Widget
build_pallet(Widget parent)
{
	Arg args[10];
	Cardinal n, i;
	Widget icon_pallet;
	Widget sc_icon_pallet;

	i=0;
	XtSetArg(args[i], XmNallowShellResize, True);i++;
	XtSetArg(args[i], XmNtitle, "LXB Widget Pallet");i++;
	XtSetArg(args[i], XmNdeleteResponse, XmDO_NOTHING);i++;
	XtSetArg(args[i], XmNmwmFunctions,
										MWM_FUNC_RESIZE|MWM_FUNC_MOVE|MWM_FUNC_MINIMIZE|MWM_FUNC_MAXIMIZE);i++;

	pallet_shell = XtCreatePopupShell("pallet_shell", topLevelShellWidgetClass, parent, args, i);

	/* make scrolled window - for the widget icons */
	n=0;
	XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC);n++;
	XtSetArg(args[n], XmNvisualPolicy, XmVARIABLE);n++;
	XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmAS_NEEDED);n++;
	sc_icon_pallet = XtCreateWidget("sc_icon_pallet", xmScrolledWindowWidgetClass, pallet_shell, args, n);

	/* make the container for the icons */
	n=0;
	icon_pallet = XtCreateManagedWidget ("icon_pallet", xmFormWidgetClass, sc_icon_pallet, args, n);

	XmScrolledWindowSetAreas(sc_icon_pallet, NULL, NULL, icon_pallet);

	XtManageChild(sc_icon_pallet);

	/* make the GUI icons themselves, 1 for each Widget Class */
	build_icons(icon_pallet);

	XtPopup(pallet_shell, XtGrabNone);          

	displayed = True;

	return (sc_icon_pallet);
}
/********************************************************************
 *
 * Function: build_icons
 *
 *	Build all the icons for Widgets that can be instantiated.
 *
 * 	parent is the pallet
 *
 *******************************************************************/
static void
build_icons(Widget parent)
{
	int n, i;
	Arg args[15];
	Arg fargs[5];
	Widget rc;
	Widget l;
	Widget f1, f2;

	/* Frame resources */
	i=0;
	XtSetArg(fargs[i], XmNshadowThickness, 2);i++;
	XtSetArg(fargs[i], XmNshadowType, XmSHADOW_OUT);i++;

	/* Rowcolumn resources */
	n=0;
	XtSetArg(args[n], XmNspacing, 5);n++;
	XtSetArg(args[n], XmNorientation, XmHORIZONTAL);n++;
	XtSetArg(args[n], XmNpacking, XmPACK_COLUMN);n++;
	XtSetArg(args[n], XmNadjustLast, False);n++;
	XtSetArg(args[n], XmNentryAlignment, XmALIGNMENT_CENTER);n++;

	/* first grouping - containers */
	l = XtCreateManagedWidget ("l", xmLabelWidgetClass, parent, NULL, 0);
	XtVaSetValues(l, XtVaTypedArg, XmNlabelString, XmRString, "Containers", 10, NULL); 
	XtVaSetValues(l, XmNalignment, XmALIGNMENT_BEGINNING, NULL); 

	/* top, bottom, left, right */
	LxbSetConstraints (l,
										XmATTACH_FORM, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
										parent, NULL, parent, parent); 

	/* top, bottom, left, right */
	LxbSetOffsets (l, 5, 0, 5, 5);

	f1 = XtCreateManagedWidget ("f1", xmFrameWidgetClass, parent, fargs, i);

	XtSetArg(args[n], XmNnumColumns, 2);
	rc = XtCreateManagedWidget ("rc", xmRowColumnWidgetClass, f1, args, n+1);

	/* top, bottom, left, right */
	LxbSetConstraints (f1,
										XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
										l, NULL, parent, parent); 

	/* top, bottom, left, right */
	LxbSetOffsets (f1, 5, 0, 5, 5);

	/* Containers */
	make_icon(rc, "Frame", "Frame", icon_callback, (XtPointer)xmFrameWidgetClass);
	make_icon(rc, "DrawA", "Drawing\nArea", icon_callback, (XtPointer)xmDrawingAreaWidgetClass);
	make_icon(rc, "Form",  "Form", icon_callback, (XtPointer)xmFormWidgetClass);
	make_icon(rc, "BullB", "Bulletin\nBoard", icon_callback, (XtPointer)xmBulletinBoardWidgetClass);
	make_icon(rc, "RowCol","Row\nColumn", icon_callback, (XtPointer)xmRowColumnWidgetClass);

	/* 2nd grouping - primitives */
	l = XtCreateManagedWidget ("l", xmLabelWidgetClass, parent, NULL, 0);
	XtVaSetValues(l, XtVaTypedArg, XmNlabelString, XmRString, "Primitives", 10, NULL); 
	XtVaSetValues(l, XmNalignment, XmALIGNMENT_BEGINNING, NULL); 

	/* top, bottom, left, right */
	LxbSetConstraints (l,
										XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
										f1, NULL, parent, parent); 

	/* top, bottom, left, right */
	LxbSetOffsets (l, 5, 0, 5, 5);

	f2 = XtCreateManagedWidget ("f2", xmFrameWidgetClass, parent, fargs, i);

	XtSetArg(args[n], XmNnumColumns, 3);
	rc = XtCreateManagedWidget ("rc", xmRowColumnWidgetClass, f2, args, n+1);

	/* top, bottom, left, right */
	LxbSetConstraints (f2,
										XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
										l, NULL, parent, parent); 

	/* top, bottom, left, right */
	LxbSetOffsets (f2, 5, 0, 5, 5);

	/* Primitives */
	make_icon(rc, "Label", 	"Label", icon_callback, (XtPointer)xmLabelWidgetClass);
	make_icon(rc, "TextF", 	"Text\nField", icon_callback, (XtPointer)xmTextFieldWidgetClass);
	make_icon(rc, "Separ", 	"Separator", icon_callback, (XtPointer)xmSeparatorWidgetClass);
	make_icon(rc, "PushB", 	"Push\nButton", icon_callback, (XtPointer)xmPushButtonWidgetClass);
	make_icon(rc, "ToggB", 	"Toggle\nButton", icon_callback, (XtPointer)xmToggleButtonWidgetClass);
	make_icon(rc, "ArrowB",	"Arrow\nButton", icon_callback, (XtPointer)xmArrowButtonWidgetClass);
	make_icon(rc, "Scrollbar", "Scroll\nBar", icon_callback, (XtPointer)xmScrollBarWidgetClass);

	/* a special composite widget that has some hidden children */
	make_icon(rc, "Scale", "Scale", icon_callback, (XtPointer)NULL);

	/* 3rd grouping - complex */
	l = XtCreateManagedWidget ("l", xmLabelWidgetClass, parent, NULL, 0);
	XtVaSetValues(l, XtVaTypedArg, XmNlabelString, XmRString, "Complex", 7, NULL); 
	XtVaSetValues(l, XmNalignment, XmALIGNMENT_BEGINNING, NULL); 

	/* top, bottom, left, right */
	LxbSetConstraints (l,
										XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
										f2, NULL, parent, parent); 

	/* top, bottom, left, right */
	LxbSetOffsets (l, 5, 0, 5, 5);

	f1 = XtCreateManagedWidget ("f1", xmFrameWidgetClass, parent, fargs, i);

	XtSetArg(args[n], XmNnumColumns, 2);
	rc = XtCreateManagedWidget ("rc", xmRowColumnWidgetClass, f1, args, n+1);

	/* top, bottom, left, right */
	LxbSetConstraints (f1,
										XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
										l, NULL, parent, parent); 

	/* top, bottom, left, right */
	LxbSetOffsets (f1, 5, 0, 5, 5);

	make_icon(rc, "List", "List", icon_callback, (XtPointer)xmListWidgetClass);
	make_icon(rc, "Text", "Text",	icon_callback, (XtPointer)xmTextWidgetClass);

	/* a special composite widget that has some hidden children */
	make_icon(rc, "ScrllW", "Scrolled\nWindow", icon_callback, (XtPointer)NULL);

	/* scrolled stuff */
	make_icon(rc, "ScList", "Scrolled\nList", icon_callback, (XtPointer)NULL);
	make_icon(rc, "ScText", "Scrolled\nText", icon_callback, (XtPointer)NULL);

	/* fourth grouping - menubar stuff */
	l = XtCreateManagedWidget ("l", xmLabelWidgetClass, parent, NULL, 0);
	XtVaSetValues(l, XtVaTypedArg, XmNlabelString, XmRString, "Menus", 5, NULL); 
	XtVaSetValues(l, XmNalignment, XmALIGNMENT_BEGINNING, NULL); 

	/* top, bottom, left, right */
	LxbSetConstraints (l,
										XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
										f1, NULL, parent, parent); 

	/* top, bottom, left, right */
	LxbSetOffsets (l, 5, 0, 5, 5);

	f2 = XtCreateManagedWidget ("f2", xmFrameWidgetClass, parent, fargs, i);

	XtSetArg(args[n], XmNnumColumns, 1);
	rc = XtCreateManagedWidget ("rc", xmRowColumnWidgetClass, f2, args, n+1);

	/* top, bottom, left, right */
	LxbSetConstraints (f2,
										XmATTACH_WIDGET, XmATTACH_NONE, XmATTACH_FORM, XmATTACH_FORM,
										l, NULL, parent, parent); 

	/* top, bottom, left, right */
	LxbSetOffsets (f2, 5, 5, 5, 5);

	make_icon(rc, "MenuBar", "MenuBar", icon_callback, (XtPointer)NULL);
	make_icon(rc, "MenuCB",  "Cascade\nButton", icon_callback, (XtPointer)NULL);

}
/***************************************************************************************
 *
 * Function: icon_callback
 *
 *	Called when widget icon is pressed to create an instance of the Widget class.
 *
 **************************************************************************************/
static void
icon_callback(Widget icon, XtPointer client_data, XtPointer call_data)
{
	call_instantiate(selected_widget, icon, client_data);
}
/**************************************************
 *
 * Function: make_icon
 *
 *	Just makes the GUI for the icon button.
 *
 **************************************************/
static Widget
make_icon(Widget parent, char *name, String label, XtCallbackProc callback, XtPointer client_data)
{
	Widget icon;
	Arg args[10];
	int n;
	XmString labelstring;

	/* the application icon/button */
	if (label){
		labelstring = XmStringCreateLtoR (label, XmSTRING_DEFAULT_CHARSET);
		n=0;
		XtSetArg (args[n], XmNhighlightThickness, 0);n++;
		XtSetArg (args[n], XmNlabelString, labelstring);n++;
		XtSetArg (args[n], XmNalignment, XmALIGNMENT_CENTER);n++;
	};

	icon = XtCreateManagedWidget(name, xmPushButtonWidgetClass, parent, args, n);

	if (callback)
		XtAddCallback (icon, XmNactivateCallback, icon_callback, client_data);

	return (icon);
}
/**************************************************
 *
 *  Function: show_pallet
 *
 *  For play mode only.
 *
 **************************************************/
void
show_pallet()
{
	XtMapWidget(pallet_shell);
}
/**************************************************
 *
 *  Function: hide_resed_editor
 *
 *  For play mode only.
 *
 **************************************************/
void
hide_pallet()
{
  if (displayed == True)
    XtUnmapWidget(pallet_shell);
}                                                        
