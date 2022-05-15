#pragma once
enum Player {
    NONE = 0,
    FIRST = 1,
    SECOND = 2
};
enum State {
    SECOND_PLAYER_WON = -1,
    RUNNING = 0,
    FIRST_PLAYER_WON = 1,
    TIE = 2
};
struct Pos {
    int x;
    int y;
};
