#include "FinalProject_header.h"

int main () {
    FILE *filePointer;
    myNode *listHead = NULL;

    filePointer = fopen("demoCsv1.csv", "r+t");
    if (filePointer == NULL)
        return 1;

    readCsvCreateList(filePointer, &listHead);
    

    fclose(filePointer);
    return 0;
}

