/**************************************************
 * File: color.c - functions for color 
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

/* include files */
#include <stdio.h>
#include <stdlib.h>
#include <Xm/Xm.h>
#include "lxb.h"
#include "color.h"
#include "top.h"

#define color_dbase "/usr/lib/X11/rgb.txt"
#define color_dbasename "rgb.txt"

static CNAMELIST colors;
static int number_colors = 0;

static FILE *
open_colordbase();

/**************************************************
 *
 *	Function: open_colordbase
 *
 **************************************************/
static FILE *
open_colordbase()
{
	FILE *file;
	char *ptr; 

	/* get the color database filename */
	ptr = XtResolvePathname(XtDisplay(shell), NULL, "rgb.txt", NULL, NULL, NULL, 0, NULL);

	file = NULL;

	file = fopen(ptr, "r");
	if (file == NULL){
		perror("Problems opening color database file rgb.txt");
	};

	return (file);
}
/**************************************************
 *
 *	Fuction: get_pixel_color
 *
 **************************************************/
char *
get_pixel_color(Pixel pixel)
{
	char line[100], save_line[100];
	char name0[35], name1[35], name2[35];
	int	num;
	XColor xcolor;
	Colormap colormap;
	FILE *file;
	char *eof;
	unsigned short r, rr, g, gg, b, bb, dr, dg, db, or, og, ob;
	unsigned short oldsum;
	int i;
	char *ptr; 

	name0[0] = '\0';
	colormap = XDefaultColormap( XtDisplay(shell), XDefaultScreen(XtDisplay(shell)) );
	xcolor.pixel = pixel;
	XQueryColor(XtDisplay(shell), colormap, &xcolor);
	xcolor.red = xcolor.red>>8; xcolor.green = xcolor.green>>8; xcolor.blue = xcolor.blue>>8;

	/* get the color database filename */
	file = open_colordbase();
	if (file == NULL){
		fprintf(stderr, "(get_pixel_color): Failed to open color database file rgb.txt\n");
		return (NULL);
	};

	oldsum = 766;
	or = 20; og = 20; ob = 20;
	dr = 0; dg = 0; db = 0;
	rr = 0; gg = 0; bb = 0;

	while ((eof = fgets(line, 100, file)) != NULL){

		/* fgets puts \n at end of each line, not \0 */
		for (i=0;i<100;i++){
			if (line[i] == '\n'){
				line[i] = '\0';
				break;
			};
		};

		sscanf(eof, "%hu%hu%hu", &r, &g, &b);

		dr = abs(r-xcolor.red);
		dg = abs(g-xcolor.green);
		db = abs(b-xcolor.blue);

		save_line[0] = 0;
		if ( (dr <= or) && (dg <= og) && (db <= ob) ){
			or = dr;
			og = dg;
			ob = db;
			memcpy(save_line, line, strlen(line) + 1);

			num = sscanf(save_line, "%*u%*u%*u%s%s%s", name0, name1, name2);

			if ( (num == 3) || (num == 2) ){

			} else if (num == 1) {

				break;
			};

		};
	};

	fclose(file);

	ptr = XtNewString(name0);
	return (ptr);
}
/**************************************************
 *
 *	Fuction: get_pixel
 *
 **************************************************/
Pixel
get_pixel(char *resource_value)
{
	Colormap colormap;
	Boolean status;
	XColor exact, color;
	Widget w;

/*
	colormap = XDefaultColormap( XtDisplay(shell), XDefaultScreen(XtDisplay(shell)) );

	status = XAllocNamedColor(XtDisplay(shell), colormap, resource_value, &color, &exact);

	if (status == 0){
		fprintf(stderr, "Unknown color: %s", resource_value);
		color.pixel = BlackPixel(XtDisplay(shell), DefaultScreen(XtDisplay(shell)) );
	};
*/

	w = shell;
	colormap = DefaultColormapOfScreen( DefaultScreenOfDisplay(XtDisplay(w)) );

	status = XAllocNamedColor( XtDisplay(w), colormap, resource_value, &color, &exact);

	if (status == 0){
		output_message("\nWarning: Could not allocate color: %s", resource_value);
		XBell(XtDisplay(shell), 100);
		color.pixel = BlackPixelOfScreen( DefaultScreenOfDisplay(XtDisplay(w)) );
	};

	return (color.pixel);
}
/**************************************************
 *
 *	Fuction: get_colornames
 *
 **************************************************/
int
get_colornames(CNAMELIST *cnamelist, int *number)
{
	char name0[35], name1[35], name2[35];
	char line[100];
	int	num, i;
	FILE *file;
	char *eof;
	CNAMELIST clist;

	if (number_colors != 0){

		/* already done the work */
		*number = number_colors;
		*cnamelist =	colors;
		return (OK);
	};

	file = open_colordbase();
	if (file == NULL){
		fprintf(stderr, "(get_colornames): Failed to open color database file rgb.txt\n");
		return (NOTOK);
	};

	/* count the number of legal names in the rgb.txt file */
	while ((eof = fgets(line, 100, file)) != NULL){
		for (i=0;i<100;i++){
			if (line[i] == '\n'){
				line[i] = '\0';
				break;
			};
		};
		num = sscanf(line, "%*u%*u%*u%s%s%s", name0, name1, name2);
		if ( (num == 3) || (num == 2) ){
		} else if (num == 1) {
			number_colors++;
		};
	};
	
	*number = number_colors;

	fclose(file);

	colors = (CNAMELIST)XtCalloc(number_colors, sizeof(CNAME));
	*cnamelist = colors;

	file = open_colordbase();
	if (file == NULL){
		fprintf(stderr, "(get_colornames): Failed to open color database file rgb.txt\n");
		return (NOTOK);
	};

	clist = colors;

	/* now, get the names */
	while ((eof = fgets(line, 100, file)) != NULL){

		/* fgets puts \n at end of each line, not \0 */
		for (i=0;i<100;i++){
			if (line[i] == '\n'){
				line[i] = '\0';
				break;
			};
		};

		num = sscanf(line, "%*u%*u%*u%s%s%s", name0, name1, name2);

		if ( (num == 3) || (num == 2) ){

		} else if (num == 1) {

			clist->colorname = XtNewString(name0);
			clist++;
		};
	};

	fclose(file);

	return (OK);

}
