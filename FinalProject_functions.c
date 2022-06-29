#include "FinalProject_header.h"

void readAndPrintCsv(FILE *filePointer){
    char tempCharPointer[10000];
    while(fscanf(filePointer, "%[^\n]%*c", tempCharPointer) !=EOF){
        printf("%s\n", tempCharPointer);
    }
}

int readAndPrintCsvSum(FILE *filePointer){

    char tempCharPointer[1000];
    myNode *head = NULL, *tempCustomerNode;
    customer *tempCustomerActivity;
    
    // "%[^\n]" == accept any character besides '\n'.
    // "%*c" == ignore next char (which is '\n').
    while(fscanf(filePointer, "%[^\n]%*c", tempCharPointer) !=EOF){
        tempCustomerActivity = (customer*) malloc(sizeof(customer));
        parseCsvLine(tempCharPointer, tempCustomerActivity);
        tempCustomerNode = findCustomerInList(head, tempCustomerActivity->id);
        tempCustomerNode ? 
            addActivityToCustomer(tempCustomerNode, tempCustomerActivity) 
            : addCustomerToList(&head, tempCustomerActivity);
    }

    printCustomerDetailsList(head);
    deallocateLinkedList(&head);
    free(tempCustomerActivity);
    return 0;
}

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
        if ((*evenHead)->singleCustomer->debt >= (*oddHead)->singleCustomer->debt)
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

void addActivityToCustomer(myNode *customerNode, customer *customerActivity){
    customerNode->singleCustomer->debt += customerActivity->debt;
}

void addCustomerToList(myNode **listHead, customer *customerActivity){
    myNode *newNode = (myNode*) malloc(sizeof(myNode));
    if (newNode == NULL)
        return;
        
    newNode->singleCustomer = customerActivity;
    newNode->next = *listHead;
    *listHead = newNode;
}

void printCustomerDetailsList(myNode *listHead){
    mergeSortList(&listHead);
    myNode *ptr = listHead;
    while (ptr != NULL)
    {
        printf("%-11s %-9s %10u %12s %12.2f %5u/%02u/%4u\n", 
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

myNode *findCustomerInList(myNode *listHead, unsigned int customerId){
    myNode *presNode = listHead;

    while (presNode != NULL && customerId != presNode->singleCustomer->id)
    {
        presNode = presNode->next;
    }
    return presNode;
}

void parseCsvLine(char *tempCharPointer, customer *tempCustomerActivity){
    char *tempToken;
    int dataCounter = 0;
    unsigned int tempDay, tempMonth, tempYear;

        tempToken = strtok(tempCharPointer, ",");

        while (tempToken != NULL)
        {
        // printf("tempToken: %s\n", tempToken);
            switch (dataCounter)
            {
            case firstname:
                tempCustomerActivity->firstname = (char*) realloc(tempCustomerActivity->firstname, strlen(tempToken));
                strcpy(tempCustomerActivity->firstname, tempToken);
                break;
            case lastname:
                tempCustomerActivity->lastname = (char*) realloc(tempCustomerActivity->lastname, strlen(tempToken));
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

        // printf("tempCustomerNode: %s,%s,%u,%s,%.2f,%u/%u/%u\n", 
        //         tempCustomerActivity->firstname, 
        //         tempCustomerActivity->lastname, 
        //         tempCustomerActivity->id, 
        //         tempCustomerActivity->phoneNum, 
        //         tempCustomerActivity->debt, 
        //         tempCustomerActivity->purchaseDate.day, 
        //         tempCustomerActivity->purchaseDate.month, 
        //         tempCustomerActivity->purchaseDate.year);
}

void deallocateLinkedList(myNode **listHead){
    while(*listHead != NULL){
        myNode *holder = *listHead;
        *listHead = (*listHead)->next;
        free(holder);
    }
}
