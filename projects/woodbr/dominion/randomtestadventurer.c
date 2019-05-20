#include "dominion.h"
#include "interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int findCard(int, struct gameState *);
int runRandomGame(struct gameState *, void(*)(struct gameState *));

static int cbCount;

static void adventurerTest(struct gameState *g)
{
	int handPos = findCard(council_room, g);
	if (handPos < 0) {
		//printf("adventurer not found!\n");
		return;
	}
	adventurerCardEffect(g, whoseTurn(g));
	++cbCount;
}

int main() {

	enum { NUM_GAMES = 1000 };
	struct gameState *g = malloc(sizeof(struct gameState));
	if (g == NULL) {
		return 1;
	}

	srand(time(NULL));

	for (int i = 0; i < NUM_GAMES; i++) {
		memset(g,0,sizeof(*g));
		runRandomGame(g, &adventurerTest);
	}
	printf("cbCount=%d\n", cbCount);
	return 0;
}
