/**************************************************
* File: tst.c - application source file
*
*    This file is generated by the program lxb.
*
**************************************************/

/* include files */
#include <stdio.h>

#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/Frame.h>
#include <Xm/DrawingA.h>
#include "Tree.h"
#include "Panner.h"
#include "Porthole.h"

#include "tst_util.h"
#include "tst.h"
#include "wtree.h"

/**************************************************
* Function: main
**************************************************/
int 
main(int argc, char *argv[])
{
	Widget tst;

	/* Initialize toolkit and parse command line options. */
	tst = XtInitialize(NULL, "Tst", NULL, 0, &argc, argv);

	build_wtree_area(tst);

	XtRealizeWidget(tst);
	XtMainLoop();
}
