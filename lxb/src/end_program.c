/**************************************************
 * File: end_program.c
 *
 *    Copyright (C) 1995  Bruce Parkin 
 *
 **************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "end_program.h"

/**************************************************
 * Funcion: end_program
 **************************************************/
int 
end_program(int flag)
{
	exit(flag);
}
