#pragma once
#ifndef MAP_H
#define MAP_H
//#include "common.h"
#include<map>
const int MAPSIZE = 10;//map is mapsize*mapsize graph
//typedef struct node_position
//{
//    int x,y;
//} NodePosition;
typedef struct node{
    int up,down,left,right;//NodePosition
} Node;
#define NoWaytoGo -1
#define Passable 1;
class Map
{
public:
    Map();
    bool JudgeSolution(PlayerId player_id, int Curr_X, int Curr_Y);
    bool Accessible(std::pair<int,int>point_1, std::pair<int,int>point_2);
    bool Remove(std::pair<int,int>point_1 ,std::pair<int,int>point_2);
    bool Add(std::pair<int,int>point_1 ,std::pair<int,int>point_2);
private:
    Node map[MAPSIZE][MAPSIZE];//graph
    Node graph_1[MAPSIZE][MAPSIZE];
    Node graph_2[MAPSIZE][MAPSIZE];
    int visited[MAPSIZE][MAPSIZE];//only used in judge solution
//    int map[MAPSIZE][MAPSIZE];//graph
//    int graph_1[MAPSIZE][MAPSIZE];
//    int graph_2[MAPSIZE][MAPSIZE];
};

#endif // MAP_H
