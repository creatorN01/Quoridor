#include <QDebug>
#include "app.h"

App::App()
{
  // 进行一些view层的信号与槽函数的绑定工作
  // 但是现在还不能确定
   qDebug() << "App()      成功连接";
}

void App::InitGameEnv()
{
  // model层初始化
  model = QSharedPointer<Model>::create();

  // viewModel层初始化
  view_model = QSharedPointer<ViewModel>::create(); // 初始化了executeCommand和stateMachine
  // 设置玩家个数和初始坐标
  view_model->GetStateMachine()->SetPlayerNum(PLAYERNUM);
  view_model->GetStateMachine()->InitPosition();
  // 设置状态机为先手ActivePlayer状态
  view_model->GetStateMachine()->SetInitialState();

  // view层初始化
  // 由于view层的部分内容还未敲定，一些绑定函数的工作也需要在这里去完成
  view = QSharedPointer<View>::create();
  view->initUI();

  QObject::connect(view.data(), SIGNAL(singleClickedSignal(QPoint, bool)), this, SLOT(When_Clicked(QPoint, bool)));
  QObject::connect(view.data(), SIGNAL(doubleClickedSignal(QPoint, bool)), this, SLOT(When_Clicked(QPoint, bool)));

}
void App::Run()
{
  qDebug() << "Run()";
  view->show();

}
void App::ExitGame()
{
}

