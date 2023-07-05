
#ifndef EXECUTECOMMAND_H
#define EXECUTECOMMAND_H

#include "Common/commands.h"
#include "Common/common.h"


class ExecuteCommand : public Commands
{
public:
    ExecuteCommand();
    // 判断是否可行的函数，在model层里面实现
    bool ExecuteMoveCommand();
    // bool IsMoveAvailable(); 这个函数要放在model层
    bool ExecutePlaceBarrierCommand();
    bool ExecuteRemoveBarrierCommand();

private:
};

#endif // EXECUTECOMMAND_H
