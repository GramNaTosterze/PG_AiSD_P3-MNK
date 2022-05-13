#include <stdio.h>

enum Player {
    FIRST = 1,
    SECOND
};
struct Pos {
    int x;
    int y;
};

int** copyArr(int** arr, int x, int y) {
    int** cpy = new int*[x];
    for(int i = 0; i < x; i++)
        cpy[i] = new int[y]; 
    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            cpy[i][j] = arr[i][j];
    return cpy;
}
class Game {
    private:
    Player activePlayer;
    int m,n,k;
    int** board;
    int possibleMoves;
    public:
    Game(int,int,int);
    void scan();
    void print();
    bool conVertical(int,int);
    bool conHorizontal(int,int);
    bool conCross(int,int);
    bool winingConditions(int,int);
    void place(Pos);
    void state();
    void changePlayer();

    ~Game();
};
class MNKSolver {
    Game *mnk;
    public:
    MNKSolver(int,int,int);
};
Game::Game(int m, int n, int k): m(m),n(n),k(k),board(new int*[n]),possibleMoves(n*k){
    for(int i = 0; i < n; i++)
        board[i] = new int[m];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            board[i][j] = 0;
}
void Game::scan() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            scanf("%i",&board[i][j]);
            if(board[i][j] != 0)
                possibleMoves--;
        }
}
void Game::print() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            printf("%i ",board[i][j]);
            changePlayer();
        }
        printf("\n");
    }
}
bool Game::conVertical(int I, int J) {
    if(I+k >= n)
        return false;
    for(int i = 0; i < k; i++)
        if(board[I+i][J] != activePlayer)
            return false;
    return true;
}
bool Game::conHorizontal(int I, int J) {
    if(J+k >= m)
        return false;
    for(int i = 0; i < k; i++)
        if(board[I][J+i] != activePlayer)
            return false;
    return true;
}
bool Game::conCross(int I, int J) {
    if(I+k >= n || J+k >= m)
        return false;
    for(int i = 0; i < k; i++)
        if(board[I+i][J+i] != activePlayer)
            return false;
    return true;
}

bool Game::winingConditions(int I, int J) {
    return conHorizontal(I,J) || conVertical(I,J) || conCross(I,J);
}
void Game::state() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(board[i][j] == activePlayer) {
                if(winingConditions(i,j)) {
                    printf("Player %i won\n",activePlayer);
                }
            }

}
void Game::place(Pos pos) {
    if(board[pos.x][pos.y] != 0) {
        printf("pole zajęte");
        return;
    }
    board[pos.x][pos.y] = (int)activePlayer;
    changePlayer();
    possibleMoves--;
    state();
}
void Game::changePlayer() {
    activePlayer = activePlayer==1 ? SECOND : FIRST;
}
Game::~Game() {
    for(int i = 0; i < n; i++)
        delete board[i];
    delete board;
    board = nullptr;
}
MNKSolver::MNKSolver(int m, int n, int k):  mnk(new Game(m,n,k)) {
    
}
int main() {
    Game ttt(3,3,3);
    ttt.scan();
    ttt.print();
    Pos pos;
    scanf("%i %i",&(pos.x),&(pos.y));
    ttt.place({pos.x-1,pos.y-1});
    ttt.print();

    return 0;
}