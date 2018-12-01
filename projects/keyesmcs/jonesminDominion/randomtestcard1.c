#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_RANDOM_TESTS 200


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

/**
 * creates a random gameState (with a little bit of structure for
 * necessary card features)
 * returns the randomly-generated player number to test on
 */
int randomizeGameState(struct gameState *randomState) {
    int playerNumber = floor(Random() * 2);

    for (int i = 0; i < sizeof(struct gameState); i++) {
        ((char*)randomState)[i] = floor(Random() * 256);
    }
    
    randomState->deckCount[playerNumber] = floor(Random() * MAX_DECK);
    randomState->discardCount[playerNumber] = floor(Random() * MAX_DECK);
    randomState->handCount[playerNumber] = floor(Random() * MAX_DECK);
    randomState->playedCardCount = floor(Random() * MAX_DECK);

    // need a mine card to actually play
    randomState->hand[playerNumber][0] = mine;
    
    // randomly choose a coin card to use with the smithy
    randomState->hand[playerNumber][1] = floor(Random() * 3) + copper;

    return playerNumber;
}


/**
 * Test the card, mostly just calls other functions
 */
void testMineCard(struct gameState *testState) {
    struct gameState *controlState = malloc(sizeof(struct gameState));
    int playerNum = randomizeGameState(testState);

    int randomBuyCard = floor(Random() * treasure_map);
    memcpy(controlState, testState, sizeof(struct gameState));
   
    printf("mineCardEffect result: %d\n", 
            mineCardEffect(testState, playerNum, 1, randomBuyCard, 0)
            );
    checkMineCard(testState, controlState, playerNum);
}


/**
 * Check the pre-function gameState with the post-fuction gameState to be
 * sure that data in them lines up
 */
void checkMineCard(struct gameState *testState,
                         struct gameState *controlState, int player) {

    // check that the card was actually able to play
    if (controlState->hand[player][1] != testState->hand[player][1]) {
        controlState->handCount[player]--;
        controlState->playedCards[controlState->playedCardCount] = mine;
        controlState->playedCardCount++;
    }
        memcpy(controlState->hand[player],
                testState->hand[player],
                sizeof(int) * MAX_DECK);
       
        memcpy(controlState->supplyCount, testState->supplyCount, 
                sizeof(int) * treasure_map);

    assert(memcmp(controlState, testState, sizeof(struct gameState)) == 0);
}

