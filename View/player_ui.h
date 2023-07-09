
#ifndef PLAYER_UI_H
#define PLAYER_UI_H

#include <QPixmap>
#include <QPoint>
#include <QWidget>
#include <QPainter>
#include "Common/common.h"
#include <QMouseEvent>

// 玩家
class Player_ui : public QWidget
{
    Q_OBJECT
public:
    explicit Player_ui(const PlayerId id, QWidget *parent = nullptr);
    void paint(QPainter &painter, const QPoint pos, int width, int height);
    void set_pos(const QPoint& pos);
    void set_selected(const bool& isSelected);
    void set_playerId(const PlayerId id);
    PlayerId& get_id();
    bool& get_isSelected();
    QPoint& get_pos();
    void mousePressEvent(QMouseEvent *event);

private:
    PlayerId id;        // 玩家id (enum类型)
    QPoint pos;         // 基准点的坐标（基准点的选取待确定）
    bool isSelected;    // 是否被选中，选中要闪烁，并显示可选择的目标位
    QPixmap img_player; // 棋子的图像
    QPixmap img_select; // 选中后的目标位的图像

    QPixmap img_arrow_up;
    QPixmap img_arrow_down;
    QPixmap img_arrow_left;
    QPixmap img_arrow_right;
};

#endif // PLAYER_UI_H
