/**************************************************************************
*
* File: TextObject.h - utility functions used in the creation of text objects.
*
**************************************************************************/

/* user may install this function - called when OK button is pressed */
typedef Boolean (*UserProc)(
	Widget w,		/* text widget id */
	char *txt		/* text string in text widget */
);

void
set_textstring(Widget w, char *txt);

Widget
new_text_object(Widget parent, Position x, Position y, char *label, 
	int label_width, int columns, UserProc proc, Widget *text_widget);
