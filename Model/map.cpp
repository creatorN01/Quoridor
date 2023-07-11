#include "map.h"
#include "./Common/common.h"
#include <QDebug>
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




bool Map::JudgeSolution(PlayerId player_id, std::pair<int, int> point)
{
    for(int i=0;i<MAPSIZE;i++)
        for(int j=0;j<MAPSIZE;j++)
            visited[i][j] = 0;
    int Curr_X = point.second;
    int Curr_Y = point.first;
    bool result = Solve(player_id, Curr_X, Curr_Y);
    return result;
}




bool Map::Solve(PlayerId player_id, int Curr_X, int Curr_Y)//
{
    if (Curr_X < 0 || Curr_X >= MAPSIZE || Curr_Y < 0 || Curr_Y >= MAPSIZE)//out of range of map
        return false;
    visited[Curr_Y][Curr_X] = 1;
    if (player_id == PlayerId::FIRST)//first
    {
        if (Curr_Y == 0)//reach top Curr_X
            return true;
        bool tmp = false;
        if ((graph_1[Curr_Y][Curr_X].down == Accessibility::PASSABLE) && (visited[Curr_Y + 1][Curr_X] == 0))//go down
        {
            Curr_Y++;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_Y--][Curr_X] = 0; }
            else return true;
        }
        if (graph_1[Curr_Y][Curr_X].up == Accessibility::PASSABLE && visited[Curr_Y - 1][Curr_X] == 0)//go up
        {
            Curr_Y--;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_Y++][Curr_X] = 0; }
            else return true;
        }
        if (graph_1[Curr_Y][Curr_X].left == Accessibility::PASSABLE && visited[Curr_Y][Curr_X - 1] == 0)//go left
        {
            Curr_X--;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_Y][Curr_X++] = 0; }
            else return true;
        }
        if (graph_1[Curr_Y][Curr_X].right == Accessibility::PASSABLE && visited[Curr_Y][Curr_X + 1] == 0)//go right
        {
            Curr_X++;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_Y][Curr_X--] = 0; }
            else return true;
        }
        return false;
    }
    else//second
    {
        if (Curr_Y == MAPSIZE - 1)//reach Curr_X
            return true;
        bool tmp = false;
        if (graph_2[Curr_Y][Curr_X].down == Accessibility::PASSABLE && visited[Curr_Y + 1][Curr_X] == 0)//go down
        {
            Curr_Y++;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_Y--][Curr_X] = 0; }
            else return true;
        }
        if (graph_2[Curr_Y][Curr_X].up == Accessibility::PASSABLE && visited[Curr_Y - 1][Curr_X] == 0)//go up
        {
            Curr_Y--;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_Y++][Curr_X] = 0; }
            else return true;
        }
        if (graph_2[Curr_Y][Curr_X].left == Accessibility::PASSABLE && visited[Curr_Y][Curr_X - 1] == 0)//go left
        {
            Curr_X--;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_Y][Curr_X++] = 0; }
            else return true;
        }
        if (graph_2[Curr_Y][Curr_X].right == Accessibility::PASSABLE && visited[Curr_Y][Curr_X + 1] == 0)//go right
        {
            Curr_X++;
            tmp = Solve(player_id, Curr_X, Curr_Y);
            if (tmp == false) { visited[Curr_Y][Curr_X--] = 0; }
            else return true;
        }
        return false;
    }
}

//bool Map::Accessible(std::pair<int, int>point_1, std::pair<int, int>point_2)//move
//{
//    int y_1 = point_1.first;
//    int x_1 = point_1.second;
//    int y_2 = point_2.first;
//    int x_2 = point_2.second;
//    qDebug() << " y_1 " << y_1 << " x_1 " << x_1<< " y_2 " << y_2 << " x_2 " << x_2;
//    if (x_1 < 0 || x_1 >= MAPSIZE || y_1 < 0 || y_1 >= MAPSIZE) /*point_1 out of range*/
//        return false;
//    if (x_2 < 0 || x_2 >= MAPSIZE || y_2 < 0 || y_2 >= MAPSIZE) /*point_2 out of range*/
//        return false;
//    // p_2 p_1
//    if (y_1 == y_2 && x_1 > x_2)
//    {
//        if (map[y_1][x_1].left == Accessibility::PASSABLE && map[y_2][x_2].right == Accessibility::PASSABLE) return true;
//        return false;
//    }

