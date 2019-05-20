#include "dominion.h"
#include "interface.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static int genRandomRange(int low, int high)
{
	assert(low < high);
	int res = rand();
	res %= high - low;
	res += low;
	return res;
}

int genRandomCard()
{
	return genRandomRange(adventurer, NUM_TOTAL_K_CARDS);
}

static int genRandomNumPlayers()
{
	enum { MIN_PLAYERS = 1 };
	return genRandomRange(MIN_PLAYERS, MAX_PLAYERS);
}

static int doRandomGame(int numCommands, struct gameState *g, void(*cb)(struct gameState *))
{
	int rc = 0;
	enum { ADD, BUY, END, PLAY, CALLBACK, NUM_COMMANDS };
	for (int i = 0; i < numCommands; i++) {
		if (isGameOver(g)) {
			rc = 1;
			break;
		}
		switch (rand() % NUM_COMMANDS) {
			case ADD:
				addCardToHand(whoseTurn(g), genRandomCard(), g);
				break;
			case BUY:
				buyCard(rand() % 20, g);
				break;
			case END:
				endTurn(g);
				break;
			case PLAY: {
				int hc = numHandCards(g);
				if (hc > 0) {
					playCard(rand() % hc,
						rand() % hc,
						rand() % hc,
						rand() % hc,
						g);
				}
				break;
			}
			case CALLBACK:
				(*cb)(g);
				break;
			default:
				assert(0);
				break;
		}
	}
	return rc;
}

int findCard(int card, struct gameState *g)
{
	int hc = numHandCards(g);
	for (int i = 0; i < hc; i++) {
		if (handCard(i, g) == card)
			return i;
	}
	return -1;
}

void runRandomGame(struct gameState *g, void(*cb)(struct gameState *))
{
	int randomSeed = rand();

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	initializeGame(genRandomNumPlayers(),k,randomSeed,g);

	enum { MAX_COMMANDS = 1000 };
	doRandomGame(rand() % MAX_COMMANDS, g, cb);
}
