/**************************************************
 * File: lbx.h - main file header - has global 
 *	data structures and variables defined here
 **************************************************/

/* used for working with resources, callbacks, constraints */
typedef struct _all{
	String 		name;
	String 		type;
  int    		size;
  XtPointer val;
} ALL, *ALLLIST;

/* callback list for each widget in the applications GUI */
typedef struct _call{
	char 	name[50]; 		/* Motif name, such as XmNactivateCallback */
	char 	function[50];	/* function name of callback (ie, "activate") */
	struct _call *next;
} CALL, *CALLLIST;

/* resource list for each widget in the applications GUI */
typedef struct _res{
	char 	name[50];
	char 	value[100];						/* font names are looooong */
	int		enumlist;
	char	reserved;												/* reserved */
	struct _res *next;
} RES, *RESLIST;

/* the widget heirarchy list */
typedef struct _wstruct{
	int						key;			/* to identify this one */
	char 					appname[50];
	Widget 					instance;		/* when built is widget */
	int						parent;			/* the "key" of the parent - parent for create function; 
												not always the real parent */
	char					class[50];			
	Boolean					global;
	Boolean					managed;
	char 					create_function[50];
	RES						*resptr;
	CALL					*callptr;
	struct _wstruct *next;
	struct _wstruct *last;
	char					reserved;		/* reserved */
	Widget					other_instance;	/* for "play mode */
	Boolean					fixed;			/* True means resources cannot be edited */
	Boolean					perm;			/* False means cannot be deleted by itself */
	Boolean					sel;			/* True means selectable via select handlers */
} WSTRUCT;

/* constants */
#define MAX_ARGS 100

/* return status */
#define NOTOK		0
#define OK			1
#define TBD			2		/* To Be Done */
#define NA			3		/* Not Available */

#define	FAIL		-1	
#define	SUCCESS	0

/* globals */
extern WSTRUCT 	*tree_ptr;
extern WSTRUCT 	*top_ptr;
extern Widget 	shell;
extern Widget 	appShell;
extern Widget 	selected_widget;
extern XtAppContext appcontext;

extern char  		*savefile_name;
extern char			*application_name;

/* global constants set at startup */
extern char 		*version;
extern int 			verbose;
