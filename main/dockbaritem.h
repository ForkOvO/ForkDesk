#ifndef DOCKBARITEM_H
#define DOCKBARITEM_H

// 底部栏子元素

#include <QPushButton>

class DockBarItem : public QPushButton
{
    Q_OBJECT
public:
    explicit DockBarItem(QWidget *parent = nullptr, QString name = "ten_OvO", bool isSystem = true);
    ~DockBarItem();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void systemConnect(); // 系统应用槽函数

private:
    QString m_name; // 应用名称
    QPixmap m_icon; // 应用图标

    QWidget* m_setToWidget = nullptr; // 放置到窗口
};

#endif // DOCKBARITEM_H