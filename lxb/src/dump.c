/***************************************************
 * File: dump.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "data.h"
#include "dump.h"

/**************************************************
 *
 *	Function: dump_callbacks
 *
 **************************************************/
void
dump_callbacks()
{
		/* TBD	*/

fprintf(stderr, "TO Be Done.\n");
}
/**************************************************
 *
 *	Function: dump_resource_names
 *
 **************************************************/
void
dump_resources(Widget w, Cardinal *no_resources, ALLLIST *resources)
{
	int i;
	ALLLIST rlist;

	printf("\n*-----------------------*\n");
	printf("*Widget Name: %s\n", widget_name(w));
	printf("*-----------------------*\n");
	printf("*Regular Resources: %d\n", *no_resources);
	printf("*-----------------------*\n");
	rlist = *resources;
	for (i=0; i<*no_resources; i++){

		printf("%s\t%s\t%d\n", rlist->name, rlist->type, rlist->size);
		rlist++;
	};
}
/**************************************************
 *
 *	Function: dump_constraint_names
 *
 **************************************************/
void
dump_constraint_names(Widget w, Cardinal *no_constraints, ALLLIST	*constraints)
{
	int i;
	ALLLIST clist;
	
	printf("\n*-----------------------*\n");
	printf("*Widget Name: %s\n", widget_name(w));
	printf("*Constraint Resources: %d\n", *no_constraints);
	printf("*-----------------------*\n");
	clist = *constraints;
	for (i=0; i<*no_constraints; i++){

		printf("%s\n", clist->name);
		clist++;
	};

	printf("*-----------------------*\n");

}
