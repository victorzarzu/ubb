#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "domain.h"
#include "infrastructure.h"

typedef int(*CompareFunction)(TRANZACTIE* t1, TRANZACTIE* t2);
typedef int (*AscendingMode)(int);
typedef int (*FilterFunction)(TRANZACTIE*);

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
* Function that sorts an array of transactions
*
* @params: Array - a pointer to a list
*         cmpF - a pointer to a compare function (const void*, const void*)
*         ascF - a pointer to an ascending function
*
* @return: -
*/
void BubbleSort(PMY_LIST Array, CompareFunction cmpF, AscendingMode ascF);

/**
* Function that sorts an array of transactions
*
* @params: Array - a pointer to a list
*         cmpF - a pointer to a compare function (const void*, const void*)
*         ascF - a pointer to an ascending function
*
* @return: -
*/
void SelectionSort(PMY_LIST Array, CompareFunction cmpF, AscendingMode ascF);

/**
* Function that compares the Zi field of 2 transactions
* 
* @params: t1 - a pointer to a transaction
*          t2 - a pointer to a transaction
*
*
* @return: 1 - if t1.Zi < t2.Zi
*          0 - otherwise
*/
int compareZi(PTRANZACTIE t1, PTRANZACTIE t2);

/**
* Function that compares the Suma field of 2 transactions
*
* @params: t1 - a pointer to a transaction
*          t2 - a pointer to a transaction
*
*
* @return: 1 - if t1.Suma < t2.Suma
*          0 - otherwise
*/
int compareSuma(PTRANZACTIE t1, PTRANZACTIE t2);

/**
* Function that returns an asceding mode of true
*
* @params: result - an integer
*
*
* @return: result - integer
*/
int ascendingMode(int result);

/**
* Function that returns an descending mode of true
*
* @params: result - an integer
*
*
* @return: !result - integer
*/
int descendingMode(int result);

/**
* Function that checks if the Tip field of a transaction is the given one
*
* @params: t - a pointer to a transaction
*          Tip - an integer
*
*
* @return: 1 - if t.Tip == Tip
*          0 - otherwise
*/
int isType(PTRANZACTIE t, int Tip);

/**
* Function that checks if the Day field of a transaction is the given one
*
* @params: t - a pointer to a transaction
*          Zi - an integer
*
*
* @return: 1 - if t.Zi == Zi
*          0 - otherwise
*/
int isDay(PTRANZACTIE t, int Zi);

/**
* Function that checks if the Suma field of a transaction is smaller than the given one
*
* @params: t - a pointer to a transaction
*          Suma - a double
*
*
* @return: 1 - if t.Suma < Suma
*          0 - otherwise
*/
int biggerSum(PTRANZACTIE t, double Suma);

/**
* Function that checks if the Suma field of a transaction is bigger than the given one
*
* @params: t - a pointer to a transaction
*          Suma - a double
*
*
* @return: 1 - if t.Suma > Suma
*          0 - otherwise
*/
int smallerSum(PTRANZACTIE t, double Suma);

void testUtils();

#endif 
