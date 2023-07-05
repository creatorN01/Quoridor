
#ifndef MAP_UI_H
#define MAP_UI_H


#include <QPixmap>
#include <QPoint>
#include <QWidget>
#include <QPainter>
#include "Common/common.h"

// 地图
// 有一个不太好处理的问题是，地图、玩家、障碍的大小关系的调整
class Map_ui : public QWidget
{
    Q_OBJECT
public:
    explicit Map_ui(QWidget *parent = nullptr);

private:
    QPixmap img_map;


};

#endif // MAP_UI_H
