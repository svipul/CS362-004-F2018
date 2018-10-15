#include "../dominion.h"

void drawCards(int player, struct gameState *state, int numCards) {
    for (int i = 0; i < numCards; i++) {
        drawCard(player, state);
    }
}


int trashAndBuy(int player, struct gameState *state, int cardToTrash,
        int cardToBuy) {
    if (state->supplyCount[cardToBuy] > 0) {
        state->hand[player][cardToTrash] = cardToBuy;
        state->supplyCount[cardToBuy]--;
        
        return 0;
    } else {
        return -1;
    }
}
