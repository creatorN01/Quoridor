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
#include "Common/common.h"
#include "ViewModel/state/abstractStateNode.h"
#include "ViewModel/state/activePlayerStateNode.h"
#include "ViewModel/state/operationStateNode.h"
#include "ViewModel/state/atomicExecuteStateNode.h"
/*#include "ViewModel/command/stateTransitionCommand.h"
#include "ViewModel/command/rollbackCommand.h"
#include "ViewModel/command/selectOperationTypeCommand.h"
#include "ViewModel/command/selectPositionCommand.h"
#include "ViewModel/command/setActivePlayerCommand.h"*/



class StateMachine
{
public:
    StateMachine();
    // 设置初始状态
    void SetInitialState();
    void InitPosition();
    // 状态转移命令
    bool SetActivePlayerCommand();
    bool SelectOperationCommand(OperationType operation);
    bool SelectPositionCommand();
    bool RollbackCommand();

    // 执行命令
    void SetExecutionInfo(Direction direction, std::pair<int, int> pos1, std::pair<int, int> pos2);
    bool ExecuteMoveCommand(std::pair<int, int> position, Direction direction);
    bool ExecutePlaceBarrierCommand(std::pair<int, int> pos1, std::pair<int, int> pos2);
    bool ExecuteRemoveBarrierCommand(std::pair<int, int> pos1, std::pair<int, int> pos2);

    // 接口
    void SetPlayerNum(int num);
    void SetPosition();
    State GetCurState();

private:
    // 状态节点组成的数组 activePlayer, operation, atomicExecute, 三种状态循环往复
    std::vector<QSharedPointer<AbstractStateNode>> nodeList;
    // 表征状态的索引
    State curNodeIndex;
    // 玩家个数和坐标
    int playerNum;
    std::vector<std::pair<PlayerId, std::pair<int, int>>> curPosition;

};

#endif // STATEMACHINE_H