//    // p_1 p_2
//    if (y_1 == y_2 && x_1 < x_2)
//    {
//        if (map[y_1][x_1].right == Accessibility::PASSABLE && map[y_2][x_2].left == Accessibility::PASSABLE) return true;
//        return false;
//    }

//    // p_2
//    // ---
//    // p_1
//    if (x_1 == x_2 && y_1 > y_2)
//    {
//        if (map[y_1][x_1].up == Accessibility::PASSABLE && map[y_2][x_2].down == Accessibility::PASSABLE) return true;
//        return false;
//    }

//    // p_1
//    // ---
//    // p_2
//    if (x_1 == x_2 && y_1 < y_2)
//    {
//        if (map[y_1][x_1].down == Accessibility::PASSABLE && map[y_2][x_2].up == Accessibility::PASSABLE) return true;
//        return false;
//    }
//    return false;//unexpected situation
//}

bool Map::Accessible(std::pair<int,int>point_1, std::pair<int,int>point_2)/*move*/
{
//    int x_1 = point_1.first;
//    int y_1 = point_1.second;
//    int x_2 = point_2.first;
//    int y_2 = point_2.second;
        int y_1 = point_1.first;
        int x_1 = point_1.second;
        int y_2 = point_2.first;
        int x_2 = point_2.second;

    qDebug() << "Map::Accessible" ;
    qDebug() << "point_1" << " fir " << x_1 << " sec " << y_1;
    qDebug() << "point_2" << " fir " << x_2 << " sec " << y_2;
    /*p_2 p_1*/
    if(x_1 == x_2 && y_1 > y_2)
    {
        qDebug() << "x_1 == x_2 && y_1 > y_2";
        if(map[x_1][y_1].left == Accessibility::PASSABLE && map[x_2][y_2].right == Accessibility::PASSABLE) return true;

        return false;
    }

    /*p_1 p_2*/
    if(x_1 == x_2 && y_1 < y_2)
    {
        qDebug() << "x_1 == x_2 && y_1 < y_2";
        if(map[x_1][y_1].right == Accessibility::PASSABLE && map[x_2][y_2].left == Accessibility::PASSABLE) return true;

        return false;
    }

    /*  p_2
         ---
         p_1   */
    if(y_1 == y_2 && x_1 > x_2)
    {
        qDebug() << "y_1 == y_2 && x_1 > x_2";
        if(map[x_1][y_1].up == Accessibility::PASSABLE && map[x_2][y_2].down == Accessibility::PASSABLE) return true;

        return false;
    }

    /*  p_1
         ---
         p_2  */
    if(y_1 == y_2 && x_1 < x_2)
    {
        qDebug() << "y_1 == y_2 && x_1 < x_2";
        qDebug() << "map[" << x_1 << "][" << y_1 << "].down" << map[x_1][y_1].down;
        qDebug() << "map[" << x_2 << "][" << y_2 << "].up" << map[x_2][y_2].up;
        // this->PrintMap();
        if(map[x_1][y_1].down == Accessibility::PASSABLE && map[x_2][y_2].up == Accessibility::PASSABLE) return true;

        return false;
    }
    return false;
}


///*set barrier and remove edge*/
//bool Map::Remove(PlayerId player_id, std::pair<int, int>point_1, std::pair<int, int>point_2)//set barrier
//{
//    int y_1 = point_1.first;
//    int x_1 = point_1.second;
//    int y_2 = point_2.first;
//    int x_2 = point_2.second;
//    if (y_1 == y_2)//竖着的杆子
//    {
//        if (x_1 < x_2)// point_1 | point_2
//        {
//            map[y_1][x_1].right = map[y_2][x_2].left = Accessibility::NOWAY;
//            if (player_id == PlayerId::FIRST)//first
//            {
//                graph_2[y_1][x_1].right = graph_2[y_2][x_2].left = Accessibility::NOWAY;
//            }
//            else {//second
//                graph_1[y_1][x_1].right = graph_1[y_2][x_2].left = Accessibility::NOWAY;
//            }
//            return true;
//        }
//        else {//  point_2 | point_1
//            map[y_1][x_1].left = map[y_2][x_2].right = Accessibility::NOWAY;
//            if (player_id == PlayerId::FIRST)//first
//            {
//                graph_2[y_1][x_1].left = graph_2[y_2][x_2].right = Accessibility::NOWAY;
//            }
//            else {//second
//                graph_1[y_1][x_1].left = graph_1[y_2][x_2].right = Accessibility::NOWAY;
//            }
//            return true;
//        }
//    }
//    else if (x_1 == x_2)//横着的杆子
//    {
//        //point_1
//        //-------
//        //point_2
//        if (y_1 < y_2)
//        {
//            map[y_1][x_1].down = map[y_2][x_2].up = Accessibility::NOWAY;
//            if (player_id == PlayerId::FIRST)//first
//            {
//                graph_2[y_1][x_1].down = graph_2[y_2][x_2].up = Accessibility::NOWAY;
//            }
//            else {//second
//                graph_1[y_1][x_1].down = graph_1[y_2][x_2].up = Accessibility::NOWAY;
//            }
//            return true;
//        }
//        //point_2
//        //-------
//        //point_1
//        else {
//            map[y_1][x_1].up = map[y_2][x_2].down = Accessibility::NOWAY;
//            if (player_id == PlayerId::FIRST)//first
//            {
//                graph_2[y_1][x_1].up = graph_2[y_2][x_2].down = Accessibility::NOWAY;
//            }
//            else {//second
//                graph_1[y_1][x_1].up = graph_1[y_2][x_2].down = Accessibility::NOWAY;
//            }
//            return true;
//        }
//    }
//    return false;//unexpected situation
//}

