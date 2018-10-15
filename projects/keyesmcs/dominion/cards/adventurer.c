#include "../dominion.h"

/**
 * Returns the most recently drawn card for a given player
 * In practice, that's the "top" card in the player's hand
 */
int getDrawnCard(struct gameState *state);


/**
 * Places the most recently drawn card on the discard pile
 */
void discardLastDrawnCard(struct gameState *state);

/**
 * Plays the adventurer card, see header for full description
 */
int playAdventurer(struct gameState *state) {
    int drawnTreasure = 0; // Tracks the number of treasure cards drawn
    int currentPlayer = whoseTurn(state);
    int cardDrawn;

    while(drawnTreasure < 2) {
        //if the deck is empty, shuffle discard and add to deck
        if (state->deckCount[currentPlayer] <1) {
	    shuffle(currentPlayer, state);
	}

        // draw a card, and get its value
	drawCard(currentPlayer, state);
        cardDrawn = getDrawnCard(state);

        // if the card is a treasure card, add it to drawnTreasure count
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  drawnTreasure++;

        // if the card isn't a treasure card, discard it
	else {
            discardLastDrawnCard(state);
	}
    }

    return 0;
}


int getDrawnCard(struct gameState *state) {
    int player = whoseTurn(state);
    int topCardIndex = state->handCount[player] - 1;
    return state->hand[player][topCardIndex];
}

void discardLastDrawnCard(struct gameState *state) {
    int player = whoseTurn(state);
    int newDiscardIndex = state->discardCount[player]++;
    int newHandIndex = state->handCount[player]--;
        state->discard[player][newDiscardIndex] =
            state->hand[player][newHandIndex];
}

