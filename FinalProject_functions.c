#include "FinalProject_data_types.h"
#include "FinalProject_functions.h"
#include "FinalProject_util_functions.h"

void createOrAddToList(customerNode **listHead, customerActivity *singleCustomerActivity, bool isNewActivity){
    customerNode *tempCustomerNode;

    // If the list is empty, create a new node and add it to the list
    if((*listHead)==NULL){
        *listHead = allocNewNode();
        (*listHead)->singleCustomer = singleCustomerActivity;
        (*listHead)->next = NULL;
        return;
    }

    // If the list is not empty, search for the customer in the list
    // If found, add activity to customer, else add new node to list
    tempCustomerNode = findIfCustomerIsInList(*listHead, singleCustomerActivity->id);
    if(tempCustomerNode){
        if(isNewActivity)
            compareCustomerDetails(tempCustomerNode->singleCustomer, singleCustomerActivity);
        addActivityToCustomer(tempCustomerNode, singleCustomerActivity);
    } else {
        addCustomerToList(listHead, singleCustomerActivity);
    }
}

int readCsv(FILE *filePointer, customerNode **listHead){

    char newLineContainer[MAX_LINE_LENGTH];
    customerActivity *newCustomerActivity;
    
    
    // "%[^\n]" == accept any character besides '\n'.
    // "%*c" == ignore next char (which is '\n').
    while(fscanf(filePointer, "%[^\n]%*c", newLineContainer) !=EOF){
        newCustomerActivity = allocNewCustomerActivity();
        if(newCustomerActivity == NULL){
            return 1;
        }
        parseCsvLine(newLineContainer, newCustomerActivity);
        createOrAddToList(listHead, newCustomerActivity, false);
    }
    return 0;
}

void addActivityToCustomer(customerNode *customerNode, customerActivity *customerActivity){
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

void addCustomerToList(customerNode **listHead, customerActivity *customerActivity){

    customerNode *newNode = allocNewNode();
    if (newNode == NULL)
        return;
    
    newNode->singleCustomer = customerActivity;
    newNode->next = *listHead;
    *listHead = newNode;
}

void manageUserInput(customerNode **listHead){
    char userInput[MAX_USER_INPUT]; 
    char *queryTypeToken, *valueToken;
    queryTypes queryType;

    while(1){
        printf("\n%s\n", PRE_QUERY_PRINT);
        fgets(userInput, MAX_USER_INPUT, stdin); 
        if (!strchr(userInput, '\n'))
        {
            printf("%s\n", "Error: input too long");
            while ((getchar()) != '\n');
            continue;
        } 
        // else {
        //     userInput[strlen(userInput) - 1] = '\0';
        // }
        
        queryTypeToken = strtok(userInput, " ");
        valueToken = strtok(NULL, "\n");

        queryType = findValueInArray(getQueryString, QUERY_STRINGS_SIZE, queryTypeToken);
        if (queryType < 0){
            printf("Error: invalid query type\n");
            continue;
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
                printCustomerDetailsList(listHead);
                break;
            case quit:
                printf("%s\n", "Exiting...");
                return;
            default:
                printf("%s\n", "Invalid query. Please try again.");
                break;
        }
    }
}

void filterCustomersListByQuery(customerNode **listHead, char *query){
    char filterByField[strlen(query) + 1], comparisonOperator[3], filteringValue[strlen(query) + 1];
    customerNode **newListHead;
    customerDataFields fieldType;
    filteringMethod filterBy;
    newListHead = (customerNode **)malloc(sizeof(customerNode *));
    *newListHead = NULL;
    sscanf(query, "%[a-zA-z ] %[=<>] %[^\n]", filterByField, comparisonOperator, filteringValue);
    fieldType = findValueInArray(getFieldNameStrings, FIELD_TYPE_SIZE, filterByField);
    filterBy = findValueInArray(getComparisonTypeString, FILTERING_METHOD_SIZE, comparisonOperator);
    
    filterListForCustomers(*listHead, newListHead, fieldType, filterBy, filteringValue);
    printCustomerDetailsList(newListHead);
    deallocateLinkedList(newListHead);
}

void insertNewCustomerActivity(customerNode **listHead, char *activityInfo){
    char activityInfoCopy[strlen(activityInfo) + 1], 
        comparisonOperator[3], 
        fieldTypeSegment[strlen(activityInfo)+1], 
        segmentValue[strlen(activityInfo)+1], 
        *fieldTypeToken, 
        delimiter = ',', 
        *newCustomerFields[6];

    int fieldType, i, numOfFields = 0;

    FILE *customerActivityFile = fopen(CSV_FILE_NAME, "a");

    customerActivity *newCustomerActivity;
    
    newCustomerActivity = allocNewCustomerActivity();
    if (newCustomerActivity == NULL){
        return;
    }

    strcpy(activityInfoCopy, activityInfo);
    fieldTypeToken = strtok(activityInfoCopy, &delimiter);
    do
    {
        sscanf(fieldTypeToken, "%[a-zA-z ] %[=] %[a-zA-z0-9./- ]", fieldTypeSegment, comparisonOperator, segmentValue);
        fieldType = findValueInArray(getFieldNameStrings, FIELD_TYPE_SIZE, fieldTypeSegment);
        if(fieldType < 0){
            printf("Error: invalid field type '%s'\n", fieldTypeSegment);
            return;
        } else if(getFieldValueValidater(fieldType)(segmentValue)){
            newCustomerFields[fieldType] = (char*) malloc(sizeof(char) * strlen(segmentValue) + 1);
            strcpy(newCustomerFields[fieldType], segmentValue);
        } else{
            printf("'%s' is not a valid value for field type '%s'\n", segmentValue, fieldTypeSegment);
            return;
        }
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
    fclose(customerActivityFile);
    for(i=0; i<FIELD_TYPE_SIZE; i++){
        free(newCustomerFields[i]);
    }
    parseCsvLine(activityInfoCopy, newCustomerActivity);
    createOrAddToList(listHead, newCustomerActivity, true);
}
