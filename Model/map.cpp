#include "map.h"
#include "./Common/common.h"
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

bool Map::Solve(PlayerId player_id, int Curr_X, int Curr_Y)
{
    for(int i=0;i<MAPSIZE;i++)
        for(int j=0;j<MAPSIZE;j++)
            visited[i][j] = 0;
    bool result = JudgeSolution(player_id, Curr_X, Curr_Y);
    return result;
}
bool Map::JudgeSolution(PlayerId player_id, int Curr_X, int Curr_Y)
{
    visited[Curr_X][Curr_Y] = 1;
    if(player_id==PlayerId::FIRST)//first
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
        if(graph_1[Curr_X][Curr_Y].up == Passable && visited[Curr_X-1][Curr_Y] == 0)//go up
        {
            Curr_X--;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X++][Curr_Y] = 0;}
            else return true;
        }
        if(graph_1[Curr_X][Curr_Y].left == Passable && visited[Curr_X][Curr_Y-1] == 0)//go left
        {
            Curr_Y--;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X][Curr_Y++] = 0;}
            else return true;
        }
        if(graph_1[Curr_X][Curr_Y].right == Passable && visited[Curr_X][Curr_Y+1] == 0)//go right
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
        if(graph_2[Curr_X][Curr_Y].up == Passable && visited[Curr_X-1][Curr_Y] == 0)//go up
        {
            Curr_X--;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X++][Curr_Y] = 0;}
            else return true;
        }
        if(graph_2[Curr_X][Curr_Y].left == Passable && visited[Curr_X][Curr_Y-1] == 0)//go left
        {
            Curr_Y--;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X][Curr_Y++] = 0;}
            else return true;
        }
        if(graph_2[Curr_X][Curr_Y].right == Passable && visited[Curr_X][Curr_Y+1] == 0)//go right
        {
            Curr_Y++;
            tmp = JudgeSolution(player_id, Curr_X, Curr_Y);
            if(tmp==false){ visited[Curr_X][Curr_Y--] = 0;}
            else return true;
        }
        return false;
    }
}

bool Map::Accessible(std::pair<int,int>point_1, std::pair<int,int>point_2)//move
{
    int x_1 = point_1.first;
    int y_1 = point_1.second;
    int x_2 = point_2.first;
    int y_2 = point_2.second;

    // p_2 p_1
    if(x_1 == x_2 && y_1 > y_2)
    {
        if(map[x_1][y_1].left == Passable && map[x_2][y_2].right == Passable) return true;
        return false;
    }

    // p_1 p_2
    if(x_1 == x_2 && y_1 < y_2)
    {
        if(map[x_1][y_1].right == Passable && map[x_2][y_2].left == Passable) return true;
        return false;
    }

    // p_2 
    // ---
    // p_1
    if(y_1 == y_2 && x_1 > x_2)
    {
        if(map[x_1][y_1].up == Passable && map[x_2][y_2].down == Passable) return true;
        return false;
    }

    // p_1 
    // ---
    // p_2
    if(y_1 == y_2 && x_1 < x_2)
    {
        if(map[x_1][y_1].down == Passable && map[x_2][y_2].up == Passable) return true;
        return false;
    }
}
bool Map::Remove(PlayerId player_id,std::pair<int,int>point_1 ,std::pair<int,int>point_2)//set barrier
{
    int x_1 = point_1.first;
    int y_1 = point_1.second;
    int x_2 = point_2.first;
    int y_2 = point_2.second;
    if(x_1 == x_2)//竖着的杆子
    {
        if(y_1 < y_2)// point_1 | point_2
        {
            map[x_1][y_1].right = map[x_2][y_2].left = NoWaytoGo;
            if(player_id == PlayerId::FIRST)//first
            {
                graph_2[x_1][y_1].right = graph_2[x_2][y_2].left = NoWaytoGo;
            }else{//second
                graph_1[x_1][y_1].right = graph_1[x_2][y_2].left = NoWaytoGo;
            }
            return true;
        }else{//  point_2 | point_1
            map[x_1][y_1].left = map[x_2][y_2].right = NoWaytoGo;
            if(player_id == PlayerId::FIRST)//first
            {
                graph_2[x_1][y_1].left = graph_2[x_2][y_2].right = NoWaytoGo;
            }else{//second
                graph_1[x_1][y_1].left = graph_1[x_2][y_2].right = NoWaytoGo;
            }
            return true;
        }
    }
    else if(y_1 == y_2)//横着的杆子
    {
        //point_1
        //-------
        //point_2
        if(x_1 < x_2)
        {
            map[x_1][y_1].down = map[x_2][y_2].up = NoWaytoGo;
            if(player_id == PlayerId::FIRST)//first
            {
                graph_2[x_1][y_1].down = graph_2[x_2][y_2].up = NoWaytoGo;
            }else{//second
                graph_1[x_1][y_1].down = graph_1[x_2][y_2].up = NoWaytoGo;
            }
            return true;
        }
        //point_2
        //-------
        //point_1
        else{
            map[x_1][y_1].up = map[x_2][y_2].down = NoWaytoGo;
            if(player_id == PlayerId::FIRST)//first
            {
                graph_2[x_1][y_1].up = graph_2[x_2][y_2].down = NoWaytoGo;
            }else{//second
                graph_1[x_1][y_1].up = graph_1[x_2][y_2].down = NoWaytoGo;
            }
            return true;
        }
    }
}
bool Map::Add(PlayerId player_id, std::pair<int,int>point_1 ,std::pair<int,int>point_2)
{
    int x_1 = point_1.first;
    int y_1 = point_1.second;
    int x_2 = point_2.first;
    int y_2 = point_2.second;
    if(x_1 == x_2)//竖着的杆子
    {
        if(y_1 < y_2)// point_1 | point_2
        {
            map[x_1][y_1].right = map[x_2][y_2].left = Passable;
            if(player_id == PlayerId::FIRST)//first
            {
                graph_2[x_1][y_1].right = graph_2[x_2][y_2].left = Passable;
            }else{//second
                graph_1[x_1][y_1].right = graph_1[x_2][y_2].left = Passable;
            }
            return true;
        }else{//  point_2 | point_1
            map[x_1][y_1].left = map[x_2][y_2].right = Passable;
            if(player_id == PlayerId::FIRST)//first
            {
                graph_2[x_1][y_1].left = graph_2[x_2][y_2].right = Passable;
            }else{//second
                graph_1[x_1][y_1].left = graph_1[x_2][y_2].right = Passable;
            }
            return true;
        }
    }
    else if(y_1 == y_2)//横着的杆子
    {
        //point_1
        //------
        //point_2
        if(x_1 < x_2)
        {
            map[x_1][y_1].down = map[x_2][y_2].up = Passable;
            if(player_id == PlayerId::FIRST)//first
            {
                graph_2[x_1][y_1].down = graph_2[x_2][y_2].up = Passable;
            }else{//second
                graph_1[x_1][y_1].down = graph_1[x_2][y_2].up = Passable;
            }
            return true;
        }
        //point_2
        //-------
        //point_1
        else{
            map[x_1][y_1].up = map[x_2][y_2].down = Passable;
            if(player_id == PlayerId::FIRST)//first
            {
                graph_2[x_1][y_1].up = graph_2[x_2][y_2].down = Passable;
            }else{//second
                graph_1[x_1][y_1].up = graph_1[x_2][y_2].down = Passable;
            }
            return true;
        }
    }
}