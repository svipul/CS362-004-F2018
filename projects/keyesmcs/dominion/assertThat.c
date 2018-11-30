#include <stdio.h>
#include "assertThat.h"

int assertThat(char * assertionText, int assertion, int testResult) {
    int assertionStatus = assertion == testResult;
    char * statusText = assertionStatus ? "SUCCEEDED" : "FAILED";
    
    printf("%s: %s\n", assertionText, statusText);

    return assertionStatus;
}
