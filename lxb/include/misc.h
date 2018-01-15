/**************************************************
 * File: misc.h
 **************************************************/

char *
get_datatype(char *resource_name, int *enumlist);

int
get_datatype_index(char *datatype);

char *
get_enum_type(int *enumlist, int *number, char *buf);
                                                         
int
get_enum_number(int *enumlist, char *enum_name);                                                                         
