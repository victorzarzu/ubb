#ifndef _VALIDATION_H_
#define _VALIDATION_H_

#include "domain.h"
#include <string.h>

typedef int (*ValidationFunction)(TRANZACTIE*, char*);

/**
* Function that validates a product
*
* @params: Produs - a product
*          errors - a pointer to a char
*
* @return: 0 - if the product is valid
*         -1 - if the product is not valid and the error messages will be in errors
*/
int ValidateTranzactie(TRANZACTIE* Tranzactie, char* errors);



#endif