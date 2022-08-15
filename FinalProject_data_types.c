#include "FinalProject_data_types.h"
#include "FinalProject_util_functions.h"


char *fieldNameStrings[] = {
    [firstname] = "first name", 
    [lastname] = "last name", 
    [id] = "id", 
    [phoneNum] = "phone", 
    [debt] = "debt", 
    [purchaseDate] = "purchase date"
};
char *getFieldNameStrings(int field){
    return fieldNameStrings[field];
}

char *queryStrings[] = {
    [_select] = "select", 
    [set] = "set", 
    [print] = "print",
    [quit] = "quit"
};
char *getQueryString(int queryType){
    return queryStrings[queryType];
}

char *comparisonTypesStrings[] = {
    [equal] = "=", 
    [less] = "<", 
    [greater] = ">", 
    [lessEqual] = "<=", 
    [greaterEqual] = ">="
};
char *getComparisonTypeString(int comparisonType){
    return comparisonTypesStrings[comparisonType];
}

filterCustomerList customerListFiltersArray[] = {
    [firstname] = filterByFirstName,
    [lastname] = filterByLastName,
    [id] = filterById,
    [phoneNum] = filterByPhoneNumber,
    [debt] = filterByDebt,
    [purchaseDate] = filterByPurchaseDate
};
filterCustomerList getCustomerListFilter(customerDataFields field){
    return customerListFiltersArray[field];
}

comparisonFunctions comparisonFunctionsArray[] = {
    [equal] = equalComparison,
    [less] = lessThanComparison,
    [greater] = greaterThanComparison,
    [lessEqual] = lessThanOrEqualComparison,
    [greaterEqual] = greaterThanOrEqualComparison
};
comparisonFunctions getComparisonFunction(filteringMethod comparisonType){
    return comparisonFunctionsArray[comparisonType];
}
