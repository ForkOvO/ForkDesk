#include "themetextlabel.h"
#include "publiccache.h"

ThemeTextLabel::ThemeTextLabel(QWidget *parent, QString text)
    : QLabel(parent)
{
    // 初始化
    setText(text);
    setAlignment(Qt::AlignCenter);

    // 加入缓存
    PublicCache::instance()->addWidget(this);
}

ThemeTextLabel::~ThemeTextLabel()
{
    // 从缓存中移除
    PublicCache::instance()->removeWidget(this);
}

void ThemeTextLabel::paintEvent(QPaintEvent *event)
{
    QString theme = PublicCache::instance()->get("theme").toString();
    if (theme == "dark") setStyleSheet("color: white;");
    else setStyleSheet("color: black;");
    QLabel::paintEvent(event);
}
