#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include "FinalProject_data_types.h"

int findCustomerField(char *data);
int findComparisonType(char *data);
int findValueInArray(getEnumStr getfunc, int size, char *value);

void parseCsvLine(char *tempCharPointer, customerActivity *tempCustomerActivity);
customerNode *findIfCustomerIsInList(customerNode *listHead, unsigned int customerId);
void filterListForCustomers(customerNode *listHead, customerNode **newListHead, customerDataFields findByType, filteringMethod comparisonType, char *filteringValue);
void printCustomerDetailsList(customerNode **listHead);
void mergeSortList(customerNode **listHead);
void splitList(customerNode **listHead, customerNode **evenHead, customerNode **oddHead);
void mergeList(customerNode **listHead, customerNode **evenHead, customerNode **oddHead);
void copyCustomerDetails(customerActivity *source, customerActivity *destination);
customerNode* allocNewNode();
customerActivity* allocNewCustomerActivity();
void deallocateLinkedList(customerNode **listHead);

void compareCustomerDetails(customerActivity *originalDetails, customerActivity *newDetails);
int compareFirstName(customerActivity *originalDetails, customerActivity *newDetails);
int compareLastName(customerActivity *originalDetails, customerActivity *newDetails);
int compareId(customerActivity *originalDetails, customerActivity *newDetails);
int comparePhoneNumber(customerActivity *originalDetails, customerActivity *newDetails);

int filterByFirstName(customerActivity *customerActivity, filteringMethod comparisonType, char *firstName);
int filterByLastName(customerActivity *customerActivity, filteringMethod comparisonType, char *lastName);
int filterById(customerActivity *customerActivity, filteringMethod comparisonType, char *id);
int filterByPhoneNumber(customerActivity *customerActivity, filteringMethod comparisonType, char *phoneNumber);
int filterByDebt(customerActivity *customerActivity, filteringMethod comparisonType, char *debt);
int filterByPurchaseDate(customerActivity *customerActivity, filteringMethod comparisonType, char *purchaseDate);
int parseDateToInt(int day, int month, int year);

int equalComparison(float customerValue, float queryValue);
int lessThanComparison(float customerValue, float queryValue);
int greaterThanComparison(float customerValue, float queryValue);
int lessThanOrEqualComparison(float customerValue, float queryValue);
int greaterThanOrEqualComparison(float customerValue, float queryValue);

int isValidFirstName(char *fieldValue);
int isValidLastName(char *fieldValue);
int isValidId(char *fieldValue);
int isValidPhoneNumber(char *fieldValue);
int isValidDebt(char *fieldValue);
int isValidPurchaseDate(char *fieldValue);
int isAlphabetical(char *fieldValue);
int isNumeric(char *fieldValue);



#endif