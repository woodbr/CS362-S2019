#include "dominion.h"
#include "interface.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MY_NUM_PLAYERS 2
#define MY_RANDOM_SEED 7

extern int adventurerRefactored(int drawntreasure, struct gameState *state, int currentPlayer);

static int setupTest(struct gameState **state, int kingdomCards[NUM_K_CARDS])
{
  *state = newGame();
  if (*state == NULL) {
    return -1;
  }

  selectKingdomCards(MY_RANDOM_SEED, kingdomCards);

  if (initializeGame(2, kingdomCards, MY_RANDOM_SEED, *state)) {
    free(*state);
    return -1;
  }

  return 0;
}

static int numTreasureCards(struct gameState *state)
{
  int player = whoseTurn(state);
  return fullDeckCount(player, copper, state) + fullDeckCount(player, silver, state) + fullDeckCount(player, gold, state);
}

static int numErrors;
static void myAssert(int cond, const char *msg, int line) {
    if (!(cond)) {
        printf(__FILE__ ":%d: FAILED: %s\n", line, msg);
        ++numErrors;
    }
}
#define asserttrue(cond) myAssert((cond), #cond, __LINE__);

static int finish()
{
  if (numErrors) {
    printf("%d checks failed\n", numErrors);
    return 1;
  }
  else {
    printf("ALL TESTS PASSED\n");
    return 0;
  }
}

int main()
{
  struct gameState *state = NULL;
  int kingdomCards[NUM_K_CARDS] = {0};

  if (setupTest(&state, kingdomCards)) {
    printf("setupTest() failed\n");
    return 1;
  }

  int player = whoseTurn(state);
  int numHandCardsBefore = numHandCards(state);
  int numTreasureCardsBefore = numTreasureCards(state);
  int drawntreasure = 10;

  printf("*** Testing adventurerRefactored\n");

  adventurerRefactored(drawntreasure, state, player);

  int numHandCardsAfter = numHandCards(state);
  int numTreasureCardsAfter = numTreasureCards(state);

  asserttrue(numHandCardsBefore < numHandCardsAfter);
  printf("OK: numHandCardsBefore < numHandCardsAfter\n");
  asserttrue(numTreasureCardsBefore == numTreasureCardsAfter);
  printf("OK: numTreasureCardsBefore == numTreasureCardsAfter\n");

  free(state);
  return finish();
}
