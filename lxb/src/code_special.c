/**************************************************
*
* File: code_special.c
*
*    Copyright (C) 1997  Bruce Parkin 
*
**************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "code.h"
#include "code_special.h"

static int no_xmstrings = 0;
static Boolean fontlist_created = False;

/**************************************************
 *
 * Function: code_special_fontlist
 *
 **************************************************/
void
code_special_fontlist(FILE *file, char *shellname, RES *rptr, int n)
{
	fontlist_created = True;

	fprintf(file, "\tfontlist = get_fontlist(%s, \"%s\");\n", shellname, rptr->value);
	fprintf(file, "\tXtSetArg(args[%d], XmN%s, fontlist);\n", n, rptr->name);
}
/**************************************************
 *
 * Function: code_special_widget
 *
 **************************************************/
void
code_special_widget(FILE *file, RES *rptr, int n)
{
	/* can be treated as a normal resource */
	fprintf(file, "\tXtSetArg(args[%d], XmN%s, %s);\n", n, rptr->name, rptr->value);   
}
/**************************************************
 *
 * Function: code_special_colorname
 *
 **************************************************/
void
code_special_colorname(FILE *file, char *widget_name, RES *rptr, int n)
{
	fprintf(file, "\tXtSetArg(args[%d], XmN%s, get_pixel(%s, \"%s\"));\n",
					n, rptr->name, widget_name, rptr->value);    
}
/**************************************************
 *
 * Function: code_special_xmstring
 *
 **************************************************/
void
code_special_xmstring(FILE *file, RES *rptr, int n)
{

	fprintf(file, "\txmstrings[%d] = XmStringCreateSimple(\"%s\");\n", 
					no_xmstrings, rptr->value);
	fprintf(file, "\tXtSetArg(args[%d], XmN%s, xmstrings[%d]);\n", 
					n, rptr->name, no_xmstrings);

	no_xmstrings++;

}
/**************************************************
 *
 * Function: code_free_special
 *
 **************************************************/
void
code_special_free(FILE *file)
{
	int i;
	Boolean done = False;

	/* code for freeing XmStrings */
	for (i=0; i<no_xmstrings; i++){

		done = True;
		fprintf(file, "\tXmStringFree(xmstrings[%d]);\n", i);

		/* reset local vars */
		no_xmstrings = 0;
	};

	if (done)
		fprintf(file, "\n");

	done = False;

	/* code for freeing the fontlist */
	if (fontlist_created){

		done = True;
		fprintf(file, "\tXmFontListFree(fontlist);\n");

		/* reset local vars */
		fontlist_created = False;
	};

	if (done)
		fprintf(file, "\n");

}
