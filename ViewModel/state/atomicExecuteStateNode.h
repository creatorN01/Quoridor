
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
    void SetPlaceBarrierPos(std::pair<int, int> pos1_, std::pair<int, int> pos2_, std::pair<int, int> pos3_, std::pair<int, int> pos4_);
    void SetBarrierType(BarrierType type_);

    Direction GetDirection();
    std::pair<int, int> GetPosition1();
    std::pair<int, int> GetPosition2();
private:
    // 用于Move的数据
    Direction direction;
    std::pair<int, int> pos1;
    std::pair<int, int> pos2;

    // 用于PlaceBarrier的数据
    BarrierType barrierType;
    std::pair<int, int> PlacePos1;
    std::pair<int, int> PlacePos2;
    std::pair<int, int> PlacePos3;
    std::pair<int, int> PlacePos4;
};

#endif // ATOMICEXECUTESTATENODE_H
