#include <stdio.h>
#include <stdlib.h>
#include "dominion_helpers.h"
#include "assertThat.h"
#include "cardtest2.h"

#define INITIAL_PILE_SIZE 10

struct gameState * smithyMockGameState();
void resetSmithyMockState(struct gameState *mockGameState);

// test function signatures

#define TEST_COUNT 2
int shufflesDeckIfHandLow(struct gameState *mockGameState);
int increasesHandByThree(struct gameState *mockGameState);

int cardtest2() {
    struct gameState *mockGameState = smithyMockGameState();

    int passingTests = 0;

    printf("Testing smithy card:\n");

    passingTests += assertThat("smithy card increases hand by three",
                               isTrue,
                               increasesHandByThree(mockGameState));

    passingTests += assertThat("smithy card shuffles the deck if it "
                               "can't draw at least three cards",
                               isTrue,
                               shufflesDeckIfHandLow(mockGameState));

    printf("smithy card: %i of %i passed\n\n", passingTests,
            TEST_COUNT);

    return passingTests == TEST_COUNT;
}

int shufflesDeckIfHandLow(struct gameState *mockGameState) {
    resetSmithyMockState(mockGameState);
    
    // set deckCount to 2, so the game has to shuffle
    mockGameState->deckCount[0] = 2;

    cardEffect(smithy, 0, 0, 0, mockGameState, 0, 0);

    
    return mockGameState->discardCount[0] != INITIAL_PILE_SIZE;
}

int increasesHandByThree(struct gameState *mockGameState) {
    resetSmithyMockState(mockGameState);

    cardEffect(smithy, 0, 0, 0, mockGameState, 0, 0);

    return mockGameState->handCount[mockGameState->whoseTurn] == 3;
}


void resetSmithyMockState(struct gameState * mockGameState) {
    int i;

    mockGameState->whoseTurn = 0;

    mockGameState->hand[0][0] = adventurer;
    mockGameState->handCount[0] = 1;

    for (i = 0; i < INITIAL_PILE_SIZE; i++) {
        mockGameState->deck[0][i] = estate;
        mockGameState->deckCount[0] += 1;
        
        mockGameState->discard[0][i] = copper;
        mockGameState->discardCount[0] += 1;
    }
}

struct gameState * smithyMockGameState() {
    struct gameState *mock = malloc(sizeof(struct gameState));
    
    return mock;
}
