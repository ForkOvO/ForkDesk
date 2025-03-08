#include "dynamicisland.h"

#include <QPainter>
#include <QPropertyAnimation>

DynamicIsland::DynamicIsland(QWidget *parent)
    : QWidget(parent)
{
    // 折叠展开数据
    m_fullRect = QRect((parent->width() - 400) / 2, 0, 400, 50);
    m_foldRect = QRect((parent->width() - 50) / 2, 0, 50, 50);
    m_foldAnimation = new QPropertyAnimation(this, "geometry");
    m_foldAnimation->setDuration(300);

    // 设置窗口属性
    setGeometry(m_fullRect);
}

DynamicIsland::~DynamicIsland()
{
}

void DynamicIsland::enterEvent(QEnterEvent *event)
{
    // 展开
    STD_DEBUG(DynamicIsland.cpp) << "expand dynamicisland";
    m_isFold = false;
    m_foldAnimation->stop();
    m_foldAnimation->setStartValue(this->geometry());
    m_foldAnimation->setEndValue(m_fullRect);
    m_foldAnimation->start();
}

void DynamicIsland::leaveEvent(QEvent *event)
{
    // 折叠
    STD_DEBUG(DynamicIsland.cpp) << "fold dynamicisland";
    m_isFold = true;
    m_foldAnimation->stop();
    m_foldAnimation->setStartValue(this->geometry());
    m_foldAnimation->setEndValue(m_foldRect);
    m_foldAnimation->start();
}

void DynamicIsland::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // 字体
    QFont font("Microsoft YaHei", 15);
    painter.setFont(font);
    // 画笔
    QPen pen(Qt::white);
    pen.setWidth(1);
    painter.setPen(pen);
    // 画刷
    painter.setBrush(QColor(Qt::black));

    // 绘制
    painter.drawRoundedRect(rect(), 10, 10); // 圆角背景
    if (!m_isFold && m_foldAnimation->state() == QAbstractAnimation::Stopped)
    {
        painter.drawText(rect(), Qt::AlignCenter, "否客桌面欢迎您"); // 文字
    }
}
