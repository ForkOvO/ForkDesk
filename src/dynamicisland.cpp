#include "dynamicisland.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>

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

    // 折叠定时器
    m_foldTimer = new QTimer(this);
    connect(m_foldTimer, &QTimer::timeout, this, [&]{ setFold(true); });
    m_foldTimer->start(4000); // 开始4秒后自动折叠
}

DynamicIsland::~DynamicIsland()
{
}

void DynamicIsland::enterEvent(QEnterEvent *event)
{
    setFold(false); // 鼠标进入时展开
}

void DynamicIsland::leaveEvent(QEvent *event)
{
    m_foldTimer->start(2000); // 鼠标离开2秒后自动折叠
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

void DynamicIsland::setFold(bool toFold)
{
    m_foldTimer->stop();
    m_isFold = toFold;
    m_foldAnimation->stop();
    m_foldAnimation->setStartValue(this->geometry());
    m_foldAnimation->setEndValue(m_isFold ? m_foldRect : m_fullRect);
    m_foldAnimation->start();
}
