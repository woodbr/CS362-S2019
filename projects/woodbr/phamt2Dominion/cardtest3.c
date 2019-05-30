#include "dominion.h"
#include "interface.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MY_NUM_PLAYERS 2
#define MY_RANDOM_SEED 7

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

int cardEffect(int, int, int, int, struct gameState *, int, int *);

int main()
{
  struct gameState *state = NULL;
  int kingdomCards[NUM_K_CARDS] = {0};

  if (setupTest(&state, kingdomCards)) {
    printf("setupTest() failed\n");
    return 1;
  }

  int bonus = 0;
  int currentPlayer = whoseTurn(state);
  int numHandCardsBefore = numHandCards(state);

  printf("*** Testing great_hall card\n");

  // put duchy, province, gold and silver on top of deck
  int deckCount = state->deckCount[currentPlayer];
  asserttrue(deckCount >= 1);
  int numActionsBefore = state->numActions;

  cardEffect(great_hall, gold, gold, gold, state, 0, &bonus);

  int numHandCardsAfter = numHandCards(state);
  int numActionsAfter = state->numActions;

  asserttrue(numHandCardsBefore == numHandCardsAfter);
  printf("OK: numHandCardsBefore == numHandCardsAfter\n");
  asserttrue(numActionsBefore + 1 == numActionsAfter);
  printf("OK: numActionsBefore + 1 == numActionsAfter\n");

  free(state);
  return finish();
}
