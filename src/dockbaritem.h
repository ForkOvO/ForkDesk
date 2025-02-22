#ifndef DOCKBARITEM_H
#define DOCKBARITEM_H

// 底部栏子元素

#include <QPushButton>

class DockBarItem : public QPushButton
{
    Q_OBJECT
public:
    explicit DockBarItem(QWidget *parent = nullptr);
    ~DockBarItem();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // DOCKBARITEM_H