#include <stdio.h>
#include "defines.h"
#include "Game.h"
#include "MNK.h"

int main() {
    MNKSolver solver(3,3,3);
    solver.genMoves();
    return 0;
}