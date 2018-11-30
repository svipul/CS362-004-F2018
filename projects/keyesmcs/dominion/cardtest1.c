#include <stdio.h>
#include <stdlib.h>
#include "dominion_helpers.h"
#include "assertThat.h"
#include "cardtest1.h"

#define INITIAL_PILE_SIZE 10

struct gameState * adventurerMockGameState();
void resetGameState(struct gameState *mockGameState);

// test function signatures

#define TEST_COUNT 4
int increasesHandByTwo(struct gameState *mockGameState);
int shufflesDeckIfNoTreasure(struct gameState *mockGameState);
int unusedCardsGrowDiscard(struct gameState *mockGameState);
int noShuffleIfTwoTreasureFound(struct gameState *mockGameState);

int cardtest1() {
    struct gameState *mockGameState = adventurerMockGameState();

    int passingTests = 0;

    printf("Testing adventurer card:\n");

    passingTests += assertThat("adventurer card increases hand by two",
                               isTrue,
                               increasesHandByTwo(mockGameState));

    passingTests += assertThat("adventurer card shuffles the deck if it "
                               "can't find at least two treasure cards",
                               isTrue,
                               shufflesDeckIfNoTreasure(mockGameState));

    passingTests += assertThat("adventurer card places unused "
                               "(non-treasure) cards in the discard pile",
                               isTrue,
                               unusedCardsGrowDiscard(mockGameState));

    passingTests += assertThat("adventurer card does not shuffle the deck "
                               "if it finds two treasure cards",
                               isTrue,
                               noShuffleIfTwoTreasureFound(mockGameState));

    printf("adventurer card: %i of %i passed\n\n", passingTests,
            TEST_COUNT);

    return passingTests == TEST_COUNT;
}

int shufflesDeckIfNoTreasure(struct gameState *mockGameState) {
    resetGameState(mockGameState);

    // set a card in the deck to copper, so there's no chance of
    // the discard pile becoming exactly 10 cards deep after shuffle
    mockGameState->deck[0][9] = copper;

    cardEffect(adventurer, 0, 0, 0, mockGameState, 0, 0);

    
    return mockGameState->discardCount[0] != INITIAL_PILE_SIZE;
}

int unusedCardsGrowDiscard(struct gameState *mockGameState) {
    resetGameState(mockGameState);

    // bonus, tests different currency amounts
    mockGameState->deck[0][8] = silver;
    mockGameState->deck[0][7] = gold;

    cardEffect(adventurer, 0, 0, 0, mockGameState, 0, 0);

    return mockGameState->discardCount[0] == INITIAL_PILE_SIZE + 1;
}

int noShuffleIfTwoTreasureFound(struct gameState *mockGameState) {
    resetGameState(mockGameState);

    mockGameState->deck[0][0] = copper;
    mockGameState->deck[0][1] = silver;

    cardEffect(adventurer, 0, 0, 0, mockGameState, 0, 0);

    return mockGameState->discardCount[0] == INITIAL_PILE_SIZE + 8;
}

int increasesHandByTwo(struct gameState *mockGameState) {
    resetGameState(mockGameState);

    cardEffect(adventurer, 0, 0, 0, mockGameState, 0, 0);

    return mockGameState->handCount[mockGameState->whoseTurn] == 2;
}


void resetGameState(struct gameState * mockGameState) {
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

struct gameState * adventurerMockGameState() {
    struct gameState *mock = malloc(sizeof(struct gameState));
    
    return mock;
}
