#include "keyboarditem.h"

#include <QPainter>

KeyboardItem::KeyboardItem(QString str, QWidget *parent)
    : QWidget(parent)
    , m_str(str)
{
    setFixedSize(40, 40);
}

KeyboardItem::~KeyboardItem()
{
}

void KeyboardItem::setPressed(bool pressed)
{
    m_pressed = pressed;
    update();
}

void KeyboardItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black));
    if (m_pressed) painter.setBrush(QColor("#808080"));
    else painter.setBrush(QColor("#20808080"));
    painter.drawRoundedRect(rect(), 5, 5);
    painter.drawText(rect(), Qt::AlignCenter, m_str);
}
