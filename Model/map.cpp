#include "map.h"

Map::Map()
{
    //initialize graph for whole , player 1 and player 2
    int i,j;
    for(i=0;i<MAPSIZE;i++)
    {
        for(j=0;j<MAPSIZE;j++)
        {
            graph_1[i][j].up = (i == 0) ? NoWaytoGo : Passable;
            graph_1[i][j].down = ((i+1) == MAPSIZE) ? NoWaytoGo : Passable ;
            graph_1[i][j].left = (j == 0) ? NoWaytoGo : Passable;
            graph_1[i][j].right = ((j+1) == MAPSIZE) ? NoWaytoGo : Passable ;
            //            graph_1[i][j].up.x = i-1;
            //            graph_1[i][j].up.y = j;
            //            graph_1[i][j].down.x = ((i+1) == MAPSIZE) ? NoWaytoGo : (i+1) ;
            //            graph_1[i][j].down.y = j;
            //            graph_1[i][j].left.x = i;
            //            graph_1[i][j].left.y = j-1;
            //            graph_1[i][j].right.x = i;
            //            graph_1[i][j].right.y = ((j+1)==MAPSIZE) ? NoWaytoGo : (j+1) ;
        }
        map[i][j] = graph_2[i][j] = graph_1[i][j];
        visited[i][j] = 0;
    }
}

/*
bool Map::JudgeSolution(int player_id, int Curr_X, int Curr_Y)
{
    visited[Curr_X][Curr_Y] = 1;
    if(player_id==1)//first
    {
        if(Curr_X==MAPSIZE-1)//reach
            return true;
        bool tmp = false;
        if(graph_1[Curr_X][Curr_Y].down == Passable && visited[Curr_X+1][Curr_Y] == 0)//go down
        {
            Curr_X++;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X--][Curr_Y] = 0;}
            else return true;
        }
        if(graph_1[Curr_X][Curr_Y].up == Passable && visited[Curr_X-1][Curr_Y] == 0)//go down
        {
            Curr_X--;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X++][Curr_Y] = 0;}
            else return true;
        }
        if(graph_1[Curr_X][Curr_Y].left == Passable && visited[Curr_X][Curr_Y-1] == 0)//go down
        {
            Curr_Y--;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X][Curr_Y++] = 0;}
            else return true;
        }
        if(graph_1[Curr_X][Curr_Y].right == Passable && visited[Curr_X][Curr_Y+1] == 0)//go down
        {
            Curr_Y++;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X][Curr_Y--] = 0;}
            else return true;
        }
        return false;
    }
    else//second
    {
        if(Curr_X==0)//reach
            return true;
        bool tmp = false;
        if(graph_2[Curr_X][Curr_Y].down == Passable && visited[Curr_X+1][Curr_Y] == 0)//go down
        {
            Curr_X++;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X--][Curr_Y] = 0;}
            else return true;
        }
        if(graph_2[Curr_X][Curr_Y].up == Passable && visited[Curr_X-1][Curr_Y] == 0)//go down
        {
            Curr_X--;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X++][Curr_Y] = 0;}
            else return true;
        }
        if(graph_2[Curr_X][Curr_Y].left == Passable && visited[Curr_X][Curr_Y-1] == 0)//go down
        {
            Curr_Y--;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X][Curr_Y++] = 0;}
            else return true;
        }
        if(graph_2[Curr_X][Curr_Y].right == Passable && visited[Curr_X][Curr_Y+1] == 0)//go down
        {
            Curr_Y++;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X][Curr_Y--] = 0;}
            else return true;
        }
        return false;
    }
}
*/
