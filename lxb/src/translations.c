/**************************************************
 * File: translations.c 
 *
 *    Copyright (C) 1995-2002  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <Xm/Xm.h>

#include "translations.h"
#include "lxb.h"

/* translation prototype */
static void
noop(Widget w, XEvent *event, String *params, Cardinal *num_params);

/*  Action */
static XtActionsRec actions[] = {
  {"noop", noop},
};

/* Translation */
static char translations[] =
  "<Key>: noop()";
                       
/**************************************************
 *
 *	Function:	remove_translations
 *
 *	Does not work.
 *
 **************************************************/
void
remove_translations(Widget w)
{
	Arg args[2];
	XtTranslations noop_translations;

	noop_translations = XtParseTranslationTable(translations);

	XtSetArg(args[0], XmNtranslations, noop_translations);
	XtSetValues(w, args, 1);

}
/**************************************************
 *
 *	Function:	add_actions
 *
 **************************************************/
void
add_noop_action()
{
	XtAppAddActions(appcontext, actions, XtNumber(actions));
}
/**************************************************
 *
 *  Function: noop - action which is a no-op
 *
 *	This is the only method I could get to work, in
 *	conjunction with the line in the resource file,
 *	to remove all translations. I think it's 'cause
 *	when you create a ToplevelShell you cannot replace
 *	via hardcode all translations??????
 *
 **************************************************/
static void
noop(Widget w, XEvent *event, String *params, Cardinal *num_params)
{
}                         
