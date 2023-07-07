
#ifndef ATOMICEXECUTESTATENODE_H
#define ATOMICEXECUTESTATENODE_H

#include <utility>
#include "Common/common.h"
#include "ViewModel/state/abstractStateNode.h"

class AtomicExecuteStateNode : public AbstractStateNode
{
public:
    AtomicExecuteStateNode();

    void SetDirection(Direction direction_);
    void SetPosition(std::pair<int, int> pos1_, std::pair<int, int> pos2_);

    Direction GetDirection();
    std::pair<int, int> GetPosition1();
    std::pair<int, int> GetPosition2();
private:
    Direction direction;
    std::pair<int, int> pos1;
    std::pair<int, int> pos2;
};

#endif // ATOMICEXECUTESTATENODE_H
