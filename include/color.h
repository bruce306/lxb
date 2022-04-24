/**************************************************
 * File: Color.h
 **************************************************/

/* data structure for colornames */
typedef struct _cname{
  char *colorname;
} CNAME, *CNAMELIST;


/* external functiobs */
char *
get_pixel_color(Pixel pixel);

Pixel
get_pixel(char *resource_value);

int
get_colornames(CNAMELIST *cnamelist, int *number);

