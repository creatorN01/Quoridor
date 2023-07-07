
#include "activePlayerStateNode.h"

ActivePlayerStateNode::ActivePlayerStateNode()
{

}

void ActivePlayerStateNode::SetActivePlayer(PlayerId id)
{
    this->activePlayer = id;
}
void ActivePlayerStateNode::SetWaitedPlayer(PlayerId id)
{
    this->waitedPlayer = id;
}
PlayerId ActivePlayerStateNode::GetActivePlayer()
{
    return this->activePlayer;
}
PlayerId ActivePlayerStateNode::GetWaitedPlayer()
{
    return this->waitedPlayer;
}
