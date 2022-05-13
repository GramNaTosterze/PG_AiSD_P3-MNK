#pragma once
enum Player {
    NONE = 0,
    FIRST = 1,
    SECOND = 2
};
enum State {
    RUNNING = 0,
    PLAYER_WON = 1,
    TIE = 2
};
struct Pos {
    int x;
    int y;
};