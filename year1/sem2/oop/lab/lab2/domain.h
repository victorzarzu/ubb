#ifndef _DOMAIN_H_
#define _DOMAIN_H_

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define epsilon 1e-5

typedef struct _PRODUS {
    int Id;
    char* Tip;
    char* Producator;
    char* Model;
    double Pret;
    int Cantitate;
}PRODUS, *PPRODUS;

/**
* Function that returns the Id of the product
* 
* @params: Produs - a product
* 
* @return: the product id (integer)
*/
int GetId(PRODUS Produs);

/**
* Function that sets the Id of the product
* 
* @params: Produs - a pointer to a product
*          Id - integer
* 
* @return: -
*/
void SetId(PPRODUS Produs, int Id);

/**
* Function that returns the Tip of the product
*
* @params: Produs - a product
*
* @return: the product Tip (char*)
*/
char* GetTip(PRODUS Produs);

/**
* Function that sets the Tip of the product
*
* @params: Produs - a pointer to a product
*          Tip - pointer to a char
*
* @return: -
*/
void SetTip(PPRODUS Produs, char* Tip);

/**
* Function that returns the Producator of the product
*
* @params: Produs - a product
*
* @return: the product Producator (char*)
*/
char* GetProducator(PRODUS Produs);

/**
* Function that sets the Producator of the product
*
* @params: Produs - a pointer to a product
*          Producator - pointer to a char
*
* @return: -
*/
void SetProducator(PPRODUS Produs, char* Producator);

/**
* Function that returns the Model of the product
*
* @params: Produs - a product
*
* @return: the product Model (char*)
*/
char* GetModel(PRODUS Produs);

/**
* Function that sets the Model of the product
*
* @params: Produs - a pointer to a product
*          Model - pointer to a char
*
* @return: -
*/
void SetModel(PPRODUS Produs, char* Model);

/**
* Function that returns the Pret of the product
*
* @params: Produs - a product
*
* @return: the product Pret (double)
*/
double GetPret(PRODUS Produs);

/**
* Function that sets the Pret of the product
*
* @params: Produs - a pointer to a product
*          Pret - a double
*
* @return: -
*/
void SetPret(PPRODUS Produs, double Pret);

/**
* Function that returns the Cantitate of the product
*
* @params: Produs - a product
*
* @return: the product Cantitate (integer)
*/
int GetCantitate(PRODUS Produs);

/**
* Function that sets the Cantitate of the product
*
* @params: Produs - a pointer to a product
*          Cantitate - a integer
*
* @return: -
*/
void SetCantitate(PPRODUS Produs, int Cantitate);

/**
* Function that checks if 2 products have the same attributes (excepting Cantitate)
* 
* @params: Produs1 - a product
*          Produs2 - a product
* 
* @return: 0 - if the products are different
*          1 - if the products are the same
*/
int ProdusEqual(PRODUS Produs1, PRODUS Produs2);

/**
* Function that creates a product with the given attributes and returns the product via the pointer to a product
* 
* @params: Produs - pointer to a pointer to a product
*          Id - an integer
*          Tip - pointer to a char
*          Producator - pointer to a char
*          Model - pointer to a char
*          Pret - a double
*          Cantitate - an integer
* 
* @return: 0 - if the creation is succesful and the product is referenced by product
*         -1 - if the creation failed
*/
int CreateProdus(PPRODUS* Produs, int Id, char* Tip, char* Producator, char* Model, double Pret, int Cantitate);

/**
* Function that compares 2 products in increasing order (first based on the price and after based on the quantity)
* 
* @params: Produs1 - a pointer to void
*          Produs2 - a pointer to void
* 
* @return: -1 - if Produs1 < Produs2 or at least one of the pointers is NULL
*           0 - if Produs1 == Produs2
*           1 - if Produs1 > Produs2
*/
int CompareProduseIncreasing(const void* Produs1, const void* Produs2);

/**
* Function that compares 2 products in decreasing order (first based on the price and after based on the quantity)
*
* @params: Produs1 - a pointer to void
*          Produs2 - a pointer to void
*
* @return: -1 - if Produs1 > Produs2 or at least one of the pointers is NULL
*           0 - if Produs1 == Produs2
*           1 - if Produs1 < Produs2
*/
int CompareProduseDecreasing(const void* Produs1, const void* Produs2);

/*
* Function that destroys a product
* 
* @params: Produs - pointer to a pointer to a product
* 
* @return: 0 - if the destroy is succesful
*          -1 - otherwise
*/
int DestroyProdus(PPRODUS* Produs);

/**
* Function that prints Produs in a nice form
* 
* @params: Produs - a product
* 
* @return: -
*/
//void PrintFormat(PRODUS Produs);

void testDomain();

#endif