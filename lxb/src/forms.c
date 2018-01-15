/**************************************************
 * File: forms.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <Xm/Form.h>
#include "lxb.h"
#include "forms.h"

/**************************************************
 *
 *	Function: LxbMakeForm
 *
 *	returns the ptr to the widget in the list
 *
 **************************************************/
Widget 
LxbMakeForm (Widget parent, String name)
{
	Widget w;
  w = XtCreateManagedWidget (name, xmFormWidgetClass, parent, NULL, 0);
	return (w);
}
/**************************************************
 *
 *	Function: LxbSetPositions
 *
 *	of Form children
 *
 **************************************************/
void 
LxbSetPositions (Widget w, int top, int bottom, int left, int right)
{
	Arg args[10];
	int i;

	i=0;

  if (top != LxbNoPosition)
    {
			XtSetArg(args[i], XmNtopAttachment, XmATTACH_POSITION);i++;
			XtSetArg(args[i], XmNtopAttachment, top);i++;
    }
  if (bottom != LxbNoPosition)
    {
      XtSetArg(args[i], XmNbottomAttachment, XmATTACH_POSITION);i++;
      XtSetArg(args[i], XmNbottomPosition, bottom);i++;
    }
  if (left != LxbNoPosition)
    {
      XtSetArg(args[i], XmNleftAttachment, XmATTACH_POSITION);i++;
      XtSetArg(args[i], XmNleftPosition, left);i++;
    }
  if (right != LxbNoPosition)
    {
      XtSetArg(args[i], XmNrightAttachment, XmATTACH_POSITION);i++;
      XtSetArg(args[i], XmNrightPosition, right);i++;
    }

  XtSetValues(w, args, i);
  return;
}
/**************************************************
 *
 *	Function: LxbSetOffsets
 *
 *	of Form children
 *
 **************************************************/
void 
LxbSetOffsets (Widget w, int top, int bottom, int left, int right)
{
	Arg args[5];
	int i;

	i=0;

  if (top != LxbNoOffset)
    XtSetArg(args[i], XmNtopOffset, (XtArgVal)top);i++;
  if (bottom != LxbNoOffset)
    XtSetArg(args[i], XmNbottomOffset, (XtArgVal)bottom);i++;
  if (left != LxbNoOffset)
    XtSetArg(args[i], XmNleftOffset, (XtArgVal)left);i++;
  if (right != LxbNoOffset)
    XtSetArg(args[i], XmNrightOffset, (XtArgVal)right);i++;
  
  XtSetValues(w, args, i);
  return;
}
/**************************************************
 *
 *	Function: LxbSetConstraints
 *
 *	of Form children
 *
 **************************************************/
void 
LxbSetConstraints (Widget w, int top, int bottom, int left, int right,
			Widget topw, Widget botw, Widget lefw, Widget rigw)
{
	Arg args[10];
	int i;

	i=0;

  if (top != XmATTACH_NONE)
    {
      XtSetArg(args[i], XmNtopAttachment, top);i++;
      if (topw)
        XtSetArg(args[i], XmNtopWidget, topw);i++;
    }
  
  if (bottom != XmATTACH_NONE)
    {
      XtSetArg(args[i], XmNbottomAttachment, bottom);i++;
      if (botw)
        XtSetArg(args[i], XmNbottomWidget, botw);i++;
    }

  if (left != XmATTACH_NONE)
    {
      XtSetArg(args[i], XmNleftAttachment, left);i++;
      if (lefw)
        XtSetArg(args[i], XmNleftWidget, lefw);i++;
    }

  if (right != XmATTACH_NONE)
    {
      XtSetArg(args[i], XmNrightAttachment, right);i++;
      if (rigw)
        XtSetArg(args[i], XmNrightWidget, rigw);i++;
    }
  
  XtSetValues(w, args, i);
  return;
}