/*set barrier and remove edge*/
bool Map::Remove(PlayerId player_id,std::pair<int,int>point_1 ,std::pair<int,int>point_2)
{
//    int x_1 = point_1.first;
//    int y_1 = point_1.second;
//    int x_2 = point_2.first;
//    int y_2 = point_2.second;
    int y_1 = point_1.first;
    int x_1 = point_1.second;
    int y_2 = point_2.first;
    int x_2 = point_2.second;
    qDebug() << "Map::Remove" ;
    qDebug() << "point_1" << " fir " << x_1 << " sec " << y_1;
    qDebug() << "point_2" << " fir " << x_2 << " sec " << y_2;
        if (x_1 < 0 || x_1 >= MAPSIZE || y_1 < 0 || y_1 >= MAPSIZE) /*point_1 out of range*/
            return false;
        if (x_2 < 0 || x_2 >= MAPSIZE || y_2 < 0 || y_2 >= MAPSIZE) /*point_2 out of range*/
            return false;
    if(x_1 == x_2)/*竖着的杆子*/
    {
        if(y_1 < y_2)/*point_1 | point_2*/
        {
            qDebug() << "x_1 == x_2 && y_1 < y_2";
            map[x_1][y_1].right = map[x_2][y_2].left = Accessibility::NOWAY;
            if(player_id == PlayerId::FIRST)/*first*/
            {
                graph_2[x_1][y_1].right = graph_2[x_2][y_2].left = Accessibility::NOWAY;
            }else{/*second*/
                graph_1[x_1][y_1].right = graph_1[x_2][y_2].left = Accessibility::NOWAY;
            }
            qDebug() << "after remove";
            //this->PrintMap();
            return true;
        }else{/*point_2 | point_1*/
            qDebug() << "x_1 == x_2 && y_1 > y_2";
            map[x_1][y_1].left = map[x_2][y_2].right = Accessibility::NOWAY;
            if(player_id == PlayerId::FIRST)/*first*/
            {
                graph_2[x_1][y_1].left = graph_2[x_2][y_2].right = Accessibility::NOWAY;
            }else{/*second*/
                graph_1[x_1][y_1].left = graph_1[x_2][y_2].right = Accessibility::NOWAY;
            }
            qDebug() << "after remove";
            //this->PrintMap();
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
            qDebug() << "x_1 < x_2 && y_1 == y_2";
            map[x_1][y_1].down = map[x_2][y_2].up = Accessibility::NOWAY;
            if(player_id == PlayerId::FIRST)/*first*/
            {
                graph_2[x_1][y_1].down = graph_2[x_2][y_2].up = Accessibility::NOWAY;
            }else{/*second*/
                graph_1[x_1][y_1].down = graph_1[x_2][y_2].up = Accessibility::NOWAY;
            }
            qDebug() << "after remove";
            // this->PrintMap();
            return true;
        }
        /*  point_2
            -------
            point_1 */
        else{
            qDebug() << "x_1 > x_2 && y_1 == y_2";
            map[x_1][y_1].up = map[x_2][y_2].down = Accessibility::NOWAY;
            if(player_id == PlayerId::FIRST)/*first*/
            {
                graph_2[x_1][y_1].up = graph_2[x_2][y_2].down = Accessibility::NOWAY;
            }else{/*second*/
                graph_1[x_1][y_1].up = graph_1[x_2][y_2].down = Accessibility::NOWAY;
            }
            qDebug() << "after remove";
           // this->PrintMap();
            return true;
        }
    }
    return false;
}


