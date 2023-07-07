
#ifndef ACTIVEPLAYERSTATENODE_H
#define ACTIVEPLAYERSTATENODE_H


#include "Common/common.h"
#include "ViewModel/state/abstractStateNode.h"
//#include "ViewModel/state/atomicExecuteStateNode.h"
//#include "ViewModel/state/operationStateNode.h"

class ActivePlayerStateNode : public AbstractStateNode
{
public:
    ActivePlayerStateNode();
    void SetActivePlayer(PlayerId id);
    void SetWaitedPlayer(PlayerId id);
    PlayerId GetActivePlayer();
    PlayerId GetWaitedPlayer();
private:
    PlayerId activePlayer;
    PlayerId waitedPlayer;
};

#endif // ACTIVEPLAYERSTATENODE_H
