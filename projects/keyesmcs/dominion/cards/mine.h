#ifndef _MINE_H
#define _MINE_H

/**
 * Plays the Mine card
 * Card description:
 *   You may trash a Treasure from your hand. Gain a Treasure to your hand
 *   costing up to $3 more than it.
 */
int playMine(int player, struct gameState *state, int mineCard, int coinCard);

#endif
