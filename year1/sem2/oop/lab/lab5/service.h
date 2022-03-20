#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "domain.h"
#include "infrastructure.h"
#include "validation.h"
#include "utils.h"
#include "repository.h"
#include <string.h>

#define oo 0x3f3f3f3f

typedef struct _SERVICE_TRANZACTII {
    REPOSITORY* Repository;
    ValidationFunction ValidateTranzactie;
} SERVICE_TRANZACTII, * PSERVICE_TRANZACTII;

/**
* Function that creates a service for transactions
*
* @params: Repository - a repository for transactions
*          Validation - a pointer to a validation function
*
* @return: a service for products
*/
SERVICE_TRANZACTII CreateService(REPOSITORY* Repository, ValidationFunction Validation);

/**
* Function that stores a transaction
*
* @params: Service - pointer to a service for transactions
*          Id - an integer
*          Zi - an integer
*          Suma - a double
*          Tip - an integer
*          Descriere - pointer to a char
*          errors - pointer to a char
*
* @return: 0 - if the storing is successful
*         -1 - otherwise and the errors are in errors variable
*/
int StoreTranzactie(PSERVICE_TRANZACTII Service, int Id, int Zi, double Suma, int Tip, char *Descriere, char* errors);

/**
* Function that deletes the transaction with the given id
*
* @params: Service - pointer to a service for transactions
*          Id - an integer
*          errors - pointer to a char
*
* @return: 0 - if the deletion is successful
*         -1 - otherwise and the errors are in errors
*/
int EraseTranzactie(PSERVICE_TRANZACTII Service, int Id, char* errors);

/**
* Function that modifies the day and sum of the transaction with the given id
*
* @params: Service - pointer to a service for transactions
*          Id - an integer
*          Suma - a double
*          Zi - an integer
*          errors - pointer to a char
*
* @return: 0 - if the modification is successful
*         -1 - otherwise and the errors are in errors
*/
int ChangeTranzactie(PSERVICE_TRANZACTII Service, int Id, double Suma, int Zi, char* errors);

/**
* Function that returns all the products sorted in Mode mode
*
* @params: Service - pointer to  a service for products
*          Mode - an integer representing the sorting mode
*          AscendingMode - an integer representing the ascending mode of the sorting
*          errors - pointer to a char
*
* @return: a pointer to a list of transactions sorted in the desired order
*/
MY_LIST* ViewTranzactii(PSERVICE_TRANZACTII Service, int Mode, int AscendingMode, char* errors);

/**
* Function that returns all the transactions that match the given filter
*
* @params: Service - pointer to  a service for transactions
*          Tip - an integer
*          Suma - a double
*          Zi - an integer
*          Mode - an integer
*          errors - pointer to a char
*
* @return: a pointer to a list for transactions that has only the products that matches the filter
*/
MY_LIST* FilterTranzactii(PSERVICE_TRANZACTII Service, int Tip, double Suma, int Zi, int Mode, int sumMode, char* errors);

/**
* Function that destroys a previously created Service
*
* @params: Service - pointer to a service for transactions
*
* @return: 0 - if the destruction was successful
*         -1 - if there was an error
*/
int DestroyService(PSERVICE_TRANZACTII Service);

/**
* Function that does an undo
*
* @params: Service - pointer to a service for transactions
*
* @return: 0 - if the destruction was successful
*         -1 - if there was an error
*/
int Undo(PSERVICE_TRANZACTII Service);

void testService();

#endif