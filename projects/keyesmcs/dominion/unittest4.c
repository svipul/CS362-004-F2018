#include <stdio.h>
#include <stdlib.h>
#include "assertThat.h"
#include "unittest4.h"
#include "dominion.h"


struct gameState * isGameOverMockGameState();
void resetSupply(struct gameState *mockGameState);

// test function signatures

#define TEST_COUNT 5
int gameIsNotOverIfNoEmptySupply(struct gameState *mockGameState);
int gameIsNotOverIfOneEmptySupply(struct gameState *mockGameState);
int gameIsNotOverIfTwoEmptySupply(struct gameState *mockGameState);
int gameIsOverIfThreeEmptySupply(struct gameState *mockGameState);
int gameIsOverIfNoProvinceCards(struct gameState *mockGameState);

int unittest4() {
    struct gameState *mockGameState = isGameOverMockGameState();

    int passingTests = 0;

    printf("Testing isGameOver:\n");

    passingTests += assertThat("isGameOver returns false if no supply "
                               "piles are empty",
                               isTrue,
                               gameIsNotOverIfNoEmptySupply(mockGameState));

    passingTests += assertThat("isGameOver returns false if there's one "
                               "empty supply pile", 
                               isTrue,
                              gameIsNotOverIfOneEmptySupply(mockGameState));

    passingTests += assertThat("isGameOver returns false if there are two "
                               "empty supply piles",
                               isTrue,
                              gameIsNotOverIfTwoEmptySupply(mockGameState));

    passingTests += assertThat("isGameOver returns true if there are three "
                               "empty supply piles",
                               isTrue,
                               gameIsOverIfThreeEmptySupply(mockGameState));

    passingTests += assertThat("isGameOver returns true if the province "
                               "supply pile is empty",
                               isTrue,
                               gameIsOverIfNoProvinceCards(mockGameState));

    printf("isGameOver: %i of %i passed\n\n", passingTests, TEST_COUNT);

    return passingTests == TEST_COUNT;
}

int gameIsNotOverIfNoEmptySupply(struct gameState *mockGameState) {
    resetSupply(mockGameState);

    return !isGameOver(mockGameState);
}

int gameIsNotOverIfOneEmptySupply(struct gameState *mockGameState) {
    resetSupply(mockGameState);

    mockGameState->supplyCount[adventurer] = 0;

    return !isGameOver(mockGameState);
}

int gameIsNotOverIfTwoEmptySupply(struct gameState *mockGameState) {
    resetSupply(mockGameState);

    mockGameState->supplyCount[adventurer] = 0;
    mockGameState->supplyCount[council_room] = 0;

    return !isGameOver(mockGameState);
}

int gameIsOverIfThreeEmptySupply(struct gameState *mockGameState) {
    resetSupply(mockGameState);

    mockGameState->supplyCount[adventurer] = 0;
    mockGameState->supplyCount[council_room] = 0;
    mockGameState->supplyCount[feast] = 0;

    return isGameOver(mockGameState);
}

int gameIsOverIfNoProvinceCards(struct gameState *mockGameState) {
    resetSupply(mockGameState);

    mockGameState->supplyCount[province] = 0;

    return isGameOver(mockGameState);
}



void resetSupply(struct gameState *mockGameState) {
    int i;

    for (i = 0; i < treasure_map; i++) {
        if (i < 16) {
            mockGameState->supplyCount[i] = 10;
        } else {
            mockGameState->supplyCount[i] = -1;
        }
    }
}

struct gameState * isGameOverMockGameState() {
    struct gameState *mock = malloc(sizeof(struct gameState));

    return mock;
}
