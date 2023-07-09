#include "textprompt.h"

TextPrompt::TextPrompt(QWidget *parent) : QWidget(parent)
{
    // 创建标签
    playerNameLabel = new QLabel(this);
    remainingBarriersLabel = new QLabel(this);
    movePromptLabel = new QLabel(this);
    moveCountLabel = new QLabel(this);

    // 设置标签的位置
    playerNameLabel->setGeometry(10, 10, 200, 20);
    remainingBarriersLabel->setGeometry(10, 40, 200, 20);
    movePromptLabel->setGeometry(10, 70, 200, 20);
    moveCountLabel->setGeometry(10, 100, 200, 20);

    // 设置样式
    playerNameLabel->setStyleSheet("font-size: 16px;");
    remainingBarriersLabel->setStyleSheet("font-size: 16px;");
    movePromptLabel->setStyleSheet("font-size: 16px;");
    moveCountLabel->setStyleSheet("font-size: 16px;");
}

void TextPrompt::setPlayerName(const QString& playerName)
{
    playerNameLabel->setText(playerName);
}

void TextPrompt::setRemainingBarriers(int count)
{
    remainingBarriersLabel->setText(QString("剩余障碍物数: %1").arg(count));
}

void TextPrompt::setMovePrompt(bool isMyMove)
{
    if (isMyMove)
        movePromptLabel->setText("轮到Player1");
    else
        movePromptLabel->setText("轮到Player2");
}

void TextPrompt::setMoveCount(int count)
{
    moveCountLabel->setText(QString("移动步数: %1").arg(count));
}

