#include "dockbar.h"

#include <QPainter>

DockBar::DockBar(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(100, parent->height() - 200, parent->width() - 200, 100);
}

DockBar::~DockBar()
{
}

void DockBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#20808080"));
    painter.drawRoundedRect(rect(), 10, 10);
    QRect bottomRect(0, 80, width(), 20);
    painter.setBrush(QColor("#80808080"));
    painter.drawRoundedRect(bottomRect, 10, 10);
}
