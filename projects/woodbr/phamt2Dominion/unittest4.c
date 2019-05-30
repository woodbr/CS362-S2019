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

  if (setupTest(&state, kingdomCards)) {
    printf("setupTest() failed\n");
    return 1;
  }

  int player = whoseTurn(state);
  int numHandCardsBefore = numHandCards(state);
  int silverSupplyBefore = supplyCount(silver, state);

  printf("*** Testing mineCardEffect\n");

  int res = mineCardEffect(state, curse - 1, treasure_map, 0, player);
  assert(res == -1);

  int numHandCardsAfter = numHandCards(state);
  int silverSupplyAfter = supplyCount(silver, state);

  asserttrue(numHandCardsBefore == numHandCardsAfter);
  printf("OK: numHandCardsBefore == numHandCardsAfter\n");
  asserttrue(silverSupplyBefore == silverSupplyAfter);
  printf("OK: silverSupplyBefore == silverSupplyAfter\n");

  res = mineCardEffect(state, curse, treasure_map + 1, 0, player);
  asserttrue(res == -1);

  numHandCardsAfter = numHandCards(state);
  silverSupplyAfter = supplyCount(silver, state);

  asserttrue(numHandCardsBefore == numHandCardsAfter);
  printf("OK: numHandCardsBefore == numHandCardsAfter\n");
  asserttrue(silverSupplyBefore == silverSupplyAfter);
  printf("OK: silverSupplyBefore == silverSupplyAfter\n");

  res = mineCardEffect(state, estate, silver, 0, player);
  asserttrue(res == 0);

  numHandCardsAfter = numHandCards(state);
  silverSupplyAfter = supplyCount(silver, state);

  asserttrue(numHandCardsBefore > numHandCardsAfter);
  printf("OK: numHandCardsBefore > numHandCardsAfter\n");
  asserttrue(silverSupplyBefore > silverSupplyAfter);
  printf("OK: silverSupplyBefore > silverSupplyAfter\n");

  free(state);
  return finish();
}
