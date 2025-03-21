#ifndef DOCKBAR_H
#define DOCKBAR_H

// 底部栏

#include "definestd.h"
#include <QWidget>

class DockBarItem;

class DockBar : public QWidget
{
    Q_OBJECT
public:
    explicit DockBar(QWidget *parent = nullptr);
    ~DockBar();

    void addItem(QString name, bool isSystem = false); // 添加按钮

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void initBtns(); // 初始化按钮

private:
    QVector<DockBarItem*> m_items; // 按钮集合
    QRect m_baseRect; // 基础矩形
};

#endif // DOCKBAR_H