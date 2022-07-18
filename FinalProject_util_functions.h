#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include "FinalProject_header.h"

void parseCsvLine(char *tempCharPointer, customer *tempCustomerActivity);
myNode *findCustomerInList(myNode *listHead, customer *customerActivity, customerDataFields findByType, filteringMethod filterBy);
void printCustomerDetailsList(myNode *listHead);
void mergeSortList(myNode **listHead);
void splitList(myNode **listHead, myNode **evenHead, myNode **oddHead);
void mergeList(myNode **listHead, myNode **evenHead, myNode **oddHead);
void deallocateLinkedList(myNode **listHead);


#endif