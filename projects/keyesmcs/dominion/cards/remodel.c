#include "../dominion.h"
#include "cardHelper.h"

int playRemodel(int player, struct gameState *state, int remodelCard,
        int cardToRemodel, int cardToBuy) {

    // available funds to remodel = card cost + 2
    int remodelFunds = getCost(state->hand[player][cardToRemodel]) + 2;
    int newCardCost = getCost(cardToBuy);

    // if there enough funds to buy the new card
    if (remodelFunds >= newCardCost) {

        // discard the remodel card, and buy the new card
        discardCard(remodelCard, player, state, 0);
        return trashAndBuy(player, state, cardToRemodel, cardToBuy);        
    
    // otherwise, return -1, 'cause that's what we're doing
    } else {
        return -1;
    }

}
