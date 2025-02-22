#ifndef DOCKBAR_H
#define DOCKBAR_H

// 底部栏

#include "definestd.h"
#include <QWidget>

class DockBar : public QWidget
{
    Q_OBJECT
public:
    explicit DockBar(QWidget *parent = nullptr);
    ~DockBar();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // DOCKBAR_H