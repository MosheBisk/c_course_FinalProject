#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include "FinalProject_data_types.h"

int readCsv(FILE *filePointer, customerNode **listHead);
void createOrAddToList(customerNode **listHead, customerActivity *singleCustomer, bool isNewCustomer);
void addCustomerToList(customerNode **listHead, customerActivity *customerActivity);
void addActivityToCustomer(customerNode *customerNode, customerActivity *customerActivity);

void manageUserInput(customerNode **listHead);
void filterCustomersListByQuery(customerNode **listHead, char *query);
void insertNewCustomerActivity(customerNode **listHead, char *activityInfo);

#endif