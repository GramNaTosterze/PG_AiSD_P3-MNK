#pragma once
#include "defines.h"
#include "Game.h"
enum Mode{
  GEN_ALL_POS_MOV,
  GEN_ALL_POS_MOV_CUT_IF_GAME_OVER,
  SOLVE_GAME_STATE
};
class MNKSolver {
  Mode mode;
    Game state;
    public:
    MNKSolver(MNKSolver&);
  MNKSolver(char*,int,int,int,Player);
  void print();
  State genMoves();
  State minMax(Game);
};
