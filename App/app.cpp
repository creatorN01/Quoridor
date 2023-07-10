#include <QDebug>
#include "app.h"

App::App()
{
  // 进行一些view层的信号与槽函数的绑定工作
  // 但是现在还不能确定
  // qDebug() << "成功连接";
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

  QObject::connect(view.data(), SIGNAL(mySignal(QPoint)), this, SLOT(When_Clicked(QPoint)));

}
void App::Run()
{
  qDebug() << "Run()";
  view->show();

}
void App::ExitGame()
{
}

void App::When_Clicked(QPoint clickedPosition)
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
  auto Map_ = model->GetMapReference();
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


  // PlaceBarrier状态下的规约点
  QPoint correctPoint;
  // 移动状态下的规约点
  QPoint correctPointMove;
  Direction keyBoardDirection;
  std::pair<int, int> pos1;
  std::pair<int, int> pos2;

  switch (state)
  {
  case ActivePlayer:
    qDebug() << "ActivePlayer状态，将进行selectOperation命令";
    // 继续判断是否点击在了ActivePlayer
    if (view.data()->ClickedInPlayer(curActivePlayer, clickedPosition))
    {
        qDebug() << "点击头像";
        // 调用viewModel，selectOperation
        stateMachine->SelectOperationCommand(Move);
        When_Clicked(clickedPosition);
        return;
    } else if (0) {
        // remove待实现
    } else {    // 意味着用户要放骨头
        qDebug() << "要放置骨头";

        // 调用viewModel, selectOperation
        stateMachine->SelectOperationCommand(PlaceBarrier);
        // 递归调用When_Clicked();
        When_Clicked(clickedPosition);
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
        pos1.first = correctPointMove.y() / 100;
        pos1.second = (correctPointMove.x() - 300) / 100;
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
        stateMachine->SetExecutionInfo(keyBoardDirection, pos1, pos2);
        stateMachine->SelectPositionCommand();
        // 递归调用，这时候就去到AtomicExecute了
        When_Clicked(clickedPosition);
        break;
      case PlaceBarrier:
        qDebug() << "用户要PlaceBarrier" << clickedPosition;
        // 调用view里面的函数来修订坐标
        correctPoint = view.data()->CorrectBarrierPosition(clickedPosition);
        qDebug() << "修正坐标" << correctPoint;
        // 调用view里面的ShowPossibleBarrier，会在里面
        view.data()->ShowPossibleBarrier(curActivePlayer, correctPoint, BarrierType::horizontal);
        break;
      case RemoveBarrier:
        break;
    }

    break;
  case AtomicExecute:
    qDebug() << "AtomicExecute";
    // 根据OperationType进行分支：
    switch (curOperation)
    {
      case Move:
        // 判断能不能走
        if (Map_.Accessible(execPos1, execPos2))
        {
            // 修改model层的数据——无

            // 修改viewModel
            stateMachine->SetPosition(curActivePlayer, execPos2);
            // 修改view
            view->MoveActivePlayerPos(curActivePlayer, execDirection);

        }
        // 设置状态机，进入后手的ActivePlayer状态
        stateMachine->SetActivePlayerCommand();
        break;
      case PlaceBarrier:
        qDebug() << "NOT";
        break;
      case RemoveBarrier:
        qDebug() << "NOT";
        break;
    }

    break;
  }
}
