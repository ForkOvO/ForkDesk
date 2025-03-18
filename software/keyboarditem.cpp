#include "keyboarditem.h"
#include "publiccache.h"

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

void KeyboardItem::setStr(QString str)
{
    m_str = str;
    update();
}

void KeyboardItem::setPressed(bool pressed)
{
    m_pressed = pressed;
    update();
}

void KeyboardItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QString theme = PublicCache::instance()->get("theme").toString();
    if (theme == "dark") painter.setPen(QPen(Qt::white));
    else painter.setPen(QPen(Qt::black));
    if (m_pressed) painter.setBrush(QColor("#808080"));
    else painter.setBrush(QColor("#20808080"));
    painter.drawRoundedRect(rect(), 5, 5);
    painter.drawText(rect(), Qt::AlignCenter, m_str);
}