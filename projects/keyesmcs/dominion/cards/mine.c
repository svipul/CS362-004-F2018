#include "../dominion.h"

/**
 * Trade out a coin card for one of the next-highest value
 */
void upgradeCoin(int player, struct gameState *state, int coinCard);

/**
 * Plays a mine card. See header file for full card description.
 */
int playMine(int player, struct gameState *state, int mineCard, int coinCard) {
    int cardValue = state->hand[player][coinCard];
    if (cardValue == copper || cardValue == silver) {
        upgradeCoin(player, state, coinCard);
        discardCard(mineCard, player, state, 0);
        return 0;
    } else {
        return -1;
    }
}

void upgradeCoin(int player, struct gameState *state, int coinCard) {
    // since the coin enums are in order, to change them out all you need
    // to do is increment the card's value
    int newCoin = state->hand[player][coinCard]++;
    state->supplyCount[newCoin]--;
}
