#include "map_ui.h"
#include <QDebug>

Map_ui::Map_ui(QWidget *parent) : QWidget(parent)
{
    // 加载素材图像
    img_map.load("://images//GameKit//background.jpg");
    t1.load("://images//GameKit//t1.jpg");
    t2.load("://images//GameKit//t2.jpg");
}

void Map_ui::paint(QPainter &painter, int width, int height)
{
    painter.drawPixmap(0, 0, img_map.scaled(width, height, Qt::KeepAspectRatio));
    painter.drawPixmap(110, 150, t1.scaled(100, 100, Qt::KeepAspectRatio));
    painter.drawPixmap(110, 500, t2.scaled(100, 100, Qt::KeepAspectRatio));
}
