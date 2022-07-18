#include "FinalProject_header.h"

char *titlesForPrint[] = {
    [firstname] = "First Name", 
    [lastname] = "Last Name", 
    [id] = "ID", 
    [phoneNum] = "Phone Number", 
    [debt] = "Debt", 
    [purchaseDate] = "Purchase Date"
};

int readCsvCreateList(FILE *filePointer, myNode **listHead){

    char tempCharPointer[1000];
    myNode *tempCustomerNode;
    customer *tempCustomerActivity;
    
    // "%[^\n]" == accept any character besides '\n'.
    // "%*c" == ignore next char (which is '\n').
    while(fscanf(filePointer, "%[^\n]%*c", tempCharPointer) !=EOF){
        tempCustomerActivity = (customer*) malloc(sizeof(customer));
        if(tempCustomerActivity == NULL){
            return 1;
        }
        parseCsvLine(tempCharPointer, tempCustomerActivity);
        tempCustomerNode = findCustomerInList(*listHead, tempCustomerActivity, id, equal);
        tempCustomerNode ? 
            addActivityToCustomer(tempCustomerNode, tempCustomerActivity) 
            : addCustomerToList(listHead, tempCustomerActivity);
    }

    printCustomerDetailsList(*listHead);
    deallocateLinkedList(listHead);
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
    float sum, newAmount;
    newAmount = customerActivity->debt;
    sum = customerNode->singleCustomer->debt + customerActivity->debt;
    customerNode->singleCustomer->debt = sum;
    if(newAmount * sum <= 0)
        customerNode->singleCustomer->purchaseDate = customerActivity->purchaseDate;
}

void addCustomerToList(myNode **listHead, customer *customerActivity){
    myNode *nodePtr, *nodePtr2, *newNode = (myNode*) malloc(sizeof(myNode));
    int i;
    if (newNode == NULL)
        return;
    newNode->singleCustomer = customerActivity;
    nodePtr2 = nodePtr = *listHead;

    if (*listHead == NULL)
    {
        *listHead = newNode;
        newNode->next = NULL;
        return;
    }

    while(nodePtr != NULL)
    {
        i = strcmp(nodePtr->singleCustomer->lastname, newNode->singleCustomer->lastname);
        if(i < 0)
            if(nodePtr->next != NULL){
                nodePtr2 = nodePtr;
                nodePtr = nodePtr->next;
            }
            else{
                nodePtr->next = newNode;
                newNode->next = NULL;
                break;
            }
        else{
            if(*listHead != nodePtr){
                newNode->next = nodePtr;
                nodePtr2->next = newNode;
            }
            else{
                newNode->next = nodePtr;
                *listHead = newNode;
            }
            break;
        }
    }
    printf("\n");
    printCustomerDetailsList(*listHead);
}

void printCustomerDetailsList(myNode *listHead){
    // mergeSortList(&listHead);
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

myNode *findCustomerInList(myNode *listHead, customer *customerActivity, dataNames findByType, filteringMethod filterBy){
    myNode *presNode = listHead;

    while (presNode != NULL)
    {
        switch (findByType)
        {
            case firstname:
                if (strcmp(presNode->singleCustomer->firstname, customerActivity->firstname) == 0)
                    return presNode;
            case lastname:
                if (strcmp(presNode->singleCustomer->lastname, customerActivity->lastname) == 0)
                    return presNode;
            case id:
                if (presNode->singleCustomer->id == customerActivity->id)
                    return presNode;
            case phoneNum:
                if (strcmp(presNode->singleCustomer->phoneNum, customerActivity->phoneNum) == 0)
                    return presNode;
            case debt:
            // add filterBy to find customer with debt greater than or equal to a certain amount.
                if (presNode->singleCustomer->debt == customerActivity->debt)
                    return presNode;
            case purchaseDate:
                if (presNode->singleCustomer->purchaseDate.day == customerActivity->purchaseDate.day &&
                    presNode->singleCustomer->purchaseDate.month == customerActivity->purchaseDate.month &&
                    presNode->singleCustomer->purchaseDate.year == customerActivity->purchaseDate.year)
                    return presNode;
        }
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