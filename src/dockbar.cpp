#include "dockbar.h"

#include <QPainter>
#include <QPropertyAnimation>

DockBar::DockBar(QWidget *parent)
    : QWidget(parent)
{
    m_foldRect = QRect(200, parent->height() - 200, parent->width() - 400, 100);
    m_fullRect = QRect(100, parent->height() - 200, parent->width() - 200, 100);
    setGeometry(m_foldRect);

    // 折叠动画
    m_foldAnimation = new QPropertyAnimation(this, "geometry");
    m_foldAnimation->setDuration(300);
}

DockBar::~DockBar()
{
}

void DockBar::enterEvent(QEnterEvent *event)
{
    // 展开
    STD_DEBUG(DockBar.cpp) << "enterEvent";
    m_foldAnimation->setStartValue(geometry());
    m_foldAnimation->setEndValue(m_fullRect);
    m_foldAnimation->start();
}

void DockBar::leaveEvent(QEvent *event)
{
    // 折叠
    STD_DEBUG(DockBar.cpp) << "leaveEvent";
    m_foldAnimation->setStartValue(geometry());
    m_foldAnimation->setEndValue(m_foldRect);
    m_foldAnimation->start();
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
