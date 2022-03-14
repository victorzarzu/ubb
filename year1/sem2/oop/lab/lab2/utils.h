#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "domain.h"

typedef int(*CompareFunction)(PRODUS* o1, PRODUS* o2);

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

/**
* Function that sorts an array of products
* 
* params: Array - a pointer to a product (an array of products)
*         cmpF - a pointer to a compare function (const void*, const void*)
*         length - the number of elements in Array
* 
* @return: -
*/
void BubbleSort(PPRODUS Array, CompareFunction cmpF, int length);

/**
* Function that sorts an array of products
*
* params: Array - a pointer to a product (an array of products)
*         cmpF - a pointer to a compare function (const void*, const void*)
*         length - the number of elements in Array
*
* @return: -
*/
void SelectionSort(PPRODUS Array, CompareFunction cmpF, int length);

#endif 
