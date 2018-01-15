/**************************************************
 *
 * File: save.c
 *	
 *	Copyright (C) 1997  Bruce Parkin
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>   
#include <unistd.h>      
#include <errno.h>      
#include <Xm/Xm.h>      

#include "lxb.h"
#include "TopShell.h"
#include "top.h"
#include "save.h"

/* local prototypes */
static int
write_resources(WSTRUCT *wptr, int file);
static int
write_callbacks(WSTRUCT *wptr, int file);

/**************************************************
 *
 * Function: save_gui
 *
 **************************************************/
int
save_gui(Boolean overwrite)
{
	int status;
	int	file;   
	WSTRUCT	*wptr;
	char cmd[100];
	char buf[124];
	char *appname;
	int n;
	Arg args[5];

	char *name = savefile_name;

	output_message("\nSaving application in file: %s", savefile_name);

	/* check about overwriting the old file */
	file = open(name, O_WRONLY|O_CREAT|O_EXCL, 0644);

	if (errno == EEXIST){
		
		if (!overwrite) {

			return (EEXIST);
		};

		strcpy(cmd, "mv ");
		strcat(cmd, name);
		strcat(cmd, " ");
		strcat(cmd, name);
		strcat(cmd, ".bak");

		system(cmd);

		file = open(name, O_WRONLY|O_CREAT, 0644);
		if (file == -1){
			fprintf(stderr, "File: %s\n", name);
			perror("Problems opening GUI save file");
			return (NOTOK);
		};

	} else if (file == -1){

		fprintf(stderr, "File: %s\n", name);
		perror("Problems opening GUI save file");
		return (NOTOK);
	};

	status = write(file, version, strlen(version) +1);
	if (status == -1){
		perror("Problems writing GUI save file");	
		return (NOTOK);														
	};																				

	/* write some more lines for future used */
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	if (status == -1){
		perror("Problems writing GUI save file");	
		return (NOTOK);														
	};																				

	/* do the entire list */
	wptr = tree_ptr;
	while (wptr != NULL){

		if (wptr == top_ptr){

			/* get and set the real application name */
/*
			appname = get_appname();
			strcpy(top_ptr->appname, appname);
			XtFree(appname);
*/
			strcpy(top_ptr->appname, application_name);
		};

		status = write(file, (char *)wptr, sizeof(WSTRUCT));
		if (status == -1){
			perror("Problems writing GUI save file");	
			return (NOTOK);														
		};																				

		/* record the shell widget resources at the last */
		if (wptr == top_ptr){
			record_last_appshell_resources();
		};

		/* save the resources for all widgets */
		if (wptr->resptr != NULL){
			status = write_resources(wptr, file);
			if (status == 0){
				return (NOTOK);
			};
		};

		/* save the callbacks for all widgets */
		if (wptr->callptr != NULL){
			status = write_callbacks(wptr, file);
			if (status == 0){
				return (NOTOK);
			};
		};

		wptr = wptr->next;
	};

	close(file);

  /* title in main window bar */
  strcpy(buf, "LXB - Application Save File: ");
  strcat(buf, savefile_name);

  n=0;
  XtSetArg(args[n], XmNtitle, buf);n++;          
  XtSetValues(shell, args, n);    

	return (OK);
}
/**************************************************
 *
 * Function: write_resources
 *
 **************************************************/
static int
write_resources(WSTRUCT *wptr, int file) 
{
	RES     *rptr;       
	int     status;    

	if (verbose >4)
		printf("writing widget resources: %s\n", wptr->appname);

	rptr = wptr->resptr;
	while (rptr != NULL){

		status = write(file, (char *)rptr, sizeof(RES));
		if (status == -1){
			perror("problems with writing resources to GUI save file");
			return (0);
		};

		if (verbose >6)
			printf("resources: %s  value: %s\n", rptr->name, rptr->value);

		rptr=rptr->next;
	};     

	return (1);
}
/**************************************************
 *
 * Function: write_callbacks
 *
 **************************************************/
static int
write_callbacks(WSTRUCT *wptr, int file) 
{
	CALL 	*cptr;       
	int  	status = 1;    

	if (verbose >4)
		printf("writing widget callbacks: %s\n", wptr->appname);

	cptr = wptr->callptr;
	while (cptr != NULL){

		status = write(file, (char *)cptr, sizeof(CALL));
		if (status == -1){
			perror("problems with writing resources to GUI save file");
			status = 0;
			break;
		};

		if (verbose >4)
			printf("name: %s  function: %s\n", cptr->name, cptr->function);

		cptr=cptr->next;
	};     

	return (status);
}
/**************************************************
 *
 * Function: save_tmp_gui
 *
 **************************************************/
void
save_tmp_gui()
{
	int status;
	int	file;   
	WSTRUCT	*wptr;
	char cmd[100];
	char buf[124];
	char *appname;
	int n;
	Arg args[5];

	char *name = "#lxbSave.lxb#";
	output_message("\nWriting lxb tmp save file: %s", name);

	file = open(name, O_WRONLY|O_CREAT, 0644);
	if (file == -1){
		fprintf(stderr, "File: %s\n", name);
		perror("Problems opening GUI save file");
		return;
	};

	status = write(file, version, strlen(version) +1);
	if (status == -1){
		perror("Problems writing GUI save file");	
		return;
	};																				

	/* write some more lines for future used */
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	status = write(file, "RESERVED", 9);
	if (status == -1){
		perror("Problems writing GUI save file");	
		return;
	};																				

	/* do the entire list */
	wptr = tree_ptr;
	while (wptr != NULL){

		if (wptr == top_ptr){

			/* get and set the real application name */
			strcpy(top_ptr->appname, application_name);
		};

		status = write(file, (char *)wptr, sizeof(WSTRUCT));
		if (status == -1){
			perror("Problems writing GUI save file");	
			return;
		};																				

		/* record the shell widget resources at the last */
		if (wptr == top_ptr){
			record_last_appshell_resources();
		};

		/* save the resources for all widgets */
		if (wptr->resptr != NULL){
			status = write_resources(wptr, file);
			if (status == 0){
				return;
			};
		};

		/* save the callbacks for all widgets */
		if (wptr->callptr != NULL){
			status = write_callbacks(wptr, file);
			if (status == 0){
				return;
			};
		};

		wptr = wptr->next;
	};

	close(file);
}
