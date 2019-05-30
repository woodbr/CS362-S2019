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

int main()
{
  struct gameState *state = NULL;
  int kingdomCards[NUM_K_CARDS] = {0};
  int tempHand[MAX_HAND] = {0};

  if (setupTest(&state, kingdomCards)) {
    printf("setupTest() failed\n");
    return 1;
  }

  int player = whoseTurn(state);
  int choice1 = estate;
  int numHandCardsBefore = numHandCards(state);
  int numChoice1CardsBefore = supplyCount(choice1, state);

  printf("*** Testing feastCardEffect\n");

  // make sure player has enough coins for estate card
  updateCoins(player, state, getCost(choice1));
  feastCardEffect(state, tempHand, choice1, player);

  int numHandCardsAfter = numHandCards(state);
  int numChoice1CardsAfter = supplyCount(choice1, state);

  asserttrue(numHandCardsBefore == numHandCardsAfter);
  printf("OK: numHandCardsBefore == numHandCardsAfter\n");
  asserttrue(numChoice1CardsBefore - 1 == numChoice1CardsAfter);
  printf("OK: numChoice1CardsBefore - 1 == numChoice1CardsAfter\n");

  free(state);
  return finish();
}
