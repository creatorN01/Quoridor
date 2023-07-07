
#ifndef VIEWMODEL_H
#define VIEWMODEL_H



#include "ViewModel/statemachine.h"

class ViewModel
{
public:
    ViewModel();
    // QSharedPointer<ExecuteCommand> GetExecuteCommand();
    QSharedPointer<StateMachine> GetStateMachine();

private:
    QSharedPointer<StateMachine> stateMachine;
};

#endif // VIEWMODEL_H
