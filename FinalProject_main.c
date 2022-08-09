#include "FinalProject_data_types.h"
#include "FinalProject_functions.h"
#include "FinalProject_util_functions.h"

int main () {
    FILE *filePointer;
    myNode *listHead = NULL;

    filePointer = fopen("demoCsv1.csv", "r+t");
    if (filePointer == NULL)
        return 1;

    readCsvCreateList(filePointer, &listHead);
    printCustomerDetailsList(listHead);
    manageUserInput(&listHead);

    deallocateLinkedList(&listHead);
    fclose(filePointer);
    return 0;
}

