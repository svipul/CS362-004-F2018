#include <stdio.h>
#include <stdlib.h>
#include "dominion_helpers.h"
#include "assertThat.h"
#include "cardtest3.h"

struct gameState * mineMockGameState();
void resetMineMockState(struct gameState *mockGameState);

// test function signatures

#define TEST_COUNT 3
int copperBuysSilver(struct gameState *mockGameState);
int silverBuysGold(struct gameState *mockGameState);
int doNotBuyIfNoCoinAvailable(struct gameState *mockGameState);

int cardtest3() {
    struct gameState *mockGameState = mineMockGameState();

    int passingTests = 0;

    printf("Testing mine card:\n");

    passingTests += assertThat("mine card buys sliver with copper",
                               isTrue,
                               copperBuysSilver(mockGameState));

    passingTests += assertThat("mine card buys gold with silver",
                               isTrue,
                               silverBuysGold(mockGameState));

    passingTests += assertThat("mine card does not upgrade coin if "
                               "upgraded card is unavailable",
                               isTrue,
                               doNotBuyIfNoCoinAvailable(mockGameState));

    printf("smithy card: %i of %i passed\n\n", passingTests,
            TEST_COUNT);

    return passingTests == TEST_COUNT;
}

int copperBuysSilver(struct gameState *mockGameState) {
    resetMineMockState(mockGameState);

    cardEffect(mine, 1, 0, 0, mockGameState, 0, 0);

    return mockGameState->hand[0][0] == silver;
}

int silverBuysGold(struct gameState *mockGameState) {
    resetMineMockState(mockGameState);

    mockGameState->hand[0][1] = silver;

    cardEffect(mine, 1, 0, 0, mockGameState, 0, 0);

    return mockGameState->hand[0][0] == gold;
}

int doNotBuyIfNoCoinAvailable(struct gameState *mockGameState) {
    resetMineMockState(mockGameState);

    mockGameState->supplyCount[silver] = 0;

    cardEffect(mine, 1, 0, 0, mockGameState, 0, 0);

    return mockGameState->hand[0][0] != silver;
}

void resetMineMockState(struct gameState * mockGameState) {
    mockGameState->whoseTurn = 0;

    mockGameState->hand[0][0] = mine;
    mockGameState->hand[0][1] = copper;
    mockGameState->handCount[0] = 2;
    
    mockGameState->supplyCount[copper] = 10;
    mockGameState->supplyCount[silver] = 10;
    mockGameState->supplyCount[gold] = 10;
}

struct gameState * mineMockGameState() {
    struct gameState *mock = malloc(sizeof(struct gameState));
    
    return mock;
}
