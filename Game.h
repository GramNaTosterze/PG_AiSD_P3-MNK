#pragma once
#include "defines.h"
class Game {
    private:
    Player activePlayer;
    int m,n,k;
    Player** board;
    int possibleMoves;
    public:
  Game();
    Game(Game&);
  Game(int,int,int,Player);
    void scan();
    char* print();
    bool conVertical(int,int);
    bool conHorizontal(int,int);
    bool conCross(int,int);
    bool winingConditions(int,int);
    State place(Pos);
    State state();
    Player changePlayer();
    int getM() const;
    int getN() const;
    int getK() const;
    Player getPlayer() const;
    int  getPMoves() const;
    Player operator[](Pos);

    ~Game();
};
