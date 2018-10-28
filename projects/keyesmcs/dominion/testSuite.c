#include <stdio.h>
#include "unittest1.h"
#include "unittest2.h"
#include "unittest3.h"
#include "unittest4.h"
#include "cardtest1.h"
#include "cardtest2.h"
#include "cardtest3.h"
#include "cardtest4.h"

#define DOMINION_C_TEST_COUNT 4
#define CARD_TEST_COUNT 4

int main() {
    int passingTests = 0;

    printf("Running tests on dominion.c:\n\n");

    passingTests += unittest1();
    passingTests += unittest2();
    passingTests += unittest3();
    passingTests += unittest4();

    printf("dominion.c tests: %i of %i passed\n\n", passingTests,
            DOMINION_C_TEST_COUNT);

    passingTests = 0;

    passingTests += cardtest1();
    passingTests += cardtest2();
    passingTests += cardtest3();
    passingTests += cardtest4();

    printf("card tests: %i of %i passed\n\n", passingTests, 
            CARD_TEST_COUNT);
}
