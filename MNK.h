#pragma once
#include "defines.h"
#include "Game.h"
class MNKSolver {
    Game mnk;
    public:
    MNKSolver(MNKSolver&);
    MNKSolver(int,int,int);
    void genMoves();
};