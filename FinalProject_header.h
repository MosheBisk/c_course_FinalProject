#ifndef FINAL_PROJECT_H
#define FINAL_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    firstname, lastname, id, phoneNum, debt, purchaseDate
} dataNames;

typedef enum {
    false, true
} bool;

typedef struct{
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 12;
}date;

typedef struct {
    char *firstname, *lastname, phoneNum[10];
    date purchaseDate;
    unsigned int id;
    float debt;
}customer;

typedef struct myNode{
    customer *singleCustomer;
    struct myNode *next;
}myNode;

void readAndPrintCsv();
int readAndPrintCsvSum();
void parseCsvLine(char *tempCharPointer, customer *tempCustomerActivity);
myNode *findCustomerInList(myNode *listHead, unsigned int customerId);
void addCustomerToList(myNode **listHead, customer *customerActivity);
void addActivityToCustomer(myNode *customerNode, customer *customerActivity);
void deallocateLinkedList(myNode **listHead);
void printCustomerDetailsList(myNode *listHead);
void mergeSortList(myNode **listHead);
void splitList(myNode **listHead, myNode **evenHead, myNode **oddHead);
void mergeList(myNode **listHead, myNode **evenHead, myNode **oddHead);

#endif