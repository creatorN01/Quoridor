
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

void StateMachine::SetPosition(PlayerId activePlayer, std::pair<int, int> pos)
{
    this->curPosition[activePlayer] = pos;
}




void StateMachine::InitPosition()
{
    std::pair<int, int> p1(4,8);
    std::pair<int, int> p2(4,0);
    this->curPosition[0] = p1;
    this->curPosition[1] = p2;
//    std::pair<PlayerId, std::pair<int, int>> position1(FIRST, p1);
//    std::pair<PlayerId, std::pair<int, int>> position2(SECOND, p2);
//    curPosition.push_back(position1);
//    curPosition.push_back(position2);
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

std::vector<QSharedPointer<AbstractStateNode>> StateMachine::GetNodeList()
{
    return this->nodeList;
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
    if(this->curNodeIndex != Operation) return false;
    curNodeIndex = AtomicExecute;
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
void StateMachine::SetPlaceBarrierExecInfo(BarrierType type_, std::pair<int, int> pos1, std::pair<int, int> pos2, std::pair<int, int> pos3, std::pair<int, int> pos4)
{
    auto tran = this->nodeList[AtomicExecute].get();
    auto curNode = static_cast<AtomicExecuteStateNode *>(tran);
    curNode->SetBarrierType(type_);
    curNode->SetPlaceBarrierPos(pos1, pos2, pos3, pos4);
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

