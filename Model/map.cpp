#include "map.h"
#include "./Common/common.h"
Map::Map()
{
    /*initialize graph for whole , player 1 and player 2*/
    int i,j;
    for(i=0;i<MAPSIZE;i++)
    {
        for(j=0;j<MAPSIZE;j++)
        {
            graph_1[i][j].up = (i == 0) ? Accessibility::NOWAY : Accessibility::PASSABLE;
            graph_1[i][j].down = ((i + 1) == MAPSIZE) ? Accessibility::NOWAY : Accessibility::PASSABLE;
            graph_1[i][j].left = (j == 0) ? Accessibility::NOWAY : Accessibility::PASSABLE;
            graph_1[i][j].right = ((j + 1) == MAPSIZE) ? Accessibility::NOWAY : Accessibility::PASSABLE;
            map[i][j] = graph_2[i][j] = graph_1[i][j];
            visited[i][j] = 0;
        }
    }
}

bool Map::JudgeSolution(PlayerId player_id, int Curr_X, int Curr_Y)/*Solve*/
{
    for(int i=0;i<MAPSIZE;i++)
        for(int j=0;j<MAPSIZE;j++)
            visited[i][j] = 0;
    bool result = Solve(player_id, Curr_X, Curr_Y);
    return result;
}




bool Map::Solve(PlayerId player_id, int Curr_X, int Curr_Y)/*JudgeSolution*/
{
    if (Curr_X < 0 || Curr_X >= MAPSIZE || Curr_Y < 0 || Curr_Y >= MAPSIZE)/*out of range of map*/
        return false;
    visited[Curr_X][Curr_Y] = 1;
    if (player_id == PlayerId::FIRST)/*first*/
    {
        if (Curr_X == 0)/*first player reach top*/
            return true;
        bool tmp = false;
        if ((graph_1[Curr_X][Curr_Y].down == Accessibility::PASSABLE) && (visited[Curr_X + 1][Curr_Y] == 0))/*go down*/
        {
            Curr_X++;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_X--][Curr_Y] = 0; }
            else return true;
        }
        if (graph_1[Curr_X][Curr_Y].up == Accessibility::PASSABLE && visited[Curr_X - 1][Curr_Y] == 0)/*go up*/
        {
            Curr_X--;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_X++][Curr_Y] = 0; }
            else return true;
        }
        if (graph_1[Curr_X][Curr_Y].left == Accessibility::PASSABLE && visited[Curr_X][Curr_Y - 1] == 0)/*go left*/
        {
            Curr_Y--;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_X][Curr_Y++] = 0; }
            else return true;
        }
        if (graph_1[Curr_X][Curr_Y].right == Accessibility::PASSABLE && visited[Curr_X][Curr_Y + 1] == 0)/*go right*/
        {
            Curr_Y++;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_X][Curr_Y--] = 0; }
            else return true;
        }
        return false;
    }
    else/*second*/
    {
        if (Curr_X == MAPSIZE - 1)/*second player reach bottom*/
            return true;
        bool tmp = false;
        if (graph_2[Curr_X][Curr_Y].down == Accessibility::PASSABLE && visited[Curr_X + 1][Curr_Y] == 0)/*go down*/
        {
            Curr_X++;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_X--][Curr_Y] = 0; }
            else return true;
        }
        if (graph_2[Curr_X][Curr_Y].up == Accessibility::PASSABLE && visited[Curr_X - 1][Curr_Y] == 0)/*go up*/
        {
            Curr_X--;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_X++][Curr_Y] = 0; }
            else return true;
        }
        if (graph_2[Curr_X][Curr_Y].left == Accessibility::PASSABLE && visited[Curr_X][Curr_Y - 1] == 0)/*go left*/
        {
            Curr_Y--;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_X][Curr_Y++] = 0; }
            else return true;
        }
        if (graph_2[Curr_X][Curr_Y].right == Accessibility::PASSABLE && visited[Curr_X][Curr_Y + 1] == 0)/*go right*/
        {
            Curr_Y++;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_X][Curr_Y--] = 0; }
            else return true;
        }
        return false;
    }
}

bool Map::Accessible(std::pair<int,int>point_1, std::pair<int,int>point_2)/*move*/
{
    int x_1 = point_1.first;
    int y_1 = point_1.second;
    int x_2 = point_2.first;
    int y_2 = point_2.second;

    /*p_2 p_1*/
    if(x_1 == x_2 && y_1 > y_2)
    {
        if(map[x_1][y_1].left == Accessibility::PASSABLE && map[x_2][y_2].right == Accessibility::PASSABLE) return true;
        return false;
    }

    /*p_1 p_2*/
    if(x_1 == x_2 && y_1 < y_2)
    {
        if(map[x_1][y_1].right == Accessibility::PASSABLE && map[x_2][y_2].left == Accessibility::PASSABLE) return true;
        return false;
    }

     /*  p_2
         ---
         p_1   */
    if(y_1 == y_2 && x_1 > x_2)
    {
        if(map[x_1][y_1].up == Accessibility::PASSABLE && map[x_2][y_2].down == Accessibility::PASSABLE) return true;
        return false;
    }

     /*  p_1
         ---
         p_2  */
    if(y_1 == y_2 && x_1 < x_2)
    {
        if(map[x_1][y_1].down == Accessibility::PASSABLE && map[x_2][y_2].up == Accessibility::PASSABLE) return true;
        return false;
    }
    return false;
}


