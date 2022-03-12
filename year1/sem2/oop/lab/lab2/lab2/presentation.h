#ifndef _PRESENTATION_H_
#define _PRESENTAION_H_

#include <stdio.h>
#include <stdlib.h>
#include "service.h"
#include <ctype.h>

#define oo 0x3f3f3f3f

typedef struct CONSOLE {
    PSERVICE_PRODUCTS ServiceProduse;
} CONSOLE, * PCONSOLE;

int readCommand();

/**
* Function that creates a console
* 
* @params: Console - a pointer to a pointer to a console
*          ServiceProduse - a pointer to a service
* 
* @return: 0 - if the creation is a success
*         -1 - otherwise
*/
int CreateConsole(PCONSOLE* Console, PSERVICE_PRODUCTS ServiceProduse);

/**
* Function that destroys a previously created console
*
* @params: Console - a pointer to a pointer to a console
*
* @return: 0 - if the destruction is a success
*         -1 - otherwise
*/
int DestroyConsole(PCONSOLE* Console);


int consoleAddProdus(PCONSOLE Console, char* errors);
int consoleDeleteProdus(PCONSOLE Console, char* errors);
int consoleViewProduse(PCONSOLE Console, char* errors);
int consoleFilterProduse(PCONSOLE Console, char* errors);

int runConsole(PCONSOLE Console);

#endif
