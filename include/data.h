/**************************************************
 * File: data.h
 **************************************************/

int
change_widget_name(Widget w, char *newname);

int
get_counter();

Widget
adjust_parent(Widget act_w);

Widget
get_parent_widget(int key);

int 
get_parent_key(Widget w);

Widget
widget_instance(char *name);

char *
widget_name(Widget w);

WSTRUCT *
widget_ptr(Widget w);

WSTRUCT *
get_wstruct(void);

char *
get_widget_classname(Widget w);

char *
choose_default_name(WidgetClass wclass);

WidgetClass
get_widgetclass(char *class);

char *
widget_classname(Widget w);
