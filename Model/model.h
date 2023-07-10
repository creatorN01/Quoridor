#ifndef MODEL_H
#define MODEL_H
#include "map.h"
#include <QDebug>
#include <QSharedPointer>
class Model
{
public:
    Model();
    ~Model(){qDebug() << "model dtor析构------------------------------------";}
    QSharedPointer<Map> GetMap();
    // Map &GetMapReference();
    void test(); // only demo
private:
    QSharedPointer<Map> WholeMap;
    // Map WholeMap;
};

#endif // MODEL_H
