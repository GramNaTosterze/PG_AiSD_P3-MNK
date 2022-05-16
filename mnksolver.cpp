#include <stdio.h>
#include "defines.h"
#include "Game.h"
#include "MNK.h"

int main() {
  int n,m,k;
  Player activePlayer;
  char cmd[33];
  while(true) {
    scanf("%32s %i %i %i %i",cmd,&n,&m,&k,&activePlayer);
    if(feof(stdin)!=0)
      break;
    MNKSolver solver(cmd,n,m,k,activePlayer);
    solver.print();
  }
  return 0;
}
