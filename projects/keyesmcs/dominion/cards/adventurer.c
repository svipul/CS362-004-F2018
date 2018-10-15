#include "../dominion.h"

/**
 * Returns the most recently drawn card for a given player
 * In practice, that's the "top" card in the player's hand
 */
int getDrawnCard(int player, struct gameState *state);


/**
 * Places the most recently drawn card on the discard pile
 */
void discardLastDrawnCard(int player, struct gameState *state);

/**
 * Plays the adventurer card, see header for full description
 */
int playAdventurer(int player, struct gameState *state) {
    int drawnTreasure = 0; // Tracks the number of treasure cards drawn
    int cardDrawn;

    while(drawnTreasure < 2) {
        //if the deck is empty, shuffle discard and add to deck
        if (state->deckCount[player] <1) {
	    shuffle(player, state);
	}

        // draw a card, and get its value
	drawCard(player, state);
        cardDrawn = getDrawnCard(player, state);

        // if the card is a treasure card, add it to drawnTreasure count
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  drawnTreasure++;

        // if the card isn't a treasure card, discard it
	else {
            discardLastDrawnCard(player, state);
	}
    }

    return 0;
}


int getDrawnCard(int player, struct gameState *state) {
    int topCardIndex = state->handCount[player] - 1;
    return state->hand[player][topCardIndex];
}

void discardLastDrawnCard(int player, struct gameState *state) {
    int newDiscardIndex = state->discardCount[player]++;
    int newHandIndex = state->handCount[player]--;
        state->discard[player][newDiscardIndex] =
            state->hand[player][newHandIndex];
}

