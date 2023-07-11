#include "textprompt.h"

TextPrompt::TextPrompt(QWidget *parent) : QWidget(parent)
{
    // 创建标签
    playerNameLabel_1 = new QLabel(this);
    playerNameLabel_2 = new QLabel(this);
    remainingBarriersLabel_1 = new QLabel(this);
    remainingBarriersLabel_2 = new QLabel(this);
    moveCountLabel_1 = new QLabel(this);
    moveCountLabel_2 = new QLabel(this);
    movePromptLabel = new QLabel(this);

    // 设置标签的位置
    playerNameLabel_2->setGeometry(100, 250, 100, 50);
    remainingBarriersLabel_2->setGeometry(100, 300, 150, 50);
    moveCountLabel_2->setGeometry(100, 350, 150, 50);

    playerNameLabel_1->setGeometry(100, 600, 100, 50);
    remainingBarriersLabel_1->setGeometry(100, 650, 150, 50);
    moveCountLabel_1->setGeometry(100, 700, 150, 50);


    movePromptLabel->setGeometry(1290, 300, 200, 50);

    // 设置样式
    playerNameLabel_1->setStyleSheet("font-size: 25px; color: red;");
    playerNameLabel_2->setStyleSheet("font-size: 25px; color: blue;");
    remainingBarriersLabel_1->setStyleSheet("font-size: 25px; color: red;");
    remainingBarriersLabel_2->setStyleSheet("font-size: 25px; color: blue;");
    moveCountLabel_1->setStyleSheet("font-size: 25px; color: red;");
    moveCountLabel_2->setStyleSheet("font-size: 25px; color: blue;");

    QFont font("Arial", 16); // 创建字体对象，指定字体名称和字号
    font.setWeight(QFont::Bold);
    playerNameLabel_1->setFont(font); // 为标签设置字体
    playerNameLabel_2->setFont(font);
    remainingBarriersLabel_1->setFont(font);
    remainingBarriersLabel_2->setFont(font);
    moveCountLabel_1->setFont(font);
    moveCountLabel_2->setFont(font);
    movePromptLabel->setFont(font);
}

void TextPrompt::increase_count_round_1() {
    this->count_round_1++;
}

void TextPrompt::increase_count_round_2() {
    this->count_round_2++;
}

void TextPrompt::set_play_id(PlayerId player) {
    this->player_id = player;
}

void TextPrompt::setPlayerName()
{
    playerNameLabel_1->setText("Player 1");
    playerNameLabel_2->setText("Player 2");
}

void TextPrompt::setRemainingBarriers(int count1, int count2)
{
    remainingBarriersLabel_1->setText(QString("barrier: %1").arg(count1));
    remainingBarriersLabel_2->setText(QString("barrier: %1").arg(count2));
}

void TextPrompt::setMovePrompt(PlayerId player)
{
    if (player == FIRST) {
        movePromptLabel->setStyleSheet("font-size: 25px; color: red;");
        movePromptLabel->setText("Red's turn");
    }

    else {
        movePromptLabel->setStyleSheet("font-size: 25px; color: blue;");
        movePromptLabel->setText("Blue's turn");
    }

}

void TextPrompt::setMoveCount(int count1, int count2)
{
    moveCountLabel_1->setText(QString("round: %1").arg(count1));
    moveCountLabel_2->setText(QString("round: %1").arg(count2));
}

void TextPrompt::paint() {
    setPlayerName();
    setRemainingBarriers(this->count_barrier_1, this->count_barrier_2);
    setMoveCount(this->count_round_1, this->count_round_2);
    setMovePrompt(this->player_id);
}

void TextPrompt::decrease_barrier_1() {
    count_barrier_1--;
}

void TextPrompt::decrease_barrier_2() {
    count_barrier_2--;
}
