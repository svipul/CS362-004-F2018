#include "../dominion.h"
#include "cardHelper.h"

int playSmithy(int player, struct gameState *state, int smithyCard) {
    
    // draw three cards, yep
    drawCards(player, state, 3);
			
    //discard card from hand
    discardCard(smithyCard, player, state, 0);
    
    return 0;
}


