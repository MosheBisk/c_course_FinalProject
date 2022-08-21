#include "FinalProject_data_types.h"
// #include "FinalProject_data_types.c"
#include "FinalProject_functions.h"
#include "FinalProject_util_functions.h"

void createOrAddToList(myNode **listHead, customer *singleCustomerActivity){
    char idAsStrHolder[10];
    myNode *tempCustomerNode;

    sprintf(idAsStrHolder, "%d", singleCustomerActivity->id);
    tempCustomerNode = findCustomerInList(*listHead, NULL, id, equal, idAsStrHolder);
    tempCustomerNode ? 
        addActivityToCustomer(tempCustomerNode, singleCustomerActivity) 
        : addCustomerToList(listHead, singleCustomerActivity);
}

int readCsv(FILE *filePointer, myNode **listHead){

    char tempCharPointer[MAX_LINE_LENGTH];
    customer *tempCustomerActivity;
    
    // "%[^\n]" == accept any character besides '\n'.
    // "%*c" == ignore next char (which is '\n').
    while(fscanf(filePointer, "%[^\n]%*c", tempCharPointer) !=EOF){
        tempCustomerActivity = (customer*) malloc(sizeof(customer));
        if(tempCustomerActivity == NULL){
            return 1;
        }
        parseCsvLine(tempCharPointer, tempCustomerActivity);
        createOrAddToList(listHead, tempCustomerActivity);
    }

    // mergeSortList(listHead);
    // printCustomerDetailsList(*listHead);
    // free(tempCustomerActivity);
    // tempCustomerActivity = NULL;
    return 0;
}

void addActivityToCustomer(myNode *customerNode, customer *customerActivity){
    float sum, newAmount;
    int currentDate, newDate;
    currentDate = parseDateToInt(customerNode->singleCustomer->purchaseDate.day, customerNode->singleCustomer->purchaseDate.month, customerNode->singleCustomer->purchaseDate.year);
    newDate = parseDateToInt(customerActivity->purchaseDate.day, customerActivity->purchaseDate.month, customerActivity->purchaseDate.year);
    newAmount = customerActivity->debt;
    sum = customerNode->singleCustomer->debt + customerActivity->debt;
    customerNode->singleCustomer->debt = sum;
    if(newDate < currentDate || newAmount * sum <= 0)
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
    char userInput[MAX_USER_INPUT], *tempInput; 
    char *queryTypeToken, *valueToken;//, *fieldTypeToken
    queryTypes queryType;

    while(1){
        printf("\n%s\n", PRE_QUERY_PRINT);
        fgets(userInput, MAX_USER_INPUT, stdin); // check for \n
        if (!strchr(userInput, '\n'))
        {
            printf("%s\n", "Error: input too long");
            while ((getchar()) != '\n');
        } else {
            userInput[strlen(userInput) - 1] = '\0';
        }
        
        tempInput = (char*) malloc(sizeof(char) * strlen(userInput) + 1);
        if (tempInput == NULL){
            printf("%s\n", "Error: malloc failed");
            continue;
            // return;
        }
        strcpy(tempInput, userInput);
        queryTypeToken = strtok(tempInput, " ");
        // fieldTypeToken = strtok(NULL, "=");
        valueToken = strtok(NULL, "\n");
        // printf("%s/%s/%s \n", queryTypeToken, fieldTypeToken, valueToken);

        queryType = findValueInArray(getQueryString, QUERY_STRINGS_SIZE, queryTypeToken);
        printf("%d queryType\n", queryType);
        if (queryType < 0){
            printf("Error: invalid query type\n");
            continue;
            // return;
        }
        switch (queryType)
        {
            case _select:
                filterCustomersListByQuery(listHead, valueToken);
                break;
            case set:
                insertNewCustomerActivity(listHead, valueToken);
                break;
            case print:
                printCustomerDetailsList(*listHead);
                break;
            case quit:
                printf("%s\n", "Exiting...");
                return;
            default:
                printf("%s\n", "Invalid query. Please try again.");
                break;
        }
        free(tempInput);
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
    printf("fieldType: %d\n", fieldType);
    filterBy = findValueInArray(getComparisonTypeString, FILTERING_METHOD_SIZE, comparisonOperator);
    
    customerNode = findCustomerInList(*listHead, newListHead, fieldType, filterBy, filteringValue);
    if(customerNode != NULL)
        printf("firstname: %s\n", customerNode->singleCustomer->firstname);
    printCustomerDetailsList(customerNode);
    deallocateLinkedList(&newListHead);
}

void insertNewCustomerActivity(myNode **listHead, char *activityInfo){
    char activityInfoCopy[strlen(activityInfo) + 1], comparisonOperator[3], 
        fieldTypeSegment[strlen(activityInfo)+1], segmentValue[strlen(activityInfo)+1], 
        *fieldTypeToken, delimiter = ',', *newCustomerFields[6];
    int fieldType, i, numOfFields = 0;
    // customerDataFields fieldType;
    FILE *customerActivityFile = fopen(CSV_FILE_NAME, "a");
    customer *newCustomerActivity = NULL;
    newCustomerActivity = (customer*) malloc(sizeof(customer));

    strcpy(activityInfoCopy, activityInfo);
    fieldTypeToken = strtok(activityInfoCopy, &delimiter);
    do
    {
        sscanf(fieldTypeToken, "%[a-zA-z ] %[=] %[a-zA-z0-9/- ]", fieldTypeSegment, comparisonOperator, segmentValue);
        fieldType = findValueInArray(getFieldNameStrings, FIELD_TYPE_SIZE, fieldTypeSegment);
        if(fieldType < 0){
            printf("Error: invalid field type '%s'\n", fieldTypeSegment);
            return;
        } else {
            newCustomerFields[fieldType] = (char*) malloc(sizeof(char) * strlen(segmentValue) + 1);
            strcpy(newCustomerFields[fieldType], segmentValue);
        }
        printf("fieldType:: %d\n", fieldType);
        fieldTypeToken = strtok(NULL, &delimiter);
        numOfFields++;
    } while (fieldTypeToken != NULL);
    if(numOfFields != FIELD_TYPE_SIZE){
        printf("Error: invalid number of fields\n");
        return;
    }
    strcpy(activityInfoCopy, "");
    snprintf(activityInfoCopy, strlen(activityInfo) + 1, "%s,%s,%s,%s,%s,%s", newCustomerFields[0], newCustomerFields[1], newCustomerFields[2], newCustomerFields[3], newCustomerFields[4], newCustomerFields[5]);
    fprintf(customerActivityFile, "\n%s", activityInfoCopy);
    // fprintf(customerActivityFile, "%s,%s,%s,%s,%s,%s\n", newCustomerFields[0], newCustomerFields[1], newCustomerFields[2], newCustomerFields[3], newCustomerFields[4], newCustomerFields[5]);
    fclose(customerActivityFile);
    for(i=0; i<FIELD_TYPE_SIZE; i++){
        // strcat(activityInfoCopy, newCustomerFields[i]);
        free(newCustomerFields[i]);
    }
    parseCsvLine(activityInfoCopy, newCustomerActivity);
    createOrAddToList(listHead, newCustomerActivity);


    // customerNode = findCustomerInList(*listHead, newListHead, fieldType, filterBy, filteringValue);
    // if(customerNode != NULL)
    //     printf("firstname: %s\n", customerNode->singleCustomer->firstname);
    // printCustomerDetailsList(customerNode);
    // deallocateLinkedList(&newListHead);
}
