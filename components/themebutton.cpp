#include "themebutton.h"
#include "publiccache.h"

#include <QPainter>

ThemeButton::ThemeButton(QWidget *parent, QString name, int size)
    : QPushButton(parent)
{
    // 初始化
    m_name = name;
    setFixedSize(size, size);
    // 加入缓存
    PublicCache::instance()->addWidget(this);
}

ThemeButton::~ThemeButton()
{
    // 从缓存中移除
    PublicCache::instance()->removeWidget(this);
}

void ThemeButton::paintEvent(QPaintEvent *event)
{
    QString theme = PublicCache::instance()->get("theme").toString();
    if (theme == "dark")
    {
        setStyleSheet(QString("border-image: url(:/res/%1_white.png);").arg(m_name));
    }
    else
    {
        setStyleSheet(QString("border-image: url(:/res/%1_black.png);").arg(m_name));
    }
    QPushButton::paintEvent(event);
}
