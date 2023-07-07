
#include "operationStateNode.h"

OperationStateNode::OperationStateNode()
{

}

OperationType OperationStateNode::GetOperationType()
{
    return this->operationType;
}
void OperationStateNode::SetOperationType(OperationType type)
{
    this->operationType = type;
}
