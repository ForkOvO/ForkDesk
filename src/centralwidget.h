#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

// 主体窗口

#include <QWidget>

// 自定义
class MainWindow; // 折叠窗口
class ThemeButton; // 主题按钮
class DockBar; // 底部栏
class DynamicIsland; // 否客岛
class ThemeTextLabel; // 主题文字

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);

protected:
    // 拖拽
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    // 绘制菜单栏背景
    void paintEvent(QPaintEvent *event) override;

private:
    DockBar* m_dockBar = nullptr; // 底部栏
    DynamicIsland* m_dynamicIsland = nullptr; // 否客岛
    ThemeButton* m_themeSwitchBtn = nullptr; // 主题切换
    ThemeButton* m_githubBtn = nullptr; // GitHub
    ThemeButton* m_bilibiliBtn = nullptr; // Bilibili
    ThemeTextLabel* m_timeLabel = nullptr; // 时间

    QTimer* m_timer = nullptr; // 定时器
};

#endif // CENTRALWIDGET_H
