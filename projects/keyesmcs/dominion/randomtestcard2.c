#include "dominion.h"
#include "dominion_helpers.h"
#include "cards/smithy.h"
#include "rngs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_RANDOM_TESTS 2000
#define CARDS_SMITHY_DRAWS 3

int randomizeGameState(struct gameState *randomState);
void testSmithyCard(struct gameState *testState);
void checkSmithyCard(struct gameState *testState,
                         struct gameState *controlState, int player);

int main() {
    struct gameState *testState = malloc(sizeof(struct gameState));

    printf("Testing playSmithy\n");

    for(int i = 0; i < NUM_RANDOM_TESTS; i++) {
        printf("test %d\n", i);
        testSmithyCard(testState);
    }

    printf("ALL TESTS OK\n");

    return 0;
}


int randomizeGameState(struct gameState *randomState) {
    int playerNumber = floor(Random() * 2);

    for (int i = 0; i < sizeof(struct gameState); i++) {
        ((char*)randomState)[i] = floor(Random() * 256);
    }
    
    randomState->deckCount[playerNumber] = floor(Random() * MAX_DECK);
    randomState->discardCount[playerNumber] = floor(Random() * MAX_DECK);
    randomState->handCount[playerNumber] = floor(Random() * MAX_DECK);
    randomState->hand[playerNumber][0] = smithy;

    return playerNumber;
}


void testSmithyCard(struct gameState *testState) {
    struct gameState *controlState = malloc(sizeof(struct gameState));

    int playerNum = randomizeGameState(testState);


    memcpy(controlState, testState, sizeof(struct gameState));

    playSmithy(playerNum, testState, 0);

    checkSmithyCard(testState, controlState, playerNum);
}

void checkSmithyCard(struct gameState *testState,
                         struct gameState *controlState, int player) {

/*    if (testState->handCount[player] ==
            controlState->handCount[player] + CARDS_SMITHY_DRAWS) {
*/
            controlState->handCount[player] += CARDS_SMITHY_DRAWS;

        memcpy(controlState->hand[player],
                testState->hand[player],
                sizeof(int) * MAX_DECK);
        memcpy(controlState->deck[player], testState->deck[player],
                sizeof(int) * MAX_DECK);
        memcpy(controlState->discard[player], testState->discard[player],
                sizeof(int) * MAX_DECK);

        controlState->deckCount[player] = testState->deckCount[player];
        controlState->discardCount[player] = testState->discardCount[player];
        controlState->handCount[player] = testState->handCount[player];
// }


    assert(memcmp(controlState, testState, sizeof(struct gameState)) == 0);
}

