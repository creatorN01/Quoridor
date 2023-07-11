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
    void setPlayerName();
    void setMovePrompt(PlayerId player);
    void setRemainingBarriers(int count1, int count2);
    void setMoveCount(int count1, int count2);

    void increase_count_round_1();
    void increase_count_round_2();
    void decrease_barrier_1();
    void decrease_barrier_2();
    void set_play_id(PlayerId player);
    void paint();

private:
    QLabel* playerNameLabel_1; // 用于显示玩家名称的标签
    QLabel* playerNameLabel_2; // 用于显示玩家名称的标签
    QLabel* remainingBarriersLabel_1; // 用于显示剩余可放置障碍物数的标签
    QLabel* remainingBarriersLabel_2; // 用于显示剩余可放置障碍物数的标签
    QLabel* moveCountLabel_1; // 用于显示移动步数的标签
    QLabel* moveCountLabel_2; // 用于显示移动步数的标签
    QLabel* movePromptLabel; // 用于显示"My move"提示的标签

    int count_barrier_1 = 10, count_barrier_2 = 10;
    int count_round_1 = 0, count_round_2 = 0;
    PlayerId player_id = FIRST;

signals:

};

#endif // TEXTPROMPT_H
