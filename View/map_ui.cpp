#include "map_ui.h"
#include <QDebug>

Map_ui::Map_ui(QWidget *parent) : QWidget(parent)
{
    // 加载素材图像
    img_map.load(":/GameKit/background.jpg");
}

void Map_ui::paint(QPainter &painter, int width, int height)
{
    painter.drawPixmap(0, 0, img_map.scaled(width, height, Qt::KeepAspectRatio));
}
