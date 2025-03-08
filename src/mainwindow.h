#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// 折叠窗口

#include <QMainWindow>

class QPropertyAnimation;
class CentralWidget;
class ThemeButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeFoldStatus(); // 切换折叠状态

protected:
    // 右键移动折叠浮窗
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    // 渐变背景
    void paintEvent(QPaintEvent *event) override;
    // 拖拽
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    ThemeButton* m_foldSwitchBtn = nullptr; // 折叠开关按钮
    CentralWidget* m_centralWidget = nullptr; // 中心控件
    QPropertyAnimation* m_foldAnimation = nullptr; // 折叠窗口动画

    bool m_isFold = false; // 是否折叠
    QRect m_fullRect; // 展开窗口数据
    QRect m_foldRect; // 折叠窗口数据
    QPoint m_startPos; // 移动窗口起始位置
    QVector<QColor> m_backColors = {
        QColor("#604962"),
        QColor("#0C1824"),
        QColor("#FFF3FF"),
        QColor("#D8EAFF")
    }; // 渐变背景颜色 {暗左 暗右 亮左 亮右}
};

#endif // MAINWINDOW_H
