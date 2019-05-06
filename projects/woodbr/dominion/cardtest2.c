#include "dominion.h"
#include "dominion_helpers.h"
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

  printf("*** Testing smithy card\n");

  int deckCountBefore = state->deckCount[currentPlayer];
  asserttrue(deckCountBefore >= 3);

  cardEffect(smithy, gold, gold, gold, state, 0, &bonus);

  int deckCountAfter = state->deckCount[currentPlayer];
  int numHandCardsAfter = numHandCards(state);

  asserttrue(deckCountBefore - 3 == deckCountAfter);
  asserttrue(numHandCardsBefore + 3 - 1 == numHandCardsAfter);

  free(state);
  return finish();
}
