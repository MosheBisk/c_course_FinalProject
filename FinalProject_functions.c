#include "FinalProject_header.h"

void readAndPrintCsv(FILE *filePointer){
    char tempCharPointer[10000];
    
    while(fscanf(filePointer, "%[^\n]%*c", tempCharPointer) !=EOF){
        printf("%s\n", tempCharPointer);
    }
}

int readAndPrintCsvSum(FILE *filePointer){

    char tempCharPointer[1000];
    Node *head = NULL, *tempNext = head, *tempCustomerNode;
    customer *tempCustomerActivity;
    
    // "%[^\n]" == accept any character besides '\n'.
    // "%*c" == ignore next char (which is '\n').
    while(fscanf(filePointer, "%[^\n]%*c", tempCharPointer) !=EOF){
        tempCustomerActivity = (customer*) malloc(sizeof(customer));
        tempCustomerNode = (Node*) malloc(sizeof(Node));
        parseCsvLine(tempCharPointer, tempCustomerActivity);
        tempCustomerNode->singleActivity = *tempCustomerActivity;
        free(tempCustomerActivity);
        free(tempCustomerNode);
    }

    return 0;
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

        printf("tempCustomerNode: %s,%s,%u,%s,%.2f,%u/%u/%u\n", 
                tempCustomerActivity->firstname, 
                tempCustomerActivity->lastname, 
                tempCustomerActivity->id, 
                tempCustomerActivity->phoneNum, 
                tempCustomerActivity->debt, 
                tempCustomerActivity->purchaseDate.day, 
                tempCustomerActivity->purchaseDate.month, 
                tempCustomerActivity->purchaseDate.year);
}

