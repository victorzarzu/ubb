#ifndef _INFRASTRUCTURE_H_
#define _INFRASTRUCTURE_H_

#include <stdlib.h>
#include "domain.h"

typedef void* ElemType;

#define INITIAL_SIZE 4
#define RC 2
#define RM 2
#define INPUT_SIZE 20

typedef struct _MY_LIST
{
    ElemType* Array;
    int Count;
    int Size;
}MY_LIST, * PMY_LIST;

typedef void (*DestroyFunction)(ElemType);

/**
* Function that creates an empty List and returns it
*
* @params: -
*
* @return: a pointe to the created list
*
*/
MY_LIST* CreateList();

/**
*
* Function that access the element on given position
*
* @params: List - a pointer to a List
*          Position - an integer (the element position)
*
* @return: the accessed element (ElemType)
*
*/
ElemType GetElement(PMY_LIST List, int Position);

/**
*
* Function that sets the element on the given position to a new one
*
* @params: List - a pointer to a List
*          Position - an integer (the element position)
*          Tranzactie - ElemType
*
* @return: the old element on that position (ElemType)
*
*/
ElemType SetElement(PMY_LIST List, int Position, ElemType Tranzactie);

/**
* Function that searches for a transaction by its id and returns the answer via Result pointer
*
* @params: List - a pointer to a List
*          Id - an integer
*          Result - a pointer to an ElemType
*
* @return: 0 - if the search is successful and transaction will reference the searched product
*         -1 - if the product does not exist
*/
int SearchTranzactie(PMY_LIST List, int Id, ElemType* Result);

/**
* Function that inserts an ElemType in the List
*
* @params: List - a pointer to a list
*          Element - a pointer to an ElemType
*
* @return: 0 - if the insert is successful
*/
int Insert(PMY_LIST List, ElemType Element);

/**
* Function that deletes an transaction from the list
*
* @params: List - a pointer to a Repository for products
*          Id - an integer
*          destrF - a pointer to a destruction function
*
* @result: 0 - if the deletion is successful
*         -1 - if error
*/
int Delete(PMY_LIST List, int Id, DestroyFunction destrF);

/**
* Function that clears the list
*
* @params: List - a pointer to a List
*          destrF - a destruction function
*
* @return: 0 - if the clearing is successful
*         -1 - otherwise
*/
int ClearList(PMY_LIST List, DestroyFunction destrF);

/**
* Function that returns a deep copy of the list
*
* @params: List - a pointer to a list
*
* @return: the copy of the given List (MY_LIST*)
*/
MY_LIST* CopyList(PMY_LIST List);

/**
* Function that returns the number of elements in the list
*
* @params: List - a pointer to a list
*
* @return: the number of elements in the list (integer)
*/
int GetLength(PMY_LIST List);

/**
* Function that removes the last element from the list and returns it
*
* @params: List - a pointer to a list
*
* @return: an ElemType
*/
ElemType RemoveLast(PMY_LIST List);

/**
* Function that maintains the upper limit of the list
* 
* @params: List - a pointer to a list
*
* @return: -
*/
void MaintainListBelow(PMY_LIST List);

/**
* Function that maintains the bottom limit of the list
*
* @params: List - a pointer to a list
*
* @return: -
*/
void MaintainListAbove(PMY_LIST List);

/**
* Function that destroys a previously created list
*
* @params: List - pointer to a list
*          destrF - a pointer to a destruction function
*
* @return: 0 - if the destruction was successful
*         -1 - if the there was a problem
*/
int Destroy(PMY_LIST List, DestroyFunction destrF);

/**
* Function that destroys a previously created list of elements
*
* @params: List - pointer to a list
*
* @return: -
*/
void DestroyList(MY_LIST* List);

void testInfrastructure();

#endif