void App::When_Clicked(QPoint clickedPosition, bool clickType)
{
  // 调用view判断区域是否在地图里的函数
  if (!view.data()->ClickedInMap(clickedPosition))     // 返回false说明点在了非map区域
  {
      // 如果已经返回了false，这时已经弹出了提示框，我这直接返回就行
      qDebug() << "点击Map以外";
      return;
  }
  qDebug() << "进入槽函数";
  // qDebug() << "When_clicked";
  // 数据准备
  // 把map取出来
  auto Map_ = model->GetMap();
  // 拿到状态机的状态
  auto stateMachine = view_model->GetStateMachine();
  auto state = stateMachine->GetCurState();
  auto nodeList = stateMachine->GetNodeList();

  auto tran1 = nodeList[ActivePlayer].get();
  auto curActivePlayerNode = static_cast<ActivePlayerStateNode *>(tran1);
  auto curActivePlayer = curActivePlayerNode->GetActivePlayer();

  auto tran2 = nodeList[Operation].get();
  auto curOperationNode = static_cast<OperationStateNode *>(tran2);
  auto curOperation = curOperationNode->GetOperationType();

  auto tran3 = nodeList[AtomicExecute].get();
  auto curAtomicExecuteNode = static_cast<AtomicExecuteStateNode *>(tran3);
  auto execDirection = curAtomicExecuteNode->GetDirection();
  auto execPos1 = curAtomicExecuteNode->GetPosition1();
  auto execPos2 = curAtomicExecuteNode->GetPosition2();
  auto execPlaceBarrierType = curAtomicExecuteNode->GetBarrierType();
  auto execPlace1 = curAtomicExecuteNode->GetPlace1();
  auto execPlace2 = curAtomicExecuteNode->GetPlace2();
  auto execPlace3 = curAtomicExecuteNode->GetPlace3();
  auto execPlace4 = curAtomicExecuteNode->GetPlace4();

  // 为setExecInfo准备的临时变量
  // PlaceBarrier状态下的规约点
  QPoint correctPoint;
  // 移动状态下的规约点
  QPoint correctPointMove;
  // RemoveBarrier状态下的规约点
  QPoint correctPointRemove;
  Direction keyBoardDirection;
  std::pair<int, int> pos1;
  std::pair<int, int> pos2;
  BarrierType barrierTypePlaced;
  std::pair<int, int> pos1_;
  std::pair<int, int> pos2_;
  std::pair<int, int> pos3_;
  std::pair<int, int> pos4_;
  BarrierType barrierTypeRemove;

  switch (state)
  {
  case ActivePlayer:
    qDebug() << "ActivePlayer状态，将进行selectOperation命令";
    // 继续判断是否点击在了ActivePlayer
    if (clickType == ClickType::LeftSingleClicked)     // 单击
    {
        if (view.data()->ClickedInPlayer(curActivePlayer, clickedPosition))
        {
            qDebug() << "点击头像";
            // 调用viewModel，selectOperation
            stateMachine->SelectOperationCommand(Move);
            When_Clicked(clickedPosition, true);
            return;
        } else {    // 意味着用户要放Barrier
            qDebug() << "要放置Barrier";

            // 调用viewModel, selectOperation
            stateMachine->SelectOperationCommand(PlaceBarrier);
            // 递归调用When_Clicked();
            When_Clicked(clickedPosition, true);
        }
    }
    else        // 双击，意味着要RemoveBarrier
    {
        qDebug() << "要移除Barrier";
        // 调用viewModel，selectOperation
        stateMachine->SelectOperationCommand(RemoveBarrier);
        // 递归调用When_Clicked();
        When_Clicked(clickedPosition, true);
    }


    break;
  case Operation:
    qDebug() << "Operation状态，将进行selectPosition命令";
    // 再套一个switch case用于分支到底是Move PlaceBarrier RemoveBarrier
    switch (curOperation)
    {
      case Move:
        qDebug() << "用户要move";
        // 调用view，显示箭头，需要修正坐标
        correctPointMove.setX(clickedPosition.x()/100*100);
        correctPointMove.setY(clickedPosition.y()/100*100);
        qDebug() << "correctPointMove.setX" << correctPointMove.x();
        view.data()->ShowArrowAround(correctPointMove);
        // 接着用户需要在“上下左右”键中选择一个按下
        keyBoardDirection = view.data()->GetDirectionFromKeyboard();
        // 设定执行的数据，调整状态机
        qDebug() << "keyBoardDirection = " << keyBoardDirection;
        pos1.first = (correctPointMove.x() - 300) / 100;
        pos1.second = correctPointMove.y() / 100;
        qDebug() << "move左上基准点的index" << "fir" << pos1.first << "sec" << pos1.second;
        switch (keyBoardDirection)
        {
          case Up:
            pos2.first = pos1.first;
            pos2.second = pos1.second - 1;
            break;
          case Down:
            pos2.first = pos1.first;
            pos2.second = pos1.second + 1;
            break;
          case Left:
            pos2.first = pos1.first - 1;
            pos2.second = pos1.second;
            break;
          case Right:
            pos2.first = pos1.first + 1;
            pos2.second = pos1.second;
            break;
        }
        qDebug() << "move终点的index" << "fir" << pos2.first << "sec" << pos2.second;
        stateMachine->SetExecutionInfo(keyBoardDirection, pos1, pos2);
        stateMachine->SelectPositionCommand();
        // 递归调用，这时候就去到AtomicExecute了
        When_Clicked(clickedPosition, true);
        break;
      case PlaceBarrier:
        qDebug() << "用户要PlaceBarrier" << clickedPosition;
        // 调用view里面的函数来修订坐标
        correctPoint = view.data()->CorrectBarrierPosition(clickedPosition);
        qDebug() << "修正坐标" << correctPoint;
        // 调用view里面的ShowPossibleBarrier，会在里面设定好的
        barrierTypePlaced = view.data()->ShowPossibleBarrier(curActivePlayer, correctPoint, BarrierType::horizontal);
        // 设定执行的数据，调整状态机
        pos4_.first = (correctPoint.x() - 300) / 100;
        pos4_.second = correctPoint.y() / 100;
        pos1_.first = pos4_.first - 1;
        pos1_.second = pos4_.second - 1;
        pos2_.first = pos4_.first;
        pos2_.second = pos4_.second - 1;
        pos3_.first = pos4_.first - 1;
        pos3_.second = pos4_.second;
        qDebug() << "PlaceBarrier四个点的index";
        qDebug() << "fir" << pos1_.first << "sec" << pos1_.second;
        qDebug() << "fir" << pos2_.first << "sec" << pos2_.second;
        qDebug() << "fir" << pos3_.first << "sec" << pos3_.second;
        qDebug() << "fir" << pos4_.first << "sec" << pos4_.second;

        stateMachine->SetPlaceBarrierExecInfo(barrierTypePlaced, pos1_, pos2_, pos3_, pos4_);
        stateMachine->SelectPositionCommand();
        // 递归调用，这时候就去到了AtomicExecute
        When_Clicked(clickedPosition, true);
        break;
      case RemoveBarrier:
        qDebug() << "用户要RemoveBarrier" << clickedPosition;
        // 调用view里面的函数来修订坐标
        correctPointRemove = view.data()->CorrectBarrierPosition(clickedPosition);
        qDebug() << "修正坐标" << correctPointRemove;
        // 要调用view里面的某一个未实现的函数，来判断这个修正后的坐标上是否有可以删除的障碍
        if (view.data()->JudgeBarrierRemovedExistence(correctPointRemove) == false)
        {
            qDebug() << "No Barrier";
            // rollback
            // 弹出提示
        }
        qDebug() << "Have Barrier";
        // 调用view里面的ShowRemoveBarrier
        barrierTypeRemove = view.data()->ShowRemoveBarrier(curActivePlayer, correctPointRemove);
        // 设定执行的数据，调整状态机
        pos4_.first = (correctPointRemove.x() - 300) / 100;
        pos4_.second = correctPointRemove.y() / 100;
        pos1_.first = pos4_.first - 1;
        pos1_.second = pos4_.second - 1;
        pos2_.first = pos4_.first;
        pos2_.second = pos4_.second - 1;
        pos3_.first = pos4_.first - 1;
        pos3_.second = pos4_.second;
        qDebug() << "RemoveBarrier四个点的index";
        qDebug() << "fir" << pos1_.first << "sec" << pos1_.second;
        qDebug() << "fir" << pos2_.first << "sec" << pos2_.second;
        qDebug() << "fir" << pos3_.first << "sec" << pos3_.second;
        qDebug() << "fir" << pos4_.first << "sec" << pos4_.second;
        stateMachine->SetRemoveBarrierExecInfo(barrierTypeRemove, pos1_, pos2_, pos3_, pos4_);
        stateMachine->SelectPositionCommand();
        // 递归调用，这时候就去到了AtomicExecute
        When_Clicked(clickedPosition, true);
        break;
    }

    break;
  case AtomicExecute:
    qDebug() << "AtomicExecute";
    // 根据OperationType进行分支：
    switch (curOperation)
    {
      case Move:
        qDebug() << "ExecuteMove";
        qDebug() << "execPos1 = " << execPos1.first << "," << execPos1.second;
        qDebug() << "execPos2 = " << execPos2.first << "," << execPos2.second;
        // 判断能不能走
        if (Map_->Accessible(execPos1, execPos2) == true)
        {
            // 修改model层的数据——无
                qDebug() << "yes";
            // 修改viewModel
            stateMachine->SetPosition(curActivePlayer, execPos2);
            // 修改view
            view->MoveActivePlayerPos(curActivePlayer, execDirection);

        }
        else
        {
            qDebug() << "NOT";
        }
        // 判断move后是否达成胜利条件
        // waiting
        if (view.data()->JudgeVictory(curActivePlayer) == true)
        {
            qDebug() << curActivePlayer << "胜利";
            if (curActivePlayer == FIRST)
            {
                view.data()->set_game_status(FIRST_WIN);
            }
            else
            {
                view.data()->set_game_status(SECOND_WIN);
            }

        }
        // 设置状态机，进入后手的ActivePlayer状态
        stateMachine->SetActivePlayerCommand();
        break;
      case PlaceBarrier:
        qDebug() << "ExecutePlaceBarrier";
        qDebug() << "execPlace1" << "fir" << execPlace1.first << "sec" << execPlace1.second;
        qDebug() << "execPlace2" << "fir" << execPlace2.first << "sec" << execPlace2.second;
        qDebug() << "execPlace3" << "fir" << execPlace3.first << "sec" << execPlace3.second;
        qDebug() << "execPlace4" << "fir" << execPlace4.first << "sec" << execPlace4.second;
        // 调JudgePlaceBarrier
        // waiting 没有debug
        if (Map_->JudgePlaceBarrier(execPlaceBarrierType, execPlace1, execPlace2, execPlace3, execPlace4) == false)
        {
            // rollback
            qDebug() << "NOT";
        }
        else
        {
            qDebug() << "Yes";
        }
        // 这里还需要调用judgeSolution函数
        // waiting
        // 先修改model层的数据
        if (execPlaceBarrierType == BarrierType::horizontal)    // 水平
        {
            Map_->Remove(curActivePlayer, execPlace1, execPlace3);
            Map_->Remove(curActivePlayer, execPlace2, execPlace4);
        }
        else
        {
            Map_->Remove(curActivePlayer, execPlace1, execPlace2);
            Map_->Remove(curActivePlayer, execPlace3, execPlace4);
        }

        // 再修改viewModel层的数据————无
        // 最后修改view层的数据
        // view要改什么东西？画Barrier、文字提示的更新、vector<> Barrier_ui_List
        view->PlaceBarrier_ui();
        // 设置状态机，进入后手的ActivePlayer状态
        stateMachine->SetActivePlayerCommand();
        break;
      case RemoveBarrier:
        qDebug() << "ExecuteRemoveBarrier";
        qDebug() << "execPlace1" << "fir" << execPlace1.first << "sec" << execPlace1.second;
        qDebug() << "execPlace2" << "fir" << execPlace2.first << "sec" << execPlace2.second;
        qDebug() << "execPlace3" << "fir" << execPlace3.first << "sec" << execPlace3.second;
        qDebug() << "execPlace4" << "fir" << execPlace4.first << "sec" << execPlace4.second;
        // 先修改model层的数据
        // waiting 还没有debug
        if (execPlaceBarrierType == BarrierType::horizontal)    // 水平
        {
            Map_->Add(curActivePlayer, execPlace1, execPlace3);
            Map_->Add(curActivePlayer, execPlace2, execPlace4);
        }
        else
        {
            Map_->Add(curActivePlayer, execPlace1, execPlace2);
            Map_->Add(curActivePlayer, execPlace3, execPlace4);
        }
        qDebug() << "跳出add";
        // 再修改viewModel层的数据————无
        // 最后修改view层的数据
        view->RemoveBarrier_ui();

        stateMachine->SetActivePlayerCommand();
        break;
    }
    break;
  }
}
