
#include "app.h"

App::App()
{
    // 进行一些view层的信号与槽函数的绑定工作
    // 但是现在还不能确定
}

void App::InitGameEnv()
{
    // model层初始化
    model = QSharedPointer<Model>::create();

    // viewModel层初始化
    view_model = QSharedPointer<ViewModel>::create();  // 初始化了executeCommand和stateMachine
    // 设置玩家个数和初始坐标
    view_model->GetStateMachine()->SetPlayerNum(PLAYERNUM);
    view_model->GetStateMachine()->InitPosition();
    // 设置状态机为先手ActivePlayer状态
    view_model->GetStateMachine()->SetInitialState();

    // view层初始化
    // 由于view层的部分内容还未敲定，一些绑定函数的工作也需要在这里去完成
    view = QSharedPointer<View>::create();
    view->initUI();
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
    view->show();
}
void App::ExitGame()
{

}


