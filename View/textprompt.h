
#ifndef TEXTPROMPT_H
#define TEXTPROMPT_H


#include <QPixmap>
#include <QPoint>
#include <QWidget>
#include <QPainter>
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

signals:

};

#endif // TEXTPROMPT_H