/*set barrier and remove edge*/
bool Map::Remove(PlayerId player_id,std::pair<int,int>point_1 ,std::pair<int,int>point_2)
{
    int x_1 = point_1.first;
    int y_1 = point_1.second;
    int x_2 = point_2.first;
    int y_2 = point_2.second;
    if(x_1 == x_2)/*竖着的杆子*/
    {
        if(y_1 < y_2)/*point_1 | point_2*/
        {
            map[x_1][y_1].right = map[x_2][y_2].left = Accessibility::NOWAY;
            if(player_id == PlayerId::FIRST)/*first*/
            {
                graph_2[x_1][y_1].right = graph_2[x_2][y_2].left = Accessibility::NOWAY;
            }else{/*second*/
                graph_1[x_1][y_1].right = graph_1[x_2][y_2].left = Accessibility::NOWAY;
            }
            return true;
        }else{/*point_2 | point_1*/
            map[x_1][y_1].left = map[x_2][y_2].right = Accessibility::NOWAY;
            if(player_id == PlayerId::FIRST)/*first*/
            {
                graph_2[x_1][y_1].left = graph_2[x_2][y_2].right = Accessibility::NOWAY;
            }else{/*second*/
                graph_1[x_1][y_1].left = graph_1[x_2][y_2].right = Accessibility::NOWAY;
            }
            return true;
        }
    }
    else if(y_1 == y_2)/*横着的杆子*/
    {
        /*  point_1
            -------
            point_2 */
        if(x_1 < x_2)
        {
            map[x_1][y_1].down = map[x_2][y_2].up = Accessibility::NOWAY;
            if(player_id == PlayerId::FIRST)/*first*/
            {
                graph_2[x_1][y_1].down = graph_2[x_2][y_2].up = Accessibility::NOWAY;
            }else{/*second*/
                graph_1[x_1][y_1].down = graph_1[x_2][y_2].up = Accessibility::NOWAY;
            }
            return true;
        }
        /*  point_2
            -------
            point_1 */
        else{
            map[x_1][y_1].up = map[x_2][y_2].down = Accessibility::NOWAY;
            if(player_id == PlayerId::FIRST)/*first*/
            {
                graph_2[x_1][y_1].up = graph_2[x_2][y_2].down = Accessibility::NOWAY;
            }else{/*second*/
                graph_1[x_1][y_1].up = graph_1[x_2][y_2].down = Accessibility::NOWAY;
            }
            return true;
        }
    }
    return false;
}


/*remove barrier and add edge*/
bool Map::Add(PlayerId player_id, std::pair<int,int>point_1 ,std::pair<int,int>point_2)
{
    int x_1 = point_1.first;
    int y_1 = point_1.second;
    int x_2 = point_2.first;
    int y_2 = point_2.second;
    if(x_1 == x_2)/*竖着的杆子*/
    {
        if(y_1 < y_2)/*point_1 | point_2*/
        {
            map[x_1][y_1].right = map[x_2][y_2].left = Accessibility::PASSABLE;
            graph_2[x_1][y_1].right = graph_2[x_2][y_2].left = Accessibility::PASSABLE;
            graph_1[x_1][y_1].right = graph_1[x_2][y_2].left = Accessibility::PASSABLE;
            return true;
        }else{/*point_2 | point_1*/
            map[x_1][y_1].left = map[x_2][y_2].right = Accessibility::PASSABLE;
            graph_2[x_1][y_1].left = graph_2[x_2][y_2].right = Accessibility::PASSABLE;
            graph_1[x_1][y_1].left = graph_1[x_2][y_2].right = Accessibility::PASSABLE;
            return true;
        }
    }
    else if(y_1 == y_2)/*横着的杆子*/
    {
        /*  point_1
            ------
            point_2   */
        if(x_1 < x_2)
        {
            map[x_1][y_1].down = map[x_2][y_2].up = Accessibility::PASSABLE;
            graph_2[x_1][y_1].down = graph_2[x_2][y_2].up = Accessibility::PASSABLE;
            graph_1[x_1][y_1].down = graph_1[x_2][y_2].up = Accessibility::PASSABLE;
            return true;
        }
        /*  point_2
            -------
            point_1  */
        else{
            map[x_1][y_1].up = map[x_2][y_2].down = Accessibility::PASSABLE;
            graph_2[x_1][y_1].up = graph_2[x_2][y_2].down = Accessibility::PASSABLE;
            graph_1[x_1][y_1].up = graph_1[x_2][y_2].down = Accessibility::PASSABLE;
            return true;
        }
    }
    return false;
}
