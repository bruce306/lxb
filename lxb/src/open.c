/**************************************************
 * File: open.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>   
#include <unistd.h>      
#include <Xm/Xm.h>      

#include "lxb.h"
#include "open.h"

/* prototypes */
static int
read_resource_list(WSTRUCT *wptr, int file);
static int
read_callback_list(WSTRUCT *wptr, int file);

/**************************************************
 *
 * Function: open_gui
 *
 *	Just read in the list of widgets and resources.
 *
 **************************************************/
int
open_gui()
{
	int   	status;
	int			file;   
	WSTRUCT	*wptr;
	WSTRUCT	*xptr;
	char		*name;
	char 		buf[100];
	Boolean	tail;
	char 		*ptr;
	char	this_version[50];
	Boolean old_version;

	old_version = True;

	/* save filename */
	name = savefile_name;

	if (verbose > 4)
		printf("\nAttempt to open application save file: %s\n", name);

	file = open(name, O_RDONLY, 0444);
	if (file == -1){
		perror("Attempt to open GUI save file failed");
		return (0);
	};

	if (verbose >4)
		printf("\tReading save file: %s\n", name);

	/* get version */
	ptr = this_version;
	status = read(file, ptr, 1);
	while (status != -1){

		if (*ptr == '\0'){
			break;
		};
		ptr++;

		status = read(file, ptr, 1);
	}; 

	if (status == -1){
		perror("Attempt to read GUI save file failed");	
		close(file);	
		return (0);	
	}; 

	if ( (strcmp(version, this_version) != 0) ){
		fprintf(stderr, "WARNING: may not be able to accurately read %s\n", name);
		fprintf(stderr, "Different versions of lxb save file (%s) and lxb (%s)\n", this_version, version);
	};

	/* if new save file then read past reserved lines */
	if (atof(this_version) >= 0.3){

		/* 7 "RESERVED" */
		status = read(file, buf, 63);
		old_version = False;
	};

	tail = True;

	xptr = (WSTRUCT *)&wptr;

	/* read nodes from file */
	while (xptr != NULL){

		/* allocate node */
		wptr = (WSTRUCT *)XtMalloc(sizeof(WSTRUCT));
		memset(wptr, 0, sizeof(WSTRUCT));

		/* read node from file */
		status = read(file, (char *)wptr, sizeof(WSTRUCT));

		/* address is old and bad; only used to check for NULL: means list end */
		xptr = wptr->next;

		/*  NOTE: TBD - free all memory in these lists!     */
		if (status == -1){
			perror("Attempt to read GUI save file failed");	
			close(file);	
			tree_ptr = NULL;
			top_ptr = NULL;	
			return (0);	
		}; 

		if (verbose >4){
			printf("Widget:            %s\n", wptr->appname);
			printf("    class:           %s\n", wptr->class);
			printf("    key:             %d\n", wptr->key);
			printf("    parent:          %d\n", wptr->parent);
			printf("    create function: %s\n", wptr->create_function);
			if (wptr->managed == True)
				printf("    managed:         True\n"); 
			else
				printf("    managed:         False\n"); 
		};

		/* see if original widget had any resources changed */
		if (wptr->resptr != NULL){

			/* get resource linked list */
			status = read_resource_list(wptr, file);

			/*  NOTE: TBD - free all memory in these lists!     */
			if (status == 0){	
				perror("Attempt to read GUI save file resources failed");
				close(file);																						
				tree_ptr = NULL;																			
				top_ptr = NULL;																			
				return (0);																				
			};									

		};              

		/* see if original widget had any callbacks assigned */
		if (wptr->callptr != NULL){

			/* get resource linked list */
			status = read_callback_list(wptr, file);

			/*  NOTE: TBD - free all memory in these lists!     */
			if (status == 0){	
				perror("Attempt to read GUI save file callbacks failed");
				close(file);																						
				tree_ptr = NULL;																			
				top_ptr = NULL;																			
				return (0);																				
			};									

		};              
		/* check for tail of the list; and relink - old addresses not valid */
		if (tail == True){
			
			/* tail of the list */
			tree_ptr = wptr;
			top_ptr = wptr;
			tail = False;
			tree_ptr->next = NULL;
			top_ptr->last = NULL;
		}else {
			
			top_ptr->next = wptr;
			wptr->last  = top_ptr;
			wptr->next = NULL;
			top_ptr = wptr;
		};

	};

	/* set the application name */
	XtFree(application_name);
	application_name = XtNewString(top_ptr->appname);

	/* change the name of the shell widget to default */
	strcpy(top_ptr->appname, "topLevelShell");

	close(file);
	return (1);
}
/**************************************************
 *
 * Function: read_resource_list
 *
 **************************************************/
static int
read_resource_list(WSTRUCT *wptr, int file)
{
  RES     *rptr;
  RES     *old_rptr;
  int     status;
	Boolean 	first;

	/* set to anything non-NULL */

	rptr = wptr->resptr;

	first = True;

	if (verbose >4)
		printf("    Resources:\n");

  while (rptr != NULL) {

    rptr = (RES *)XtMalloc(sizeof(RES));            
		memset(rptr, 0, sizeof(RES));

		if (first == True){
			wptr->resptr = rptr;
			first = False;
		} else {

			old_rptr->next = rptr;
		};

		old_rptr = rptr;

		/* read resource struct from file */
		status = read(file, (char *)rptr, sizeof(RES));

    if (status == -1){
      return (0);
    };

		if (verbose >4){
			printf("        name:          %s", rptr->name);
			printf("        value:         %s\n", rptr->value);
		};

		/* use old address for check of end */
		rptr = rptr->next;
  };

	if (verbose >4)
		printf("\n");

	old_rptr->next = NULL;

  return (1);
}                       
/**************************************************
 *
 * Function: read_callback_list
 *
 **************************************************/
static int
read_callback_list(WSTRUCT *wptr, int file)
{
  CALL     	*cptr;
  CALL     	*old_cptr;
  int     	status;
	Boolean 	first;

	/* set to anything non-NULL */
	cptr = wptr->callptr;

	first = True;

	if (verbose >4)
		printf("\tCallbacks:\n");

  while (cptr != NULL) {

    cptr = (CALL *)XtMalloc(sizeof(CALL));            
		memset(cptr, 0, sizeof(CALL));

		if (first == True){
			wptr->callptr = cptr;
			first = False;
		} else {

			old_cptr->next = cptr;
		};

		old_cptr = cptr;

    status = read(file, (char *)cptr, sizeof(CALL));

    if (status == -1){
      return (0);
    };

		if (verbose >4){
			printf("        name:          %s", cptr->name);
			printf("        function:      %s\n", cptr->function);
		};

		/* use old address for check of end */
		cptr = cptr->next;
  };

	if (verbose >4)
		printf("\n");

	old_cptr->next = NULL;

  return (1);
}                       
