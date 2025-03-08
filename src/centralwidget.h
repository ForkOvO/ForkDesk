#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

// 主体窗口

#include <QWidget>

// 自定义
class MainWindow; // 折叠窗口
class ThemeButton; // 主题按钮
class DockBar; // 底部栏

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);

private:
    DockBar* m_dockBar = nullptr; // 底部栏
    
    ThemeButton* m_themeSwitchBtn = nullptr; // 主题切换
    ThemeButton* m_githubBtn = nullptr; // GitHub
    ThemeButton* m_bilibiliBtn = nullptr; // Bilibili
};

#endif // CENTRALWIDGET_H
