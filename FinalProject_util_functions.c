#include "FinalProject_util_functions.h"
#include "FinalProject_data_types.h"

void mergeSortList(customerNode **listHead){
    customerNode *evenHead = NULL, *oddHead = NULL;

    if (*listHead == NULL || (*listHead)->next == NULL)
        return;

    splitList(listHead, &evenHead, &oddHead);
    mergeSortList(&evenHead);
    mergeSortList(&oddHead);
    mergeList(listHead, &evenHead, &oddHead);
}

void splitList(customerNode **listHead, customerNode **evenHead, customerNode **oddHead){
    customerNode *tempNode;
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
void mergeList(customerNode **listHead, customerNode **evenHead, customerNode **oddHead){
    customerNode *listTail = NULL, *tempNode;
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

void printCustomerDetailsList(customerNode **listHead){
    mergeSortList(listHead);
    customerNode *ptr = *listHead;
    while (ptr != NULL)
    {
        printf("\n%-11s %-9s %10u %12s %12.2f  %02u/%02u/%4u\n", 
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

customerNode* allocNewNode(){
    customerNode *newNode = (customerNode*)malloc(sizeof(customerNode));
    if (newNode == NULL)
    {
        printf("Error: Node memory allocation failed.\n");
        return NULL;
    }
    newNode->singleCustomer = allocNewCustomerActivity();
    if (newNode->singleCustomer == NULL)
    {
        free(newNode);
        printf("Error: Customer memory allocation failed.\n");
        return NULL;
    }
    newNode->next = NULL;
    return newNode;
}
customerActivity* allocNewCustomerActivity(){
    customerActivity *newCustomer = (customerActivity*)malloc(sizeof(customerActivity));
    if (newCustomer == NULL)
    {
        printf("Error: Customer memory allocation failed.\n");
        return NULL;
    }
    newCustomer->firstname = (char*)malloc(sizeof(char) * FIRST_NAME_LENGTH);
    newCustomer->lastname = (char*)malloc(sizeof(char) * LAST_NAME_LENGTH);
    if (newCustomer->firstname == NULL || newCustomer->lastname == NULL)
    {
        free(newCustomer->firstname);
        free(newCustomer->lastname);
        free(newCustomer);
        printf("Error: Customer name field memory allocation failed.\n");
        return NULL;
    }
    return newCustomer;
}

void copyCustomerDetails(customerActivity *source, customerActivity *destination){
    destination->id = source->id;
    strcpy(destination->firstname, source->firstname);
    strcpy(destination->lastname, source->lastname);
    strcpy(destination->phoneNum, source->phoneNum);
    destination->debt = source->debt;
    destination->purchaseDate.day = source->purchaseDate.day;
    destination->purchaseDate.month = source->purchaseDate.month;
    destination->purchaseDate.year = source->purchaseDate.year;
}

customerNode *findIfCustomerIsInList(customerNode *listHead, unsigned int customerId){

    customerNode *presNode = listHead;

    while (presNode != NULL && customerId != presNode->singleCustomer->id)
    {
        presNode = presNode->next;
    }
    return presNode;
}

void filterListForCustomers(customerNode *listHead, customerNode **newListHead, customerDataFields findByType, filteringMethod comparisonType, char *filteringValue){
    customerNode *presNode = listHead, *newNode;
    int result;

    while (presNode != NULL)
    {
        result = 0;
        result = getCustomerListFilter(findByType)(presNode->singleCustomer, comparisonType, filteringValue);
        if (result == 1){
            if (*newListHead == NULL)
            {
                *newListHead = allocNewNode();
                if (*newListHead == NULL){
                    return;
                }
                copyCustomerDetails(presNode->singleCustomer, (*newListHead)->singleCustomer);
                if(comparisonType == equal){
                    return;
                }
            }
            else
            {
                newNode = allocNewNode();
                if (newNode == NULL){
                    return;
                }
                copyCustomerDetails(presNode->singleCustomer, newNode->singleCustomer);
                newNode->next = *newListHead;
                *newListHead = newNode;
            }
        }
        presNode = presNode->next;
    }
}

void compareCustomerDetails(customerActivity *originalDetails, customerActivity *newDetails){
    int i;
    for(i = 0; i < NUM_OF_FIELDS_TO_COMPARE; i++){
        if(!getCustomerFieldComparators(i)(originalDetails, newDetails))
            printf("New %s value is different then original one.\n", getFieldNameStrings(i));
    }
}
int compareFirstName(customerActivity *originalDetails, customerActivity *newDetails){
    return !strcmp(originalDetails->firstname, newDetails->firstname);
}
int compareLastName(customerActivity *originalDetails, customerActivity *newDetails){
    return !strcmp(originalDetails->lastname, newDetails->lastname);
}
int compareId(customerActivity *originalDetails, customerActivity *newDetails){
    return originalDetails->id == newDetails->id;
}
int comparePhoneNumber(customerActivity *originalDetails, customerActivity *newDetails){
    return !strcmp(originalDetails->phoneNum, newDetails->phoneNum);
}

int filterByFirstName(customerActivity *customerActivity, filteringMethod comparisonType, char *firstName){
    return !strcmp(customerActivity->firstname, firstName); 
}
int filterByLastName(customerActivity *customerActivity, filteringMethod comparisonType, char *lastName){
    return !strcmp(customerActivity->lastname, lastName); 
}
int filterById(customerActivity *customerActivity, filteringMethod comparisonType, char *id){
    return customerActivity->id == atoi(id); 
}
int filterByPhoneNumber(customerActivity *customerActivity, filteringMethod comparisonType, char *phoneNumber){
    return !strcmp(customerActivity->phoneNum, phoneNumber); 
}
int filterByDebt(customerActivity *customerActivity, filteringMethod comparisonType, char *debt){
    return getComparisonFunction(comparisonType)(customerActivity->debt, strtof(debt, NULL)); 
}
int filterByPurchaseDate(customerActivity *customerActivity, filteringMethod comparisonType, char *purchaseDate){
    int day, month, year;
    sscanf(purchaseDate, "%02d/%02d/%04d", &day, &month, &year);
    int customersDate = parseDateToInt(customerActivity->purchaseDate.day, customerActivity->purchaseDate.month, customerActivity->purchaseDate.year);
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

int isValidFirstName(char *fieldValue){
    if(strlen(fieldValue) > FIRST_NAME_LENGTH - 1)
        fieldValue[FIRST_NAME_LENGTH -1] = '\0';
    return isAlphabetical(fieldValue);
}
int isValidLastName(char *fieldValue){
    if(strlen(fieldValue) > LAST_NAME_LENGTH - 1)
        fieldValue[LAST_NAME_LENGTH -1] = '\0';
    return isAlphabetical(fieldValue);
}
int isValidId(char *fieldValue){
    if(strlen(fieldValue) != 9 || strchr(fieldValue, '.') != NULL || strchr(fieldValue, '-') != NULL)
        return false;
    return isNumeric(fieldValue);
}
int isValidPhoneNumber(char *fieldValue){
    return isNumeric(fieldValue);
}
int isValidDebt(char *fieldValue){
    return isNumeric(fieldValue);
}
int isValidPurchaseDate(char *fieldValue){
    int day = 0, month = 0, year = 0;
    sscanf(fieldValue, "%d/%d/%d", &day, &month, &year);
    if(day > 0 && day <= 31 && month > 0 && month <= 12 && year > 0)
        return true;
    return false;
}
int isAlphabetical(char *fieldValue){
    while (*fieldValue != '\0'){
        if (!((*fieldValue >= 'a' && *fieldValue <= 'z') || (*fieldValue >= 'A' && *fieldValue <= 'Z') || *fieldValue == ' '))
            return false;
        fieldValue++;
    }
    return true;
}
int isNumeric(char *fieldValue){
    while (*fieldValue != '\0'){
        if (!((*fieldValue >= '0' && *fieldValue <= '9') || *fieldValue == '.' || *fieldValue == '-'))
            return false;
        fieldValue++;
    }
    return true;
}

void parseCsvLine(char *tempCharPointer, customerActivity *tempCustomerActivity){
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

void deallocateLinkedList(customerNode **listHead){
    while(*listHead != NULL){
        customerNode *holder = *listHead;
        *listHead = (*listHead)->next;
        free(holder->singleCustomer->firstname);
        free(holder->singleCustomer->lastname);
        free(holder->singleCustomer);
        free(holder);
        holder = NULL;
    }
}

int findValueInArray(getEnumStr getfunc, int size, char *value){
    int i;
    if(value == NULL)
        return -1;
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
