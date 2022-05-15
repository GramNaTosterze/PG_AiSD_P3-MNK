#include <stdio.h>
#include <string.h>
#include "MNK.h"

MNKSolver::MNKSolver(MNKSolver& other): state(other.state){}
MNKSolver::MNKSolver(char* cmd, int n, int m, int k, Player activePlayer): state(m,n,k,activePlayer) {
  if(!strcmp(cmd,"SOLVE_GAME_STATE"))
    mode = SOLVE_GAME_STATE;
  else if(!strcmp(cmd,"GEN_ALL_POS_MOV_CUT_IF_GAME_OVER"))
    mode = GEN_ALL_POS_MOV_CUT_IF_GAME_OVER;
  else
    mode = GEN_ALL_POS_MOV;
}
void MNKSolver::print() {
    state.scan();
    switch(mode) {
    case GEN_ALL_POS_MOV: {
	genMoves();
	return;
    }
    case GEN_ALL_POS_MOV_CUT_IF_GAME_OVER: {
      switch(genMoves()) {
      case FIRST_PLAYER_WON:{
	printf("FIRST_PLAYER_WON");
	return;
      }
      case SECOND_PLAYER_WON:{
	printf("SECOND_PLAYER_WON");
	return;
      }
      case TIE:{
	printf("BOTH_PLAYERS_TIED");
	return;
      }
	default:{
	  return;
	}
      }
    }
    case SOLVE_GAME_STATE: {
      switch(minMax(state)) {
      case TIE: {
	printf("BOTH_PLAYERS_TIED");
	return;
      }
      case FIRST_PLAYER_WON: {
	printf("FIRST_PLAYER_WON");
	return;
      }
      case SECOND_PLAYER_WON: {
	printf("SECOND_PLAYER_WON");
	return;
      }
      default: {
	return;
      }
      }
    }
  }
}
State MNKSolver::genMoves() {
  int pMoves = 0;
  State currentState = RUNNING;
  char** moves = new char*[state.getPMoves()];
    for(int i = 0; i < state.getM(); i++)
        for(int j = 0; j < state.getN(); j++)
            if(state[{i,j}] == NONE) {
	      Game generated(state);
	      currentState = generated.place({i,j});
	      moves[pMoves] = generated.print();
              pMoves++;
	    }
    if(currentState == RUNNING || mode == GEN_ALL_POS_MOV){
      printf("%i\n",pMoves);
      for(int i = 0; i < pMoves; i++)
	printf("%s\n",moves[i]);
    }
    delete[] moves;
    return currentState;
}
Game* genAllPossibleMoves(Game gameState) {
  int possibleMoves = gameState.getPMoves();
  Game* allPossibleMoves = new Game[possibleMoves];
  for(int i = 0; i < possibleMoves; i++)
    allPossibleMoves[i] = Game(gameState);
  for(int i = 0; i < gameState.getM(); i++)
    for(int j = 0; j < gameState.getN(); j++)
      if(gameState[{i,j}] == NONE)
	allPossibleMoves[i].place({i,j});

  return allPossibleMoves;
}
State MNKSolver::minMax(Game gameState) {
    int possibleMoves = gameState.getPMoves();
    Game* allPossibleMoves = genAllPossibleMoves(gameState);
    if(gameState.state()) { return gameState.state();}
    State best; 
    if(gameState.getPlayer() == Player::FIRST)
      for(int i = 0; i < possibleMoves; i++) {
	State mm = minMax(allPossibleMoves[i]);
	best = best > mm ? best : mm;
      }
    else
      for(int i = 0; i < possibleMoves; i++) {
	State mm = minMax(allPossibleMoves[i]);
	best = best < mm ? best : mm;
      }
    return best;
}
