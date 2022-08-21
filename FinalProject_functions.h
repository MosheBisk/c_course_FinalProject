#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include "FinalProject_data_types.h"

int readCsv(FILE *filePointer, myNode **listHead);
void createOrAddToList(myNode **listHead, customer *singleCustomer);
void addCustomerToList(myNode **listHead, customer *customerActivity);
void addActivityToCustomer(myNode *customerNode, customer *customerActivity);

void manageUserInput(myNode **listHead);
void filterCustomersListByQuery(myNode **listHead, char *query);
void insertNewCustomerActivity(myNode **listHead, char *activityInfo);

#endif