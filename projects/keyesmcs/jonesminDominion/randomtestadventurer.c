#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_RANDOM_TESTS 200
#define CARDS_ADVENTURER_DRAWS 2

int randomizeGameState(struct gameState *randomState);
void testAdventurerCard(struct gameState *testState);
void checkAdventurerCard(struct gameState *testState,
                         struct gameState *controlState, int player);

int main() {
    struct gameState *testState = malloc(sizeof(struct gameState));

    printf("Testing playAdventurer\n");

    for(int i = 0; i < NUM_RANDOM_TESTS; i++) {
        printf("test %d\n", i);
        testAdventurerCard(testState);
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
    randomState->playedCardCount = 0;

    // make sure there are enough coins in the deck for the card to 
    // be successful
    randomState->deck[playerNumber][0] = copper;
    randomState->deck[playerNumber][1] = copper;

    return playerNumber;
}

/**
 * Test the card, mostly just calls other functions
 */
void testAdventurerCard(struct gameState *testState) {
    struct gameState *controlState = malloc(sizeof(struct gameState));

    int playerNum = randomizeGameState(testState);


    memcpy(controlState, testState, sizeof(struct gameState));

    adventurerCardEffect(testState, playerNum);

    checkAdventurerCard(testState, controlState, playerNum);
}


/**
 * Check the pre-function gameState with the post-fuction gameState to be
 * sure that data in them lines up
 */
void checkAdventurerCard(struct gameState *testState,
                         struct gameState *controlState, int player) {
   
    if (testState->handCount[player] ==
            controlState->handCount[player] + CARDS_ADVENTURER_DRAWS) {

            controlState->handCount[player] += CARDS_ADVENTURER_DRAWS;

        memcpy(controlState->hand[player],
                testState->hand[player],
                sizeof(int) * MAX_DECK);
        memcpy(controlState->deck[player], testState->deck[player],
                sizeof(int) * MAX_DECK);
        memcpy(controlState->discard[player], testState->discard[player],
                sizeof(int) * MAX_DECK);
        controlState->deckCount[player] = testState->deckCount[player];
  }

    assert(memcmp(controlState, testState, sizeof(struct gameState)) == 0);
}

