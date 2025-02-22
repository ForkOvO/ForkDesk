#ifndef DOCKBAR_H
#define DOCKBAR_H

// 底部栏

#include "definestd.h"
#include <QWidget>

class QPropertyAnimation;
class DockBarItem;

class DockBar : public QWidget
{
    Q_OBJECT
public:
    explicit DockBar(QWidget *parent = nullptr);
    ~DockBar();

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPropertyAnimation* m_foldAnimation = nullptr; // 折叠动画

    QVector<DockBarItem*> m_items; // 按钮集合
    QRect m_baseRect; // 基础矩形
};

#endif // DOCKBAR_H