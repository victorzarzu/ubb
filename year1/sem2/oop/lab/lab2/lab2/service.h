#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "domain.h"
#include "infrastructure.h"
#include "validation.h"
#include <string.h>

#define oo 0x3f3f3f3f

typedef struct _SERVICE_PRODUCTS {
    PREPOSITORY_PRODUSE Repository;
    ValidationFunction ValidateProduct;
} SERVICE_PRODUCTS, *PSERVICE_PRODUCTS;

/**
* Function that creates a service for products
* 
* @params: Service - a pointer to a pointer to a service for products
*          Repository - a pointer to a repository
*          Validation - a pointer to a validation function
* 
* @return: 0 - if the creation is successful
*         -1 - otherwise
*/
int CreateService(PSERVICE_PRODUCTS* Service, PREPOSITORY_PRODUSE Repository, ValidationFunction Validation);

/**
* Function that stores a product
* 
* @params: Service - pointer to a service for products
*          Id - an integer
*          Tip - pointer to a char
*          Producator - pointer to a char
*          Model - pointer to a char
*          Pret - a double
*          Cantitate - an integer
*          errors - pointer to a char
* 
* @return: 0 - if the storing is successful
*         -1 - otherwise and the errors are in errors
*/
int StoreProdus(PSERVICE_PRODUCTS Service, int Id, char* Tip, char* Producator, char* Model, double Pret, int Cantitate, char* errors);

/**
* Function that deletes the product with the given id
* 
* @params: Service - pointer to a service for products
*          Id - an integer
*          errors - pointer to a char
* 
* @return: 0 - if the deletion is successful
*         -1 - otherwise and the errors are in errors
*/
int EraseProdus(PSERVICE_PRODUCTS Service, int Id, char *errors);

/**
* Function that modifies the price or quantity of the product with the given id
* 
* @params: Service - pointer to a service for products
*          Id - an integer
*          Pret - a double
*          Cantitate - an integer
*          errors - pointer to a char
* 
* @return: 0 - if the modification is successful
*         -1 - otherwise and the errors are in errors
*/
int ChangeProdus(PSERVICE_PRODUCTS Service, int Id, double Pret, int Cantitate, char* errors);

/**
* Function that returns all the products sorted in Mode mode
*
* @params: Service - pointer to  a service for products
*          Mode - an integer
*          Array - a pointer to an array of products
*          errors - pointer to a char
*/
int ViewProduse(PSERVICE_PRODUCTS Service, int Mode, PPRODUS* Array, char* errors);

/**
* Function that returns all the products that match the given filter
*
* @params: Service - pointer to  a service for products
*          Producator - a pointer to char
*          Pret - a double
*          Cantitate - an integer
*          Array - a pointer to an array of products
*          Number - a pointer to integer
*          errors - pointer to a char
*/
int FilterProduse(PSERVICE_PRODUCTS Service, char* Producator, double Pret, int Cantitate, PPRODUS* Array, int* Number, char* errors);

/**
* Function that destroys a previously created Service
* 
* @params: Service - pointer to a pointer to a service for products
* 
* @return: 0 - if the destruction was successful
*/
int DestroyService(PSERVICE_PRODUCTS* Service);

void testService();

#endif