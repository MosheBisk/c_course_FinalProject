#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include "FinalProject_data_types.h"

int findCustomerField(char *data);
int findComparisonType(char *data);
int findValueInArray(getEnumStr getfunc, int size, char *value);

void parseCsvLine(char *tempCharPointer, customer *tempCustomerActivity);
myNode *findCustomerInList(myNode *listHead, myNode *newListHead, customerDataFields findByType, filteringMethod comparisonType, char *filteringValue);
void printCustomerDetailsList(myNode *listHead);
void mergeSortList(myNode **listHead);
void splitList(myNode **listHead, myNode **evenHead, myNode **oddHead);
void mergeList(myNode **listHead, myNode **evenHead, myNode **oddHead);
void deallocateLinkedList(myNode **listHead);

int filterByFirstName(customer *customer, filteringMethod comparisonType, char *firstName);
int filterByLastName(customer *customer, filteringMethod comparisonType, char *lastName);
int filterById(customer *customer, filteringMethod comparisonType, char *id);
int filterByPhoneNumber(customer *customer, filteringMethod comparisonType, char *phoneNumber);
int filterByDebt(customer *customer, filteringMethod comparisonType, char *debt);
int filterByPurchaseDate(customer *customer, filteringMethod comparisonType, char *purchaseDate);
int parseDateToInt(int day, int month, int year);

int equalComparison(float customerValue, float queryValue);
int lessThanComparison(float customerValue, float queryValue);
int greaterThanComparison(float customerValue, float queryValue);
int lessThanOrEqualComparison(float customerValue, float queryValue);
int greaterThanOrEqualComparison(float customerValue, float queryValue);



#endif