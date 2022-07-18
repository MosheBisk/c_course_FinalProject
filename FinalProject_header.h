#ifndef FINAL_PROJECT_H
#define FINAL_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    firstname, lastname, id, phoneNum, debt, purchaseDate
} customerDataFields;

typedef enum {
    equal = '=', less = '<', greater = '>'
} filteringMethod;

typedef enum {
    false, true
} bool;

typedef struct {
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

int readCsvCreateList(FILE *filePointer, myNode **listHead);
void addCustomerToList(myNode **listHead, customer *customerActivity);
void addActivityToCustomer(myNode *customerNode, customer *customerActivity);

#endif