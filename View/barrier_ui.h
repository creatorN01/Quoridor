
#ifndef BARRIER_UI_H
#define BARRIER_UI_H

#include <QPixmap>
#include <QPoint>
#include <QWidget>
#include <QPainter>
#include "Common/common.h"

class Barrier_ui : public QWidget
{
    Q_OBJECT
public:
    explicit Barrier_ui(QWidget *parent = nullptr);
    void paint(QPainter &painter);
    void set_pos(const QPoint& pos);
    void set_playerId(const PlayerId& id);
    void set_type(const BarrierType& type);
    void set_needToShow(const bool need){this->ifNeedtoShow = need;}
    QPoint& get_pos();
    PlayerId& get_playerId();
    BarrierType& get_type();
    bool getIfNeedToShow();

private:
    // 四种图像作为静态成员存储更合适一些，所有的对象共用一份
    // 不知道会不会在显示的时候出bug...实在不行，再改
    QPixmap img_barrier1_row;
    QPixmap img_barrier1_column;
    QPixmap img_barrier2_row;
    QPixmap img_barrier2_column;

    // 基准点坐标，就中心点好了
    QPoint pos;
    // 是谁放置的
    PlayerId playerId;
    // 横or竖
    BarrierType type;

    bool ifNeedtoShow = false;
};
// 记得给静态成员赋值~

#endif // BARRIER_UI_H
