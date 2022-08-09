#include "FinalProject_data_types.h"
// #include "FinalProject_data_types.c"
#include "FinalProject_functions.h"
#include "FinalProject_util_functions.h"

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

