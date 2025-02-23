#include "dockbar.h"
#include "dockbaritem.h"

#include <QPainter>
#include <QMouseEvent>

DockBar::DockBar(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true); // 启用鼠标跟踪

    QVector<QString> btnlist = {"ten_OvO", "calculator", "ten_OvO", "ten_OvO", "ten_OvO", "ten_OvO"};
    int width = btnlist.size() * 100;
    int height = 200;

    // 初始化窗口
    m_baseRect = QRect((parent->width() - width) / 2, parent->height() - 300, width, height);
    setGeometry(m_baseRect);

    // 按钮
    for (int i = 0; i < btnlist.size(); i++)
    {
        DockBarItem *item = new DockBarItem(this, btnlist[i]);
        item->setGeometry(100 * i, 100, 100, 100);
        m_items.append(item);
    }
}

DockBar::~DockBar()
{
}

void DockBar::mouseMoveEvent(QMouseEvent *event)
{
    // 放大悬浮的按钮
    int x = event->globalPosition().toPoint().x() - m_baseRect.x();
    int width = 0;
    for (int i = 0; i < m_items.size(); i++)
    {
        int add = 100 - qAbs(x - 50 - 100 * i); // 当前按钮放大数据
        if (add > 0) 
        {
            m_items[i]->setGeometry(width, 100 - add, 100 + add, 100 + add);
            width += 100 + add;
        }
        else
        {
            m_items[i]->setGeometry(width, 100, 100, 100);
            width += 100;
        }
    }
    int d_width = (width - m_baseRect.width()) / 2;
    setGeometry(m_baseRect.x() - d_width, m_baseRect.y(), width, m_baseRect.height());
    QWidget::mouseMoveEvent(event);
}

void DockBar::leaveEvent(QEvent *event)
{
    for (int i = 0; i < m_items.size(); i++) // 缩小所有的按钮
    {
        m_items[i]->setGeometry(100 * i, 100, 100, 100);
    }
    setGeometry(m_baseRect);
}

void DockBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#20808080"));
    QRect backRect(0, 100, width(), 100);
    painter.drawRoundedRect(backRect, 10, 10);
    QWidget::paintEvent(event);
}
