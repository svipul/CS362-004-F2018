#include <stdio.h>
#include <stdlib.h>
#include "dominion_helpers.h"
#include "assertThat.h"
#include "unittest2.h"

struct gameState * gainCardMockGameState();

// test function signatures
#define TEST_COUNT 6
int gainCardToHandWorks(struct gameState *mockGameState);
int gainCardToDeckWorks(struct gameState *mockGameState);
int gainCardToDiscardWorks(struct gameState *mockGameState);
int gainCardLowersSupplyCount(struct gameState *mockGameState);
int gainCardOnEmptyReturnsNegOne(struct gameState *mockGameState);
int gainCardOnNotUsedReturnsNegOne(struct gameState *mockGameState);

int unittest2() {
    struct gameState *mockGameState = gainCardMockGameState();

    int passingTests = 0;

    printf("Tesing gainCard:\n");

    passingTests += assertThat("gainCard can add a card to a player's hand",
            isTrue,
            gainCardToHandWorks(mockGameState));

    passingTests += assertThat("gainCard can add a card to a player's deck",
            isTrue,
            gainCardToDeckWorks(mockGameState));

    passingTests += assertThat("gainCard can add a card to a player's "
                               "discard",
                               isTrue,
                               gainCardToDiscardWorks(mockGameState));

    passingTests += assertThat("gainCard lowers the supply of the card "
                               "that's gained",
                               isTrue,
                               gainCardLowersSupplyCount(mockGameState));

    passingTests += assertThat("gainCard returns -1 for cards with 0 "
                               "supply count",
                               isTrue,
                               gainCardOnEmptyReturnsNegOne(mockGameState));


    passingTests += assertThat("gainCard returns -1 for cards not used "
                               "in the given game",
                               isTrue,
                             gainCardOnNotUsedReturnsNegOne(mockGameState));

    printf("gainCard: %i of %i passed\n\n", passingTests, TEST_COUNT);

    return passingTests == TEST_COUNT;

}

int gainCardToHandWorks(struct gameState *mockGameState) {
    gainCard(copper, mockGameState, 2, 0);

    return mockGameState->hand[0][mockGameState->handCount[0] - 1] ==
        copper;
}

int gainCardToDeckWorks(struct gameState *mockGameState) {
    gainCard(copper, mockGameState, 1, 0);

    return mockGameState->deck[0][mockGameState->deckCount[0] - 1] ==
        copper;
}

int gainCardToDiscardWorks(struct gameState *mockGameState) {
    gainCard(copper, mockGameState, 0, 0);

    return mockGameState->deck[0][mockGameState->discardCount[0] - 1] == 
        copper;
}

int gainCardLowersSupplyCount(struct gameState *mockGameState) {
    int originalSilverCount = mockGameState->supplyCount[silver];

    gainCard(silver, mockGameState, 0, 0);

    return originalSilverCount - 1 == mockGameState->supplyCount[silver];
}

int gainCardOnEmptyReturnsNegOne(struct gameState *mockGameState) {
    return gainCard(gold, mockGameState, 0, 0) == -1;
}

int gainCardOnNotUsedReturnsNegOne(struct gameState *mockGameState) {
    return gainCard(estate, mockGameState, 0, 0) == -1;
}


struct gameState * gainCardMockGameState() {
    struct gameState * mock = malloc(sizeof(struct gameState));
    int i;

    // set all supplies to -1, indicating that they're not in the game
    for (i = 0; i < treasure_map; i++) {
        mock->supplyCount[i] = -1;
    }

    mock->supplyCount[copper] = 99;
    mock->supplyCount[silver] = 99;
    mock->supplyCount[gold] = 0;

    return mock;
}
