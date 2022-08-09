#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include "FinalProject_data_types.h"

int readCsvCreateList(FILE *filePointer, myNode **listHead);
void addCustomerToList(myNode **listHead, customer *customerActivity);
void addActivityToCustomer(myNode *customerNode, customer *customerActivity);


#endif