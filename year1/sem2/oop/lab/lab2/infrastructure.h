#ifndef _INFRASTRUCTURE_H_
#define _INFRASTRUCTURE_H_

#include <stdlib.h>
#include "domain.h"

#define INITIAL_SIZE 64
#define RC 2
#define RM 2
#define INPUT_SIZE 20

typedef struct _REPOSITORY_PRODUSE
{
    PPRODUS* Array;
    int Count;
    int Size;
}REPOSITORY_PRODUSE, * PREPOSITORY_PRODUSE;

/**
* Function that creates a Repository for products
*
* @params: Rpository - a pointer to a Repository for products pointer
*
* @return: 0 - if the creation is successful and Repository will reference a Repository for products
*         -1 - if the creation failed
*
*/
int CreateRepository(PREPOSITORY_PRODUSE* Repository);

/**
* Function that searches for a product by its id and returns the answer via Produs pointer
*
* @params: Repository - a pointer to a Repository for products
*          Id - an integer
*          Produs - a pointer to a product
*
* @return: 0 - if the search is successful and Produs will reference the searched product
*         -1 - if the product does not exist
*/
int SearchProdus(PREPOSITORY_PRODUSE Repository, int Id, PPRODUS Produs);

/**
* Function that inserts Produs in the Repository or updates its Quantity if it is already in repo
*
* @params: Repository - a pointer to a Repository for products
*          Produs - a pointer to a product
*
* @return: 0 - if the insert is successful
*         -1 - if it is already in the Repo another product with Produs' Id and it does not have the same attributes
*/
int InsertProdus(PREPOSITORY_PRODUSE Repository, PPRODUS Produs);

/**
* Function that deletes the product with the given Id from Repository
*
* @params: Repository - a pointer to a Repository for products
*          Id - an integer
*
* @result: 0 - if the deletion is successful
*         -1 - if does not exists a product with the given Id
*/
int DeleteProdus(PREPOSITORY_PRODUSE Repository, int Id);

/**
* Function that modifies the Pret and Cantitate of the product that has the given Id
*
* @params: Repository - a pointer to a Repository for products
*          Id - an integer
*          Pret - a double value
*          Cantitate - an integer
*
* @return: 0 - if the modification is successful
*         -1 - if there is no product with the given Id
*/
int ModifyProdus(PREPOSITORY_PRODUSE Repository, int Id, double Pret, int Cantitate);

/**
* Function that clears the repository
*
* @params: Repository - a pointer to a Repository for products
*
* @return: 0 - if the clearing is successful
*         -1 - otherwise
*/
int ClearRepository(PREPOSITORY_PRODUSE Repository);

/**
* Function that returns a deep copy of all the products in the repo
* 
* @params: Repository - a pointer to a Repository for products
*          Array - a pointer to a pointer to a product
*
* @return: 0 - if the GetAll is successful
*         -1 - otherwise
*/
int GetAll(PREPOSITORY_PRODUSE Repository, PPRODUS* Array);

/**
* Function that returns the number of products in the Repository
* 
* @params: Repository - a pointer to a Repository for products
* 
* @return: the number of products in the Repository (integer)
*/
int GetLength(PREPOSITORY_PRODUSE Repository);

/**
* Function that destroys a previously created repository
*
* @params: Service - pointer to a pointer to a service for products
*
* @return: 0 - if the destruction was successful
*         -1 - if the there was a problem
*/
int DestroyRepository(PREPOSITORY_PRODUSE* Repository);

void testInfrastructure();

#endif
