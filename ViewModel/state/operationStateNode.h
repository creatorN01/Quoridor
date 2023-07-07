
#ifndef OPERATIONSTATENODE_H


#define OPERATIONSTATENODE_H

#include "ViewModel/state/abstractStateNode.h"
#include "Common/common.h"

//#include "ViewModel/state/activePlayerStateNode.h"
//#include "ViewModel/state/atomicExecuteStateNode.h"


class OperationStateNode : public AbstractStateNode
{
public:
    OperationStateNode();
    OperationType GetOperationType();
    void SetOperationType(OperationType type);

private:
    OperationType operationType;

};

#endif // OPERATIONSTATENODE_H
