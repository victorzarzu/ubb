#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
* Function that verifies if a string is an integer
* 
* @params: text - a pointer to a char
* 
* @return: 1 - if text is an integer
*          0 - false if not
*         -1 - if the pointer is NULL
*/
int isInteger(char* text);

/**
* Function that verifies if a string is a double
*
* @params: text - a pointer to a char
*
* @return: 1 - if text is an integer
*          0 - false if not
*         -1 - if the pointer is NULL
*/
int isDouble(char* text);

#endif 
