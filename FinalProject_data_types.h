#ifndef FINAL_PROJECT_DATA_TYPES_H
#define FINAL_PROJECT_DATA_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 2000
#define MAX_USER_INPUT 2000
#define FIRST_NAME_LENGTH 50
#define LAST_NAME_LENGTH 25
#define FIELD_TYPE_SIZE 6
#define FILTERING_METHOD_SIZE 5
#define QUERY_STRINGS_SIZE 4
#define NUM_OF_FIELDS_TO_COMPARE 4
#define PRE_QUERY_PRINT "Please enter a command: select for searching, set for adding, print for printing, quit for exiting.\n---> "
#define CSV_FILE_NAME "customer_activity.csv"

typedef enum {
    firstname, lastname, id, phoneNum, debt, purchaseDate
} customerDataFields;

typedef enum {
    equal, less, greater, lessEqual, greaterEqual
} filteringMethod;

typedef enum {
    false, true
} bool;

typedef enum {
    _select, set, print, quit
} queryTypes;

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
}customerActivity;

typedef struct customerNode{
    customerActivity *singleCustomer;
    struct customerNode *next;
}customerNode;


char *getFieldNameStrings(int field);
char *getQueryString(int queryType);
char *getComparisonTypeString(int comparisonType);
typedef char *(*getEnumStr)(int);

typedef int (*filterCustomerList)(customerActivity*, filteringMethod, char*);
filterCustomerList getCustomerListFilter(customerDataFields field);

typedef int (*comparisonFunctions)(float, float);
comparisonFunctions getComparisonFunction(filteringMethod comparisonType);

typedef int (*fieldValueValidaters)(char*);
fieldValueValidaters getFieldValueValidater(customerDataFields field);

typedef int (*customerFieldComparators)(customerActivity*, customerActivity*);
customerFieldComparators getCustomerFieldComparators(customerDataFields field);

#endif