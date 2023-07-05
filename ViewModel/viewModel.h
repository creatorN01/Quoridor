
#ifndef VIEWMODEL_H
#define VIEWMODEL_H


#include "ViewModel/executeCommand.h"
#include "ViewModel/statemachine.h"

class ViewModel
{
public:
    ViewModel();
private:
    ExecuteCommand executeCommand;
    StateMachine stateMachine;
};

#endif // VIEWMODEL_H
