#ifndef DOCKBAR_H
#define DOCKBAR_H

// 底部栏

#include "definestd.h"
#include <QWidget>

class QPropertyAnimation;
class DockBar : public QWidget
{
    Q_OBJECT
public:
    explicit DockBar(QWidget *parent = nullptr);
    ~DockBar();

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPropertyAnimation* m_foldAnimation = nullptr; // 折叠动画
    
    QRect m_foldRect; // 折叠矩形
    QRect m_fullRect; // 展开矩形
};

#endif // DOCKBAR_H