#include "dockbar.h"
#include "dockbaritem.h"

#include <QPainter>
#include <QMouseEvent>

DockBar::DockBar(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true); // 启用鼠标跟踪

    // 数据初始化
    QVector<QString> btnlist = {"ten_OvO", "calculator", "cmd", "recycleBin"};
    int width = btnlist.size() * 120 + 20;
    int height = 240;
    m_baseRect = QRect((parent->width() - width) / 2, parent->height() - height, width, height);

    for (int i = 0; i < btnlist.size(); i++) // 按钮
    {
        DockBarItem *item = new DockBarItem(this, btnlist[i]);
        m_items.append(item);
    }

    initBtns(); // 初始化按钮位置
}

DockBar::~DockBar()
{
}

void DockBar::addItem(QString name, bool isSystem)
{
    STD_DEBUG(DockBar.cpp) << "addItem: " << name << " isSystem: " << isSystem;
    DockBarItem *item = new DockBarItem(this, name, isSystem);
    m_items.append(item);
    m_baseRect = QRect(x() - 60, y(), m_items.size() * 120 + 20, 240);
    initBtns();
}

void DockBar::mouseMoveEvent(QMouseEvent *event)
{
    // 放大悬浮的按钮
    double dx = event->globalPosition().toPoint().x() - m_baseRect.x();
    if (dx < 20 || dx > m_baseRect.width() - 20)
    {
        initBtns(); // 恢复按钮位置
        return;
    }
    if (dx < 70) // 最左侧
    {
        int add = 30 + dx; // 100 - (70 - dx)
        m_items[0]->setGeometry(20, 120 - add, 100 + add, 100 + add);
        for (int i = 1; i < m_items.size(); i++)
        {
            m_items[i]->setGeometry(120 * i + 20 + add, 120, 100, 100);
        }
        setGeometry(m_baseRect.x() - add + 50, m_baseRect.y(), m_baseRect.width() + add, m_baseRect.height());
    }
    else if (dx >= m_baseRect.width() - 70) // 最右侧
    {
        int add = 30 - dx + m_baseRect.width(); // 100 - (dx - (width - 70))
        m_items[m_items.size() - 1]->setGeometry(120 * (m_items.size() - 1) + 20, 120 - add, 100 + add, 100 + add);
        for (int i = 0; i < m_items.size() - 1; i++)
        {
            m_items[i]->setGeometry(120 * i + 20, 120, 100, 100);
        }
        setGeometry(m_baseRect.x() - 50, m_baseRect.y(), m_baseRect.width() + add, m_baseRect.height());
    }
    else // 中间
    {
        int index = (dx - 70) / 120;
        int left = 100 - (dx - (index * 120 + 70)) / 1.2;
        int right = 100 - left;
        for (int i = 0; i < index; i++) // 左侧不变
        {
            m_items[i]->setGeometry(120 * i + 20, 120, 100, 100);
        }
        m_items[index]->setGeometry(120 * index + 20, 120 - left, 100 + left, 100 + left);
        m_items[index + 1]->setGeometry(120 * (index + 1) + 20 + left, 120 - right, 100 + right, 100 + right);
        for (int i = index + 2; i < m_items.size(); i++) // 右侧不变
        {
            m_items[i]->setGeometry(120 * i + 120, 120, 100, 100);
        }
        setGeometry(m_baseRect.x() - 50, m_baseRect.y(), m_baseRect.width() + 100, m_baseRect.height());
    }
    QWidget::mouseMoveEvent(event);
}

void DockBar::leaveEvent(QEvent *event)
{
    initBtns();
}

void DockBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#40808080"));
    QRect backRect(0, 100, width(), 140);
    painter.drawRoundedRect(backRect, 20, 20);
    QWidget::paintEvent(event);
}

void DockBar::initBtns()
{
    setGeometry(m_baseRect);
    for (int i = 0; i < m_items.size(); i++) // 缩小所有的按钮
    {
        m_items[i]->setGeometry(120 * i + 20, 120, 100, 100);
    }
}
