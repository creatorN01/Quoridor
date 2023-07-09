#ifndef TEXTPROMPT_H
#define TEXTPROMPT_H


#include <QPixmap>
#include <QPoint>
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>
#include "Common/common.h"

// 文字提示
/*
    1. PlayerName
    2. 剩余可放置的障碍数
    3. "My move"提示
    4. 移动步数
*/
class TextPrompt : public QWidget
{
    Q_OBJECT

public:
    explicit TextPrompt(QWidget *parent = nullptr);
    void setPlayerName(const QString& playerName);
    void setRemainingBarriers(int count);
    void setMovePrompt(bool isMyMove);
    void setMoveCount(int count);

private:
    QLabel* playerNameLabel; // 用于显示玩家名称的标签
    QLabel* remainingBarriersLabel; // 用于显示剩余可放置障碍物数的标签
    QLabel* movePromptLabel; // 用于显示"My move"提示的标签
    QLabel* moveCountLabel; // 用于显示移动步数的标签

signals:

};

#endif // TEXTPROMPT_H
