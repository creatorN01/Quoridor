#pragma once
#ifndef MAP_H
#define MAP_H
#include "./Common/common.h"
#include <map>
typedef struct node{
    Accessibility up,down,left,right;//NodePosition
} Node;
#define NoWaytoGo -1
#define Passable 1;
class Map
{
public:
    Map();
    bool Solve(PlayerId player_id, std::pair<int,int>point);//only in judge solution
    bool JudgeSolution(PlayerId player_id, int Curr_X, int Curr_Y);
    bool Accessible(std::pair<int,int>point_1, std::pair<int,int>point_2);
    bool Remove(PlayerId player_id,std::pair<int,int>point_1 ,std::pair<int,int>point_2);
    bool Add(PlayerId player_id,std::pair<int,int>point_1 ,std::pair<int,int>point_2);
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
