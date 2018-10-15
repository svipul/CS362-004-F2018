#ifndef _ADVENTURER_H
#define _ADVENTURER_H

/**
 * Plays the Adventurer card
 * Card description:
 *   Reveal cards from your deck until you reveal 2 Treasure cards. Put
 *   those Treasure cards into your hand and discard the other revealed
 *   cards.
 */
int playAdventurer(int player, struct gameState *state);

#endif
