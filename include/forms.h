/**************************************************
 * File: Forms.h
 **************************************************/

/* constants, externs.  etc */

#define LxbNoPosition   -99999
#define LxbNoOffset     -99999

Widget 
LxbMakeForm (Widget parent, String name);

void 
LxbSetPositions (Widget w, int top, int bottom, int left, int right);

void 
LxbSetOffsets (Widget w, int top, int bottom, int left, int right);

void 
LxbSetConstraints (Widget w, int top, int bottom, int left, int right,
			Widget topw, Widget botw, Widget lefw, Widget rigw);

