#include "MNK.h"

MNKSolver::MNKSolver(MNKSolver& other): mnk(other.mnk){}
MNKSolver::MNKSolver(int m, int n, int k):  mnk(Game(m,n,k)) {}
void MNKSolver::genMoves() {
    mnk.scan();
    for(int i = 0; i < mnk.getM(); i++)
        for(int j = 0; j < mnk.getN(); j++)
            if(mnk[{i,j}] == NONE) {
                if(mnk.place({i,j})) {
                    mnk.print();
                    return;
                }
                mnk.print();
            }
}