/*remove barrier and add edge*/
bool Map::Add(PlayerId player_id, std::pair<int, int>point_1, std::pair<int, int>point_2)
{
//    int y_1 = point_1.first;
//    int x_1 = point_1.second;
//    int y_2 = point_2.first;
//    int x_2 = point_2.second;

    int y_1 = point_1.second;
    int x_1 = point_1.first;
    int y_2 = point_2.second;
    int x_2 = point_2.first;
    qDebug() << "Map::Add" ;
    qDebug() << "point_1" << " fir " << x_1 << " sec " << y_1;
    qDebug() << "point_2" << " fir " << x_2 << " sec " << y_2;
    if (y_1 == y_2)/*竖着的杆子*/
    {
        if (x_1 < x_2)/*point_1 | point_2*/
        {
            map[y_1][x_1].right = map[y_2][x_2].left = Accessibility::PASSABLE;
            graph_2[y_1][x_1].right = graph_2[y_2][x_2].left = Accessibility::PASSABLE;
            graph_1[y_1][x_1].right = graph_1[y_2][x_2].left = Accessibility::PASSABLE;

            qDebug() << "after add";
            //this->PrintMap();

            return true;
        }
        else {/*point_2 | point_1*/
            map[y_1][x_1].left = map[y_2][x_2].right = Accessibility::PASSABLE;
            graph_2[y_1][x_1].left = graph_2[y_2][x_2].right = Accessibility::PASSABLE;
            graph_1[y_1][x_1].left = graph_1[y_2][x_2].right = Accessibility::PASSABLE;

            qDebug() << "after add";
            //this->PrintMap();

            return true;
        }
    }
    else if (x_1 == x_2)/*横着的杆子*/
    {
        /*  point_1
            ------
            point_2   */
        if (y_1 < y_2)
        {
            map[y_1][x_1].down = map[y_2][x_2].up = Accessibility::PASSABLE;
            graph_2[y_1][x_1].down = graph_2[y_2][x_2].up = Accessibility::PASSABLE;
            graph_1[y_1][x_1].down = graph_1[y_2][x_2].up = Accessibility::PASSABLE;

            qDebug() << "after add";
           // this->PrintMap();

            return true;
        }
        /*  point_2
            -------
            point_1  */
        else {
            map[y_1][x_1].up = map[y_2][x_2].down = Accessibility::PASSABLE;
            graph_2[y_1][x_1].up = graph_2[y_2][x_2].down = Accessibility::PASSABLE;
            graph_1[y_1][x_1].up = graph_1[y_2][x_2].down = Accessibility::PASSABLE;

            qDebug() << "after add";
            //this->PrintMap();

            return true;
        }
    }
    return false;
}

// test
void Map::PrintMap()
{
    /*  map  */
    for (int i = 0; i < MAPSIZE; i++)
    {
        for (int j = 0; j < MAPSIZE; j++)
        {
            qDebug() << "(i,j,map[i][j]) = (" << i << "," << j << ")" ;
             qDebug() << "(map[i][j].up) = (" << map[i][j].up << ")" ;
             qDebug() << "(map[i][j].down) = (" << map[i][j].down << ")" ;;
             qDebug() << "(map[i][j].left) = (" << map[i][j].left << ")" ;
             qDebug() << "(map[i][j].right) = (" << map[i][j].right << ")" ;
        }
    }
}


bool Map::JudgePlaceBarrier(BarrierType bt, std::pair<int,int>point_1, std::pair<int,int>point_2,
                            std::pair<int,int>point_3, std::pair<int,int>point_4)
{
    /*  1 2
            3 4   */
    bool _1_2_accessible = false, _3_4_accessible = false;
    bool _1_3_accessible = false, _2_4_accessible = false;
    if(bt == BarrierType::horizontal)
    {
        _1_2_accessible = this->Accessible(point_1,point_2);
        _3_4_accessible = this->Accessible(point_3,point_4);
        if(_1_2_accessible == false && _3_4_accessible == false) return false;
        return true;
    }else
    {
        _1_3_accessible = this->Accessible(point_1,point_3);
        _2_4_accessible = this->Accessible(point_2,point_4);
        if(_1_3_accessible == false && _2_4_accessible == false) return false;
        return true;
    }
    return false; /*exception*/
}
