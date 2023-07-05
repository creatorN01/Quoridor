
#ifndef COMMON_H
#define COMMON_H

enum PlayerId
{
    FIRST,
    SECOND
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

const int MAPSIZE = 9;


#endif // COMMON_H


