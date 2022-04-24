/****************************************************
* File: lsf.c - list fonts this X server knows about
****************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>

/**************************************************
* Function: main
**************************************************/
int 
main(int argc, char *argv[])
{
	Arg args[100];
	char **ptr;
	int actual;
	int i;
	Widget w;

	w = XtInitialize(NULL, "", NULL, 0, &argc, argv);

	ptr = XListFonts(XtDisplay(w), "*", 1000, &actual);

	for (i=0; i<actual; i++){
		printf("%s\n", *ptr);
		ptr++;
	};
}
