#include <stdio.h>
#include <stdlib.h>
#include "dominion_helpers.h"
#include "assertThat.h"
#include "unittest3.h"

struct gameState * updateCoinsMockGameState();

// test function signatures
#define TEST_COUNT 5
int copperIsWorthOne(struct gameState* mockGameState);
int silverIsWorthTwo(struct gameState* mockGameState);
int goldIsWorthThree(struct gameState* mockGameState);
int updateCoinsMathsRight(struct gameState* mockGameState);
int bonusIsAdded(struct gameState* mockGameState);

int unittest3() {
    struct gameState *mockGameState = updateCoinsMockGameState();

    int passingTests = 0;

    printf("Testing updateCoins:\n");
    
    passingTests += assertThat("updateCoins copper is worth one",
                               isTrue,
                               copperIsWorthOne(mockGameState));

    passingTests += assertThat("updateCoins silver is worth two",
                               isTrue,
                               silverIsWorthTwo(mockGameState));

    passingTests += assertThat("updateCoins gold is worth three",
                               isTrue,
                               goldIsWorthThree(mockGameState));

    passingTests += assertThat("updateCoins can count multiple coins "
                               "in a hand correctly",
                               isTrue,
                               updateCoinsMathsRight(mockGameState));

    passingTests += assertThat("updateCoins calculates a bonus correctly",
                               isTrue,
                               bonusIsAdded(mockGameState));

    printf("updateCoins: %i of %i passed\n\n", passingTests, TEST_COUNT);

    return passingTests == TEST_COUNT;
}

int copperIsWorthOne(struct gameState* mockGameState) {
    updateCoins(0, mockGameState, 0);
    return mockGameState->coins == 1;
}

int silverIsWorthTwo(struct gameState* mockGameState) {
    updateCoins(1, mockGameState, 0);
    return mockGameState->coins == 2;
}

int goldIsWorthThree(struct gameState* mockGameState) {
    updateCoins(2, mockGameState, 0);
    return mockGameState->coins == 3;
}


int updateCoinsMathsRight(struct gameState* mockGameState) {
    updateCoins(3, mockGameState, 0);
    return mockGameState->coins == 8;
}

int bonusIsAdded(struct gameState* mockGameState) {
    updateCoins(3, mockGameState, 0);
    int noBonusTotal = mockGameState->coins,
        bonusAmount = 7;
    
    updateCoins(3, mockGameState, bonusAmount);
    return noBonusTotal + bonusAmount == mockGameState->coins;
}

struct gameState * updateCoinsMockGameState() {
    struct gameState *mock = malloc(sizeof(struct gameState));

    mock->handCount[0] = 1;
    mock->hand[0][0] = copper;

    mock->handCount[1] = 1;
    mock->hand[1][0] = silver;

    mock->handCount[2] = 1;
    mock->hand[2][0] = gold;

    mock->handCount[3] = 5;
    mock->hand[3][0] = copper;
    mock->hand[3][1] = copper;
    mock->hand[3][2] = gold;
    mock->hand[3][3] = silver;
    mock->hand[3][4] = copper;

    return mock;
}
