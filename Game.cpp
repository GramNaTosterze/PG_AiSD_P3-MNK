#include <stdio.h>
#include "Game.h"

Player** copyArr(Player** arr, int x, int y) {
    Player** cpy = new Player*[x];
    for(int i = 0; i < x; i++)
        cpy[i] = new Player[y]; 
    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            cpy[i][j] = arr[i][j];
    return cpy;
}
Game::Game() {}
Game::Game(Game& other): m(other.getM()), n(other.getM()), k(other.getK()), board(copyArr(other.board,m,n)), possibleMoves(other.possibleMoves), activePlayer(other.activePlayer){}
Game::Game(int m, int n, int k, Player activePlayer): m(m),n(n),k(k),board(new Player*[n]),possibleMoves(n*k), activePlayer(activePlayer){
    for(int i = 0; i < n; i++)
        board[i] = new Player[m];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            board[i][j] = NONE;
}
void Game::scan() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
	  scanf("%i",&board[i][j]);
            if(board[i][j] != 0)
                possibleMoves--;
        }
}
char* Game::print() {
    char *prt = new char[3*n*m];
    sprintf(prt,"");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
	  sprintf(prt,"%s %i",prt,board[i][j]);
        }
        sprintf(prt,"%s\n",prt);
    }
    return prt;
}
bool Game::conVertical(int I, int J) {
    if(I+k > n)
        return false;
    for(int i = 0; i < k; i++)
        if(board[I+i][J] != activePlayer)
            return false;
    return true;
}
bool Game::conHorizontal(int I, int J) {
    if(J+k > m)
        return false;
    for(int i = 0; i < k; i++)
        if(board[I][J+i] != activePlayer)
            return false;
    return true;
}
bool Game::conCross(int I, int J) {
    if(I+k > n || J+k > m)
        return false;
    for(int i = 0; i < k; i++)
        if(board[I+i][J+i] != activePlayer)
            return false;
    return true;
}
bool Game::winingConditions(int I, int J) {
    return conHorizontal(I,J) || conVertical(I,J) || conCross(I,J);
}
State Game::state() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(board[i][j] == activePlayer)
	      if(winingConditions(i,j))
                  return activePlayer == FIRST ? FIRST_PLAYER_WON : SECOND_PLAYER_WON;
    return RUNNING;
}
State Game::place(Pos pos) {
    if(board[pos.x][pos.y] != 0) {
        printf("pole zajęte");
        return RUNNING;
    }
    board[pos.x][pos.y] = activePlayer;
    State toReturn = state();
    activePlayer = changePlayer();
    possibleMoves--;
    return toReturn;
}
Player Game::changePlayer() { return activePlayer==FIRST ? SECOND : FIRST; }
Player Game::operator[](Pos pos) { return board[pos.x][pos.y]; }
int Game::getM() const{ return m; }
int Game::getN() const{ return n; }
int Game::getK() const{ return k; }
Player Game::getPlayer() const { return activePlayer; }
int Game::getPMoves() const { return possibleMoves; }
Game::~Game() {
    for(int i = 0; i < n; i++)
        delete board[i];
    delete[] board;
    board = nullptr;
}
