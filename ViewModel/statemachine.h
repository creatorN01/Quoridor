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
#include "Model/model.h"
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
    bool ExecuteMoveCommand(PlayerId curActivePlayer, std::pair<int, int> position, Direction direction);
    bool ExecutePlaceBarrierCommand(std::pair<int, int> pos1, std::pair<int, int> pos2);
    bool ExecuteRemoveBarrierCommand(std::pair<int, int> pos1, std::pair<int, int> pos2);

    // 接口
    void SetPlayerNum(int num);
    void SetPosition(PlayerId activePlayer, std::pair<int, int> pos);
    State GetCurState();
    std::vector<QSharedPointer<AbstractStateNode>> GetNodeList();

//    // 绑定仿函数的方法
//    void set_get_JudgeSolution(const std::function<bool(PlayerId, int, int)>&&);
//    void set_get_Accessiable(const std::function<bool(std::pair<int, int>, std::pair<int, int>)>&&);
//    void set_get_Remove(const std::function<bool(PlayerId, std::pair<int, int>, std::pair<int, int>)>&&);
//    void set_get_Add(const std::function<bool(PlayerId, std::pair<int, int>, std::pair<int, int>)>&&);

private:
    // 状态节点组成的数组 activePlayer, operation, atomicExecute, 三种状态循环往复
    std::vector<QSharedPointer<AbstractStateNode>> nodeList;
    // 表征状态的索引
    State curNodeIndex;
    // 玩家个数和坐标
    int playerNum;
    // std::vector<std::pair<PlayerId, std::pair<int, int>>> curPosition;
    std::pair<int, int> curPosition[PLAYERNUM];

    // 为了能访问到Model层map里面的函数，设计仿函数解决
//    std::function<bool(PlayerId, int, int)> get_JudgeSolution;
//    std::function<bool(std::pair<int, int>, std::pair<int, int>)> get_Accessiable;
//    std::function<bool(PlayerId, std::pair<int, int>, std::pair<int, int>)> get_Remove;
//    std::function<bool(PlayerId, std::pair<int, int>, std::pair<int, int>)> get_Add;
};

#endif // STATEMACHINE_H
