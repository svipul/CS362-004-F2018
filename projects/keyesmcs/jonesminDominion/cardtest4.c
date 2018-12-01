#include <stdio.h>
#include <stdlib.h>
#include "dominion_helpers.h"
#include "assertThat.h"
#include "cardtest4.h"

#define INITIAL_PILE_SIZE 10

struct gameState * councilMockGameState();
void resetCouncilMockState(struct gameState *mockGameState);

// test function signatures

#define TEST_COUNT 3
int shufflesDeckIfLow(struct gameState *mockGameState);
int increasesHandByFour(struct gameState *mockGameState);
int givesOpponentsACard(struct gameState *mockGameState);

int cardtest4() {
    struct gameState *mockGameState = councilMockGameState();

    int passingTests = 0;

    printf("Testing council room card:\n");

    passingTests += assertThat("council room card increases hand by four",
                               isTrue,
                               increasesHandByFour(mockGameState));

    passingTests += assertThat("council room card shuffles the deck if it "
                               "can't draw at least four cards",
                               isTrue,
                               shufflesDeckIfLow(mockGameState));

    passingTests += assertThat("council room card gives other players one "
                               "card each",
                               isTrue,
                               givesOpponentsACard(mockGameState));

    printf("council room card: %i of %i passed\n\n", passingTests,
            TEST_COUNT);

    return passingTests == TEST_COUNT;
}

int shufflesDeckIfLow(struct gameState *mockGameState) {
    resetCouncilMockState(mockGameState);
    
    // set deckCount to 2, so the game has to shuffle
    mockGameState->deckCount[0] = 3;

    cardEffect(council_room, 0, 0, 0, mockGameState, 0, 0);

    
    return mockGameState->discardCount[0] != INITIAL_PILE_SIZE;
}

int increasesHandByFour(struct gameState *mockGameState) {
    resetCouncilMockState(mockGameState);

    cardEffect(council_room, 0, 0, 0, mockGameState, 0, 0);

    return mockGameState->handCount[0] == 4;
}

int givesOpponentsACard(struct gameState *mockGameState) {
    resetCouncilMockState(mockGameState);

    cardEffect(council_room, 0, 0, 0, mockGameState, 0, 0);

    return mockGameState->handCount[1] == 1 &&
           mockGameState->handCount[2] == 1 &&
           mockGameState->handCount[3] == 1;
}


void resetCouncilMockState(struct gameState * mockGameState) {
    int i;

    mockGameState->whoseTurn = 0;
    mockGameState->numPlayers = 4;
    
    mockGameState->hand[0][0] = council_room;
    mockGameState->handCount[0] = 1;

    mockGameState->handCount[1] = mockGameState->handCount[2] =
        mockGameState->handCount[3] = 0;

    mockGameState->deckCount[1] = mockGameState->deckCount[2] =
        mockGameState->deckCount[3] = 1;

    for (i = 0; i < INITIAL_PILE_SIZE; i++) {
        mockGameState->deck[0][i] = estate;
        mockGameState->deckCount[0] += 1;
        
        mockGameState->discard[0][i] = copper;
        mockGameState->discardCount[0] += 1;
    }
}

struct gameState * councilMockGameState() {
    struct gameState *mock = malloc(sizeof(struct gameState));
    
    return mock;
}
