#ifndef DYNAMICISLAND_H
#define DYNAMICISLAND_H

// 否客岛

#include "definestd.h"
#include <QWidget>

class QPropertyAnimation; // 动态属性动画

class DynamicIsland : public QWidget
{
    Q_OBJECT
public:
    DynamicIsland(QWidget *parent = nullptr);
    ~DynamicIsland();

protected:
    // 折叠
    void enterEvent(QEnterEvent *event) override; // 展开
    void leaveEvent(QEvent *event) override; // 折叠
    // 绘制背景
    void paintEvent(QPaintEvent *event) override;

private:
    void setFold(bool toFold = true); // 设置折叠状态

private:
    QPropertyAnimation* m_foldAnimation = nullptr; // 折叠窗口动画
    QTimer* m_foldTimer = nullptr; // 折叠定时器

    bool m_isFold = false; // 是否折叠
    QRect m_fullRect; // 展开窗口数据
    QRect m_foldRect; // 折叠窗口数据
};

#endif // DYNAMICISLAND_H