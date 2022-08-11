#include "FinalProject_data_types.h"
// #include "FinalProject_data_types.c"
#include "FinalProject_functions.h"
#include "FinalProject_util_functions.h"

int readCsvCreateList(FILE *filePointer, myNode **listHead){

    char tempCharPointer[MAX_LINE_LENGTH], idAsStrHolder[10];
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
        sprintf(idAsStrHolder, "%d", tempCustomerActivity->id);
        tempCustomerNode = findCustomerInList(*listHead, NULL, id, equal, idAsStrHolder);
        tempCustomerNode ? 
            addActivityToCustomer(tempCustomerNode, tempCustomerActivity) 
            : addCustomerToList(listHead, tempCustomerActivity);
    }

    mergeSortList(listHead);
    // printCustomerDetailsList(*listHead);
    // free(tempCustomerActivity);
    // tempCustomerActivity = NULL;
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
    if (newNode == NULL){
        printf("%s\n", "Error: malloc failed");
        return;
    }
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
    // printf("\n");
    // printCustomerDetailsList(*listHead);
}

void manageUserInput(myNode **listHead){
    char intialPrint[] = "Please enter a command: select for searching, set for adding, quit for exiting.\n---> ";
    char userInput[MAX_USER_INPUT], *tempInput; 
    char *queryTypeToken, *valueToken;//, *fieldTypeToken
    queryTypes queryType;


    printf("%s\n", intialPrint);
    fgets(userInput, MAX_USER_INPUT, stdin); // check for \n
    userInput[strlen(userInput) - 1] = '\0';
    tempInput = (char*) malloc(sizeof(char) * strlen(userInput) + 1);
    strcpy(tempInput, userInput);
    queryTypeToken = strtok(tempInput, " ");
    // fieldTypeToken = strtok(NULL, "=");
    valueToken = strtok(NULL, "\n");
    // printf("%s/%s/%s \n", queryTypeToken, fieldTypeToken, valueToken);

    queryType = findValueInArray(getQueryString, QUERY_STRINGS_SIZE, queryTypeToken);
    // queryType = findValueInArray(queryStrings, QUERY_STRINGS_SIZE, queryTypeToken);
    printf("queryType:: %d\n", queryType);
    switch (queryType)
    {
        case _select:
            filterCustomersListByQuery(listHead, valueToken);
            break;
        case set:
            // setQuery(*listHead, valueToken);
            break;
        case quit:
            printf("%s\n", "Exiting...");
            exit(0);
            break;
        default:
            printf("%s\n", "Invalid query. Please try again.");
            break;
    }

    
}

void filterCustomersListByQuery(myNode **listHead, char *query){
    char filterByField[strlen(query) + 1], comparisonOperator[3], filteringValue[strlen(query) + 1];
    myNode *customerNode = NULL, *newListHead = NULL;
    customerDataFields fieldType;
    filteringMethod filterBy;
    sscanf(query, "%[a-zA-z ] %[=<>] %[^\n]", filterByField, comparisonOperator, filteringValue);
    printf("%s/%s/%s \n", filterByField, comparisonOperator, filteringValue);
    fieldType = findValueInArray(getFieldNameStrings, FIELD_TYPE_SIZE, filterByField);
    // fieldType = findCustomerField(filterByField);
    printf("fieldType: %d\n", fieldType);
    filterBy = findValueInArray(getComparisonTypeString, FILTERING_METHOD_SIZE, comparisonOperator);
    
    customerNode = findCustomerInList(*listHead, newListHead, fieldType, filterBy, filteringValue);
    if(customerNode != NULL)
        printf("firstname: %s\n", customerNode->singleCustomer->firstname);
    printCustomerDetailsList(customerNode);
    deallocateLinkedList(&newListHead);
}
