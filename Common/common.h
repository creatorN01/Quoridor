
#ifndef COMMON_H
#define COMMON_H

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


enum State
{
    ActivePlayer = 0,
    Operation = 1,
    AtomicExecute = 2
};

const int MAPSIZE = 9;
const int PLAYERNUM = 2;

#endif // COMMON_H


