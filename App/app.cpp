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
  // 利用lambda表达式对仿函数进行绑定
  // 这里只需要绑定ViewModel和View的函数，不需要处理信号和槽
  // 信号和槽的绑定放在view层来做
  // 信号：
  // 鼠标的点击
  // 槽函数：
  // 状态转移命令：
  // SetActivePlayerCommand, SelectPositionCommand
  // SelectOperationCommand, RollbackCommand
  // 执行命令：
  // ExecuteMoveCommand, ExecutePlaceBarrierCommand, ExecuteRemoveBarrierCommand
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

  // PlaceBarrier状态下的规约点
  QPoint correctPoint;
  // 移动状态下的规约点
  QPoint correctPointMove;
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
        view.data()->GetDirectionFromKeyboard();
        // 设定执行的数据，调整状态机

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
    qDebug() << "NOT";
    break;
  }
}
