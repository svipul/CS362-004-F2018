#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "assertThat.h"
#include "unittest1.h"

#define PLAYER0_ESTATE_CARDS_PER_PILE 3
#define PLAYER0_CURSE_CARDS 4
#define PLAYER0_SMITHY_CARDS 8
#define PLAYER0_TREASURE_MAP_CARDS 16
#define PLAYER0_CARDS_PER_PILE 99

struct gameState * fullDeckCountMockGameState();

// test function signtures
#define TEST_COUNT 6
int canCountInDeck(struct gameState* mockGameState);
int canCountInHand(struct gameState* mockGameState);
int canCountInDiscard(struct gameState* mockGameState);
int canCountAcrossAll(struct gameState* mockGameState);
int countZeroIfCardNotPresent(struct gameState* mockGameState);
int allZeroIfPlayerEmpty(struct gameState* mockGameState);

int unittest1() {
    struct gameState *mockGameState = fullDeckCountMockGameState();
    int passingTests = 0;

    printf("Testing fullDeckCount:\n");

    passingTests += assertThat("fullDeckCount correctly counts cards in "
                               "player's deck",
                               isTrue,
                               canCountInDeck(mockGameState));

    passingTests += assertThat("fullDeckCount correctly counts cards in " 
                               "player's hand",
                               isTrue,
                               canCountInHand(mockGameState));

    passingTests += assertThat("fullDeckCount correctly counts cards in "
                              "player's discard",
                              isTrue, 
                             canCountInDiscard(mockGameState));

    passingTests += assertThat("fullDeckCount correctly counts cards "
                               "across deck, hand, and discard",
                               isTrue,
                               canCountAcrossAll(mockGameState));

    passingTests += assertThat("fullDeckCount retruns 0 if the player "
                               "doesn't own a given card",
                               isTrue,
                               countZeroIfCardNotPresent(mockGameState));


    passingTests += assertThat("fullDeckCount correctly finds no cards "
                               "of any type for a player with no cards",
                               isTrue,
                               allZeroIfPlayerEmpty(mockGameState));

    printf("fullDeckCount: %i of %i passed\n\n", passingTests, TEST_COUNT);

    return passingTests == TEST_COUNT;
}

int canCountInDeck(struct gameState* mockGameState) {
    return fullDeckCount(0,curse,mockGameState) == PLAYER0_CURSE_CARDS;
}

int canCountInHand(struct gameState* mockGameState) {
    return fullDeckCount(0,smithy,mockGameState) == PLAYER0_SMITHY_CARDS;
}

int canCountInDiscard(struct gameState* mockGameState) {
    return fullDeckCount(0,treasure_map,mockGameState) ==
        PLAYER0_TREASURE_MAP_CARDS;
}

int canCountAcrossAll(struct gameState* mockGameState) {
    return fullDeckCount(0,estate,mockGameState) ==
            PLAYER0_ESTATE_CARDS_PER_PILE * 3;
}

int countZeroIfCardNotPresent(struct gameState* mockGameState) {
    return fullDeckCount(0,adventurer,mockGameState) == 0;
}

int allZeroIfPlayerEmpty(struct gameState* mockGameState) {
    int i;
    for(i = curse; i <= treasure_map; i++) {
        if (fullDeckCount(1,i,mockGameState) > 0) {
            return 0;
        }
    }

    return 1;
}

/**
 * Returns a pointer to a gameState struct with the following mocked players
 *
 * Player 0:
 *  deck:       4 curse cards, 3 estate cards, random treasure
 *  hand:       8 smithy cards, 3 estate cards, random treasure
 *  discard:    16 treasure_map cards, 3 estate cards, random treasure
 *
 * Player 1:
 *  deck:       no cards
 *  hand:       no cards
 *  discard:    no cards
 */
struct gameState * fullDeckCountMockGameState() {
    struct gameState *mock = malloc(sizeof(struct gameState));
    int i, estateCardIndex;

    // add curse cards to Player0's deck, and fill the rest of the deck
    // with treasure cards
    for (i = 0; i < PLAYER0_CARDS_PER_PILE; i++) {
        if (i < PLAYER0_CURSE_CARDS) {
            mock->deck[0][i] = curse;
        } else {
            mock->deck[0][i] = i % 3 + 4;
        }
        mock->deckCount[0] += 1;
    }

    // add smithy cards to Player0's hand, and fill the rest of the hand
    // with treasure cards
    for (i = 0; i < PLAYER0_CARDS_PER_PILE; i++) {
        if (i < PLAYER0_SMITHY_CARDS) {   
            mock->hand[0][i] = smithy;
        } else {
            mock->hand[0][i] = i % 3 + 4;
        }
        mock->handCount[0] += 1;
    }

    // add treasure_map cards to Player0's discard pile, and fill the rest
    // of the pile with treasure cards
    for (i = 0; i < PLAYER0_CARDS_PER_PILE; i++) {
        if (i < PLAYER0_TREASURE_MAP_CARDS) {
            mock->discard[0][i] = treasure_map;
        } else {
            mock->discard[0][i] = i % 3 + 4;
        }
        mock->discardCount[0] += 1;
    }


    // Set the last few cards of Player0's piles to estate cards
    for (i = 0; i < PLAYER0_ESTATE_CARDS_PER_PILE; i++) {
        estateCardIndex = PLAYER0_CARDS_PER_PILE - 1 - i;
        mock->discard[0][estateCardIndex] =
        mock->hand[0][estateCardIndex] =
        mock->deck[0][estateCardIndex] = estate;
    }

    // set Player1's pile counts to 0
    mock->deckCount[1] = mock->handCount[1] = mock->discardCount[1] = 0;

    return mock;
}
