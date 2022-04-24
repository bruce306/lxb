/**************************************************************
 * resed.h
 *************************************************************/

/* Defines for resource types */
#define CALLBACKS     0
#define RESOURCES     1
#define CONSTRAINTS   2

/* extern globals */
extern int resource_type;
extern char *resource_name;

extern Widget  name_list;
extern Widget  value_list;
extern Widget  value_text;
extern Widget  current_name;
extern Widget  current_class;

/* external functions */
void
build_resource_editor(Widget parent);
int
show_resource_editor(Widget w);
void
redisplay_resed_editor();
void
hide_resed_editor();

void
clear_resource_editor();

void
init_resource_editor(Widget w);
