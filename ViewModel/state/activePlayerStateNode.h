
#ifndef ACTIVEPLAYERSTATENODE_H
#define ACTIVEPLAYERSTATENODE_H


#include "Common/common.h"
#include "ViewModel/state/abstractStateNode.h"
//#include "ViewModel/state/atomicExecuteStateNode.h"
//#include "ViewModel/state/operationStateNode.h"

class ActivePlayerStateNode : public AbstractStateNode
{
public:
    ActivePlayerStateNode();
    int GetActivePlayer();
    int GetWaitedPlayer();
private:
    PlayerId activePlayer = FIRST;
    PlayerId waitedPlayer = SECOND;

//    // 前驱节点
//    AtomicExecuteStateNode preNode;
//    // 后继节点
//    OperationStateNode nextNode;
};

#endif // ACTIVEPLAYERSTATENODE_H
