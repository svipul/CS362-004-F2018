#ifndef _REMODEL_H
#define _REMODEL_H

/**
 * Plays the Remodel card
 * Card description:
 *   Trash a card from your hand.
 *   Gain a card costing up to $2 more than it.
 */
int playRemodel(int player, struct gameState *state, int remodelCard,
        int cardToRemodel, int cardToBuy);

#endif
