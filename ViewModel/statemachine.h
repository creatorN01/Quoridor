/*
1. 由commands调用进行状态转移——next与rollback
2. 清晰分开每个状态的层级和关系——maybe树形结构or枚举类型
3. Init
   ->ActivePlayer->SelectOperationType->SelectPos->Execute
   ->ActivePlayer->...
   ->Exit
4. 支持rollback
5. 绘制状态图
6.

*/

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>
#include <QSharedPointer>
#include "ViewModel/state/abstractStateNode.h"
#include "ViewModel/state/activePlayerStateNode.h"
#include "ViewModel/state/operationStateNode.h"
#include "ViewModel/state/atomicExecuteStateNode.h"
#include "ViewModel/stateTransitionCommand.h"


class StateMachine
{
public:
    StateMachine();

private:
    std::vector<QSharedPointer<AbstractStateNode>> nodeList;
    int curNodeIndex;
    std::vector<std::pair<int, std::pair<int, int>>> curPosition;
    StateTransitionCommand stateTransitionCommand;
};

#endif // STATEMACHINE_H
