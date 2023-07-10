#include "model.h"

Model::Model()
{
    this->WholeMap = QSharedPointer<Map>::create();
}

QSharedPointer<Map> Model::GetMap() /*only read data*/
{
    return this->WholeMap;
}

//Map &Model::GetMapReference() /*when need to change map*/
//{
//    return this->WholeMap;
//}

void Model::test() /*demo for usage of some functions*/
{
//    Map tmp = GetMapReference();

//    tmp.Remove(PlayerId::FIRST, std::pair<int, int>(2, 3), std::pair<int, int>(3, 3));

//    tmp.Add(PlayerId::SECOND, std::pair<int, int>(4, 4), std::pair<int, int>(5, 4));

//    Map t = GetMap();

//    bool accessible = t.Accessible(std::pair<int, int>(3, 4), std::pair<int, int>(4, 4));
//    if (accessible)
//    {
//    }

//    bool hasSolution = GetMap().JudgeSolution(PlayerId::FIRST, 3, 3);
//    if (hasSolution)
//    {
//    }
}
