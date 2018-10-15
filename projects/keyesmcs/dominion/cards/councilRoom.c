#include "../dominion.h"

/**
 * Card player draws four additional cards
 */
void drawFourCards(int player, struct gameState *state);


/**
 * Each player other than the card player draws one card
 */
void otherPlayersDrawOneCard(int player, struct gameState *state);

    
int playCouncilRoom(int player, struct gameState *state, int councilPosition) {

    drawFourCards(player, state);
			
    // +1 Buy
    state->numBuys++;

    otherPlayersDrawOneCard(player, state);

    //put played card in played card pile
    discardCard(councilPosition, player, state, 0);
			
    return 0;
}

void drawFourCards(int player, struct gameState *state) {
    // Current player gets +4 Cards
    for (int i = 0; i < 4; i++) {
        drawCard(player, state);
    }
}

void otherPlayersDrawOneCard(int player, struct gameState *state) {
    for (int i = 0; i < state->numPlayers; i++) {
        if ( i != player ) {
            drawCard(i, state);
        }
    }
}
