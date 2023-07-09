
#include "statemachine.h"

StateMachine::StateMachine()
{
    // 初始化nodeList
    QSharedPointer<AbstractStateNode> activePlayer = QSharedPointer<ActivePlayerStateNode>::create();
    QSharedPointer<AbstractStateNode> operation = QSharedPointer<OperationStateNode>::create();
    QSharedPointer<AbstractStateNode> atomicExecute = QSharedPointer<AtomicExecuteStateNode>::create();
    nodeList.push_back(activePlayer);
    nodeList.push_back(operation);
    nodeList.push_back(atomicExecute);
    // curNodeIndex和curPosition放在InitGameEnv()来设置
    // 各种command类已经删掉，换成了成员函数
}

void StateMachine::SetPlayerNum(int num)
{
    this->playerNum = num;
}



void StateMachine::InitPosition()
{
    std::pair<int, int> p2(0,4);
    std::pair<int, int> p1(8,4);
    std::pair<PlayerId, std::pair<int, int>> position1(FIRST, p1);
    std::pair<PlayerId, std::pair<int, int>> position2(SECOND, p2);
    curPosition.push_back(position1);
    curPosition.push_back(position2);
}

void StateMachine::SetInitialState()
{
    this->curNodeIndex = ActivePlayer;
    auto tran = this->nodeList[curNodeIndex].get();
    auto curNode = static_cast<ActivePlayerStateNode *>(tran);
    curNode->SetActivePlayer(FIRST);
    curNode->SetWaitedPlayer(SECOND);
}

State StateMachine::GetCurState()
{
    return this->curNodeIndex;
}

bool StateMachine::SetActivePlayerCommand()
{
    this->curNodeIndex = ActivePlayer;
    auto tran = this->nodeList[curNodeIndex].get();
    auto curNode = static_cast<ActivePlayerStateNode *>(tran);
    PlayerId trans = curNode->GetActivePlayer();
    curNode->SetActivePlayer(curNode->GetWaitedPlayer());
    curNode->SetWaitedPlayer(trans);
    return true;
}

bool StateMachine::SelectOperationCommand(OperationType operation)
{
    if(this->curNodeIndex != ActivePlayer) return false;
    curNodeIndex = Operation;
    auto tran = this->nodeList[curNodeIndex].get();
    auto curNode = static_cast<OperationStateNode *>(tran);
    curNode->SetOperationType(operation);
    return true;
}



bool StateMachine::SelectPositionCommand()
{
    // 一个大大的问题是，如何把view层的数据导入到AtomicExecuteStateNode当中
    if(this->curNodeIndex != Operation) return false;


    auto tran = this->nodeList[Operation].get();
    auto curOperationTypeNode = static_cast<OperationStateNode *>(tran);

    auto tran2 = this->nodeList[ActivePlayer].get();
    auto curActivePlayerNode = static_cast<ActivePlayerStateNode *>(tran2);
    auto curActivePlayer = curActivePlayerNode->GetActivePlayer();

    auto tran3 = this->nodeList[AtomicExecute].get();
    auto curNode = static_cast<AtomicExecuteStateNode *>(tran3);

    std::pair<int, int> position = this->curPosition[curActivePlayer].second;
    Direction direction = curNode->GetDirection();
    std::pair<int, int> pos1 = curNode->GetPosition1();
    std::pair<int, int> pos2 = curNode->GetPosition2();
    // 修改Model层的数据
    switch (curOperationTypeNode->GetOperationType())
    {
      case Move:
        // 传什么参数?坐标和方向
        // 调用执行函数
        if (this->ExecuteMoveCommand(curActivePlayer, position, direction) == false) return false;
        break;
      case PlaceBarrier:
        // 传什么参数?两个点的坐标
        if (this->ExecutePlaceBarrierCommand(pos1, pos2) == false) return false;
        break;
      case RemoveBarrier:
        if (this->ExecuteRemoveBarrierCommand(pos1, pos2) == false) return false;
        break;
    }
    curNodeIndex = AtomicExecute;
    // 进行到这里说明Model已经执行成功了，这时就可以修改ViewModel层面的数据了
    if (curOperationTypeNode->GetOperationType() == Move)
    {
        Direction direction = curNode->GetDirection();
        switch (direction)
        {
          case Up:
            (curPosition[curActivePlayer].second.first)--;
            break;
          case Down:
            (curPosition[curActivePlayer].second.first)++;
            break;
          case Left:
            (curPosition[curActivePlayer].second.second)--;
            break;
          case Right:
            (curPosition[curActivePlayer].second.second)++;
            break;
        }
    }
    // 调用SetActivePlayerCommand命令，使游戏进入下一回合
    this->SetActivePlayerCommand();
    return true;
}


void StateMachine::SetExecutionInfo(Direction direction, std::pair<int, int> pos1, std::pair<int, int> pos2)
{
    auto tran = this->nodeList[AtomicExecute].get();
    auto curNode = static_cast<AtomicExecuteStateNode *>(tran);
    curNode->SetDirection(direction);
    curNode->SetPosition(pos1, pos2);
    return;
}


bool StateMachine::RollbackCommand()
{
    State curState = this->GetCurState();
    switch (curState)
    {
      case ActivePlayer:
        return false;
        break;
      case Operation:
        this->curNodeIndex = ActivePlayer;
        break;
      case AtomicExecute:
        return false;
        break;
    }
    return true;
}
// 待实现
bool StateMachine::ExecuteMoveCommand(PlayerId curActivePlayer, std::pair<int, int> position, Direction direction)
{
    // 判断能不能走

    return true;
}
bool StateMachine::ExecutePlaceBarrierCommand(std::pair<int, int> pos1, std::pair<int, int> pos2)
{
    return true;
}
bool StateMachine::ExecuteRemoveBarrierCommand(std::pair<int, int> pos1, std::pair<int, int> pos2)
{
    return true;
}


// 好像这种方式又不大对劲的样子......
//void StateMachine::set_get_JudgeSolution(const std::function<bool(PlayerId, int, int)>&& func)
//{
//    this->get_JudgeSolution = func;
//}
//void StateMachine::set_get_Accessiable(const std::function<bool(std::pair<int, int>, std::pair<int, int>)>&& func)
//{
//    this->get_Accessiable = func;
//}
//void StateMachine::set_get_Remove(const std::function<bool(PlayerId, std::pair<int, int>, std::pair<int, int>)>&& func)
//{
//    this->get_Remove = func;
//}
//void StateMachine::set_get_Add(const std::function<bool(PlayerId, std::pair<int, int>, std::pair<int, int>)>&& func)
//{
//    this->get_Add = func;
//}

