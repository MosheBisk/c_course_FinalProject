#ifndef FINAL_PROJECT_H
#define FINAL_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    firstname, lastname, id, phoneNum, debt, purchaseDate
    } dataNames;

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

typedef struct{
    customer singleActivity;
    struct Node *next;
}Node;

void readAndPrintCsv();
int readAndPrintCsvSum();
void parseCsvLine(char *tempCharPointer, customer *tempCustomerActivity);

#endif