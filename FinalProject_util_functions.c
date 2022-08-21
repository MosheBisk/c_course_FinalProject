#include "FinalProject_util_functions.h"
#include "FinalProject_data_types.h"

void mergeSortList(myNode **listHead){
    myNode *evenHead = NULL, *oddHead = NULL;

    if (*listHead == NULL || (*listHead)->next == NULL)
        return;

    splitList(listHead, &evenHead, &oddHead);
    mergeSortList(&evenHead);
    mergeSortList(&oddHead);
    mergeList(listHead, &evenHead, &oddHead);
}

void splitList(myNode **listHead, myNode **evenHead, myNode **oddHead){
    myNode *tempNode;
    bool isOdd = true;

    while (*listHead != NULL)
    {
        tempNode = *listHead;
        *listHead = (*listHead)->next;
        if (isOdd)
        {
            tempNode->next = *oddHead;
            *oddHead = tempNode;
        }
        else
        {
            tempNode->next = *evenHead;
            *evenHead = tempNode;
        }
        isOdd = !isOdd;
    }
}
void mergeList(myNode **listHead, myNode **evenHead, myNode **oddHead){
    myNode *listTail = NULL, *tempNode;
    while (*evenHead != NULL && *oddHead != NULL)
    {
        if ((*evenHead)->singleCustomer->debt <= (*oddHead)->singleCustomer->debt)
        {
            tempNode = *evenHead;
            *evenHead = (*evenHead)->next;
        }
        else
        {
            tempNode = *oddHead;
            *oddHead = (*oddHead)->next;
        }
        tempNode->next = NULL;
        
        if (*listHead == NULL)
        {
            *listHead = listTail = tempNode;
        }
        else
        {
            listTail->next = tempNode;
            listTail = listTail->next;
        }

        if (*evenHead == NULL)
        {
            listTail->next = *oddHead;
        }
        else if(*oddHead == NULL)
        {
            listTail->next = *evenHead;
        }
    }
}

void printCustomerDetailsList(myNode *listHead){
    mergeSortList(&listHead);
    myNode *ptr = listHead;
    while (ptr != NULL)
    {
        printf("%-11s %-9s %10u %12s %12.2f  %02u/%02u/%4u\n", 
                ptr->singleCustomer->firstname, 
                ptr->singleCustomer->lastname, 
                ptr->singleCustomer->id, 
                ptr->singleCustomer->phoneNum, 
                ptr->singleCustomer->debt, 
                ptr->singleCustomer->purchaseDate.day, 
                ptr->singleCustomer->purchaseDate.month, 
                ptr->singleCustomer->purchaseDate.year);
        ptr = ptr->next;
    }
}

// void exitProgram(myNode **listHead){

// }

myNode *findCustomerInList(myNode *listHead, myNode *newListHead, customerDataFields findByType, filteringMethod comparisonType, char *filteringValue){
    myNode *presNode = listHead, *newNode;
    int result;

    while (presNode != NULL)
    {
        result = 0;
        result = getCustomerListFilter(findByType)(presNode->singleCustomer, comparisonType, filteringValue);
        if (result == 1){
            if (comparisonType == equal)
                return presNode;
            else{
                newNode = (myNode*) malloc(sizeof(myNode));
                if (newNode == NULL){
                    printf("%s\n", "Error: malloc failed");
                    return NULL;
                }
                newNode->singleCustomer = presNode->singleCustomer;
                newNode->next = newListHead;
                newListHead = newNode;
            }
        }
        
        // printf("%d\n", result);
        presNode = presNode->next;
    }
    return newListHead;
    // return presNode;
}

