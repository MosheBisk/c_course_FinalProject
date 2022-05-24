#include "FinalProject_header.h"

int main () {
    FILE *filePointer;

    filePointer = fopen("demoCsv1.csv", "r+t");
    if (filePointer == NULL)
        return 1;

    // readAndPrintCsv(filePointer);
    readAndPrintCsvSum(filePointer);
    
    fclose(filePointer);
    return 0;
}

