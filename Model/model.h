#ifndef MODEL_H
#define MODEL_H
#include "map.h"
class Model
{
public:
    Model();
    Map GetMap();
    Map& GetMapReference();
    void test();//only demo
private:
    Map WholeMap;
};

#endif // MODEL_H
