
#ifndef ATOMICEXECUTESTATENODE_H
#define ATOMICEXECUTESTATENODE_H

#include <utility>
#include "Common/common.h"
#include "ViewModel/state/abstractStateNode.h"

class AtomicExecuteStateNode : public AbstractStateNode
{
public:
    AtomicExecuteStateNode();
    std::pair<int, int> getPosition1();
    std::pair<int, int> getPosition2();
private:
    Direction direction;
    std::pair<int, int> pos1;
    std::pair<int, int> pos2;
};

#endif // ATOMICEXECUTESTATENODE_H
