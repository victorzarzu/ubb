#ifndef _DOMAIN_H_
#define _DOMAIN_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define epsilon 1e-5

typedef struct _TRANZACTIE {
    int Id;
    int Zi;
    double Suma;
    int Tip;
    char* Descriere;
}TRANZACTIE, * PTRANZACTIE;


typedef int (*comparerInt)(int, int);
typedef int (*comparerDouble)(double, double);

/**
* Function that returns the Id of the product
*
* @params: Tranzactie - a product
*
* @return: the product id (integer)
*/
int GetId(PTRANZACTIE Tranzactie);

/**
* Function that sets the Id of the product
*
* @params: TRANZACTIE - a pointer to a product
*          Id - integer
*
* @return: -
*/
void SetId(PTRANZACTIE Tranzactie, int Id);

/**
* Function that returns the Tip of the product
*
* @params: TRANZACTIE - a product
*
* @return: the product Tip (char*)
*/
int GetTip(PTRANZACTIE Tranzactie);

/**
* Function that sets the Tip of the product
*
* @params: TRANZACTIE - a pointer to a product
*          Tip - pointer to a char
*
* @return: -
*/
void SetTip(PTRANZACTIE Tranzactie, int Tip);

/**
* Function that returns the Producator of the product
*
* @params: TRANZACTIE - a product
*
* @return: the product Producator (char*)
*/
int GetZi(PTRANZACTIE Tranzactie);

/**
* Function that sets the Producator of the product
*
* @params: TRANZACTIE - a pointer to a product
*          Producator - pointer to a char
*
* @return: -
*/
void SetZi(PTRANZACTIE Tranzactie, int Zi);

/**
* Function that returns the Model of the product
*
* @params: TRANZACTIE - a product
*
* @return: the product Model (char*)
*/
char* GetDescriere(PTRANZACTIE Tranzactie);

/**
* Function that sets the Model of the product
*
* @params: TRANZACTIE - a pointer to a product
*          Model - pointer to a char
*
* @return: -
*/
void SetDescriere(PTRANZACTIE Tranzactie, char* Descriere);

/**
* Function that returns the Pret of the product
*
* @params: TRANZACTIE - a product
*
* @return: the product Pret (double)
*/
double GetSuma(PTRANZACTIE Tranzactie);

/**
* Function that sets the Pret of the product
*
* @params: TRANZACTIE - a pointer to a product
*          Pret - a double
*
* @return: -
*/
void SetSuma(PTRANZACTIE Tranzactie, double Suma);

/**
* Function that returns the Cantitate of the product
*
* @params: TRANZACTIE - a product
*
* @return: the product Cantitate (integer)
*/
int TranzactieEqual(PTRANZACTIE Tranzactie1, PTRANZACTIE Tranzactie2);

/**
* Function that creates a product with the given attributes and returns it
*
* @params: Id - an integer
*          Tip - pointer to a char
*          Producator - pointer to a char
*          Model - pointer to a char
*          Pret - a double
*          Cantitate - an integer
*
* @return: a product
*/
TRANZACTIE* CreateTranzactie(int Id, int Zi, double Suma, int Tip, char* Descriere);

/**
* Function that compares 2 products in increasing order (first based on the price and after based on the quantity)
*
* @params: TRANZACTIE1 - a pointer to void
*          TRANZACTIE2 - a pointer to void
*
* @return: -1 - if TRANZACTIE1 < TRANZACTIE2 or at least one of the pointers is NULL
*           0 - if TRANZACTIE1 == TRANZACTIE2
*           1 - if TRANZACTIE1 > TRANZACTIE2
*/
int CompareTranzactieSuma(const PTRANZACTIE Tranzactie1, const PTRANZACTIE Tranzactie2, comparerDouble comparer);

/**
* Function that compares 2 products in decreasing order (first based on the price and after based on the quantity)
*
* @params: TRANZACTIE1 - a pointer to void
*          TRANZACTIE2 - a pointer to void
*
* @return: -1 - if TRANZACTIE1 > TRANZACTIE2 or at least one of the pointers is NULL
*           0 - if TRANZACTIE1 == TRANZACTIE2
*           1 - if TRANZACTIE1 < TRANZACTIE2
*/
int CompareTranzactieZi(const PTRANZACTIE Tranzactie1, const PTRANZACTIE Tranzactie2, comparerInt comparer);

/*
* Function that destroys a product
*
* @params: TRANZACTIE - pointer to a pointer to a product
*
* @return: -
*/
void DestroyTranzactie(PTRANZACTIE Tranzactie);

/**
* Function that copies the given product and returns its copy
*
* @params: TRANZACTIE - a product
*
* @return: the copy of the product (TRANZACTIE)
*/
TRANZACTIE* CopyTranzactie(PTRANZACTIE Tranzactie);

void testDomain(void);

#endif