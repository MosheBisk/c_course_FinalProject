#include "FinalProject_data_types.h"
#include "FinalProject_functions.h"
#include "FinalProject_util_functions.h"

int main () {
    FILE *filePointer;
    customerNode **listHead = (customerNode **)malloc(sizeof(customerNode *));
    *listHead = NULL;

    filePointer = fopen(CSV_FILE_NAME, "r+t");
    if (filePointer == NULL)
        return -1;

    readCsv(filePointer, listHead);
    printCustomerDetailsList(listHead);
    manageUserInput(listHead);

    deallocateLinkedList(listHead);
    fclose(filePointer);
    return 0;
}

