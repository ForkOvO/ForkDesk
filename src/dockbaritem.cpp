#include "dockbaritem.h"

#include <QPainter>

DockBarItem::DockBarItem(QWidget *parent)
    : QPushButton(parent)
{
    setMouseTracking(true); // 启用鼠标跟踪
}

DockBarItem::~DockBarItem()
{
}

void DockBarItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    QPixmap pixmap(":/res/ten_OvO_white.png");
    painter.drawPixmap(rect(), pixmap);
}
