#include "dominion.h"
#include "dominion_helpers.h"
#include "cards/mine.h"
#include "rngs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_RANDOM_TESTS 500

int randomizeGameState(struct gameState *randomState);
void testMineCard(struct gameState *testState);
void checkMineCard(struct gameState *testState,
                         struct gameState *controlState, int player);

int main() {
    struct gameState *testState = malloc(sizeof(struct gameState));

    printf("Testing playMine\n");

    for(int i = 0; i < NUM_RANDOM_TESTS; i++) {
        printf("test %d\n", i);
        testMineCard(testState);
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
    randomState->hand[playerNumber][0] = mine;
    randomState->hand[playerNumber][1] = floor(Random() * 3) + copper; 

    return playerNumber;
}


void testMineCard(struct gameState *testState) {
    struct gameState *controlState = malloc(sizeof(struct gameState));

    int playerNum = randomizeGameState(testState);


    memcpy(controlState, testState, sizeof(struct gameState));

    playMine(playerNum, testState, 0, 1);

    checkMineCard(testState, controlState, playerNum);
}

void checkMineCard(struct gameState *testState,
                         struct gameState *controlState, int player) {

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
       
        memcpy(controlState->supplyCount, testState->supplyCount, 
                sizeof(int) * treasure_map);


        assert(memcmp(controlState->supplyCount, testState->supplyCount, sizeof(int) * treasure_map)
                == 0);

    assert(memcmp(controlState, testState, sizeof(struct gameState)) == 0);
}

