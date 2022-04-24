
/*    File: tsizes.h    */

typedef struct _sstruct {
	String datatype;
	int size;
} SSTRUCT, *SSTRUCTLIST;

static SSTRUCT sstruct[] = {
	{"Boolean",	1},
	{"Cardinal",	4},
	{"Colormap",	8},
	{"Dimension",	2},
	{"KeySym",	8},
	{"Pixel",	8},
	{"Pixmap",	8},
	{"Position",	2},
	{"String",	8},
	{"Widget",	8},
	{"WidgetClass",	8},
	{"WidgetList",	8},
	{"Window",	8},
	{"XmFontList",	8},
	{"XmNavigationType",	1},
	{"XmString",	8},
	{"XmStringDirection",	1},
	{"XmTextPosition",	8},
	{"XtAccelerators",	8},
	{"XtCallbackList",	8},
	{"XtPointer",	8},
	{"XtTranslations",	8},
	{"int",	4},
	{"short",	2},
	{"unsigned char",	1},
	{"unsigned int",	4},
};

static int sstruct_count = 26;
