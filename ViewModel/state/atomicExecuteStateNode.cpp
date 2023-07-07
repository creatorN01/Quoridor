
#include "atomicExecuteStateNode.h"

AtomicExecuteStateNode::AtomicExecuteStateNode()
{

}

Direction AtomicExecuteStateNode::GetDirection()
{
    return this->direction;
}
std::pair<int, int> AtomicExecuteStateNode::GetPosition1()
{
    return this->pos1;
}
std::pair<int, int> AtomicExecuteStateNode::GetPosition2()
{
    return this->pos2;
}


void AtomicExecuteStateNode::SetDirection(Direction direction_)
{
    this->direction = direction_;
}
void AtomicExecuteStateNode::SetPosition(std::pair<int, int> pos1_, std::pair<int, int> pos2_)
{
    this->pos1 = pos1_;
    this->pos2 = pos2_;
}

