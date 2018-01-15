/**************************************************
 * File: fonts.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "fonts.h"
#include "data.h"


/**************************************************
 *
 *	Function:	get_fontlist
 *
 *		I THINK returning a value like this for the
 *		fontlist is OK as a global value is created internal
 *		to X...
 *
 **************************************************/
XmFontList
get_fontlist(Widget w, char* fontname)
{	
	XFontStruct *font;
	XmFontList fontlist;

	/* check for the default font first */
	if (!strcmp(fontname, "Default")){

		fontlist = get_default_font();
		
	} else {
	
		font = XLoadQueryFont(XtDisplay(w), fontname); 
		if (font == NULL){

			fprintf(stderr, "\tCould not load font: %s\n\n", fontname);
			fprintf(stderr, "\tUsing this system's default font instead.\n\n");

			fontlist = get_default_font();
		} else {

			fontlist = XmFontListCreate(font, XmSTRING_DEFAULT_CHARSET);
		};

	};

	return (fontlist);
}
/**************************************************
 *
 *	Function: get_fontname - this will get the name of
 *		the font of the XmNfontList resource for the 
 *		input widget. 
 *
 *		It goes thru the stored resources for the instantiated
 *		widget (the linked list of). If it does not find a
 *		XmNfontList resource/value it returns NULL, which
 *		means it was not changed from the Default used by
 *		this system.
 *
 **************************************************/
char *
get_font_name(Widget w)
{
	WSTRUCT 	*wptr;
  RES       *rptr; 

	char *ptr = NULL;

	if (w == NULL){
		printf("Cannot get fontname: no selected widget\n");
		return (ptr);
	};

	wptr = widget_ptr(w);

	if (wptr->resptr != NULL){

		rptr = wptr->resptr;
		while (rptr != NULL){

			if (!strcmp(rptr->name, "fontList")) {
				ptr = rptr->value;
			};
			rptr = rptr->next;
		};
	};                          

	/* not changed; using default */
	if (ptr == NULL){
		ptr = "Default";
	};

	return (ptr);
}
/**************************************************
 *
 *	Function:	get_default_font
 *
 *	Get the default fontlist off the Shell widget.
 *
 **************************************************/
XmFontList
get_default_font()
{	
	XmFontList fontlist;
	Arg args[2];

	XtSetArg(args[0], XmNdefaultFontList, &fontlist);
	XtGetValues(appShell, args, 1);
	return (fontlist);
}
