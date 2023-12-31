
#ifndef COMMON_H
#define COMMON_H

enum Accessibility
{
    PASSABLE = 1,
    NOWAY = -1
};

enum PlayerId
{
    FIRST = 0,
    SECOND = 1
};

enum Direction
{
    Up,
    Down,
    Left,
    Right
};

enum OperationType
{
    Move,
    PlaceBarrier,
    RemoveBarrier
};

#define MAPSIZE 9

enum State
{
    ActivePlayer = 0,
    Operation = 1,
    AtomicExecute = 2
};

const int PLAYERNUM = 2;

enum BarrierType
{
    horizontal,
    vertical
};

enum GameStatus
{
    PLAYING = 0,
    FIRST_WIN,
    SECOND_WIN
};

#endif // COMMON_H