int filterByFirstName(customer *customer, filteringMethod comparisonType, char *firstName){
    return !strcmp(customer->firstname, firstName); 
}
int filterByLastName(customer *customer, filteringMethod comparisonType, char *lastName){
    return !strcmp(customer->lastname, lastName); 
}
int filterById(customer *customer, filteringMethod comparisonType, char *id){
    return customer->id == atoi(id); 
}
int filterByPhoneNumber(customer *customer, filteringMethod comparisonType, char *phoneNumber){
    return !strcmp(customer->phoneNum, phoneNumber); 
}
int filterByDebt(customer *customer, filteringMethod comparisonType, char *debt){
    return getComparisonFunction(comparisonType)(customer->debt, strtof(debt, NULL)); 
}
int filterByPurchaseDate(customer *customer, filteringMethod comparisonType, char *purchaseDate){
    int day, month, year;
    sscanf(purchaseDate, "%02d/%02d/%04d", &day, &month, &year);
    int customersDate = parseDateToInt(customer->purchaseDate.day, customer->purchaseDate.month, customer->purchaseDate.year);
    int filterDate = parseDateToInt(day, month, year);
    return getComparisonFunction(comparisonType)(customersDate, filterDate); 
}
int parseDateToInt(int day, int month, int year){
    return year * 10000 + month * 100 + day;
}

int equalComparison(float customerValue, float queryValue){
    return customerValue == queryValue;
}
int lessThanComparison(float customerValue, float queryValue){
    return customerValue < queryValue;
}
int greaterThanComparison(float customerValue, float queryValue){
    return customerValue > queryValue;
}
int lessThanOrEqualComparison(float customerValue, float queryValue){
    return customerValue <= queryValue;
}
int greaterThanOrEqualComparison(float customerValue, float queryValue){
    return customerValue >= queryValue;
}

void parseCsvLine(char *tempCharPointer, customer *tempCustomerActivity){
    char *tempToken;
    int dataCounter = 0;
    unsigned int tempDay, tempMonth, tempYear;

        tempToken = strtok(tempCharPointer, ",");

        while (tempToken != NULL)
        {
            switch (dataCounter)
            {
            case firstname:
                tempCustomerActivity->firstname = (char*) realloc(tempCustomerActivity->firstname, strlen(tempToken));
                if(tempCustomerActivity->firstname == NULL){
                    printf("%s\n", "Error: realloc for 'first name' failed [parseCsvLine]");
                    return;
                }
                strcpy(tempCustomerActivity->firstname, tempToken);
                break;
            case lastname:
                tempCustomerActivity->lastname = (char*) realloc(tempCustomerActivity->lastname, strlen(tempToken));
                if(tempCustomerActivity->lastname == NULL){
                    printf("%s\n", "Error: realloc for 'last name' failed [parseCsvLine]");
                    return;
                }
                strcpy(tempCustomerActivity->lastname, tempToken);
                break;
            case id:
                tempCustomerActivity->id = atoi(tempToken);
                break;
            case phoneNum:
                strcpy(tempCustomerActivity->phoneNum, tempToken);            
                break;
            case debt:
                tempCustomerActivity->debt = atof(tempToken);            
                break;
            case purchaseDate:
                sscanf(tempToken, "%u/%u/%u", &tempDay, &tempMonth, &tempYear);
                tempCustomerActivity->purchaseDate.day = tempDay;
                tempCustomerActivity->purchaseDate.month = tempMonth;
                tempCustomerActivity->purchaseDate.year = tempYear;
                break;
            
            default:
                break;
            }
            dataCounter++;
            tempToken = strtok(NULL, ",");
        }
}

void deallocateLinkedList(myNode **listHead){
    while(*listHead != NULL){
        myNode *holder = *listHead;
        *listHead = (*listHead)->next;
        free(holder);
        holder = NULL;
    }
}

int findValueInArray(getEnumStr getfunc, int size, char *value){
    int i;
    if(value[strlen(value) - 1] == ' ')
        value[strlen(value) - 1] = '\0';
    if(*value == ' ')
        value++;
    for (i = 0; i < size; i++)
    {
        if (strcmp(value, getfunc(i)) == 0)
            return i;
    }
    return -1;
}
