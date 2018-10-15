#ifndef _CARD_HELPER_H
#define _CARD_HELPER_H

/**
 * Draws a number of cards specified by numCards
 */
void drawCards(int player, struct gameState *state, int numCards);

/**
 * Place one card from a player's hand into the trash, and replace it with
 * a new one
 */
int trashAndBuy(int player, struct gameState *state, int cardToTrash,
        int cardToBuy);

#endif
