
#include "viewModel.h"

ViewModel::ViewModel()
{
    // executeCommand = QSharedPointer<ExecuteCommand>::create();
    stateMachine = QSharedPointer<StateMachine>::create();
}



QSharedPointer<StateMachine> ViewModel::GetStateMachine()
{
    return stateMachine;
}


