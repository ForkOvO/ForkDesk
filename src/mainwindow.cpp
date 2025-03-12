#include "mainwindow.h"
#include "publiccache.h"
#include "centralwidget.h"
#include "themebutton.h"

#include <QScreen>
#include <QGuiApplication>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QPainter>
#include <QGradient>
#include <QPainterPath>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 折叠展开数据
    m_fullRect = QGuiApplication::primaryScreen()->geometry(); // 全屏
    m_foldRect = QRect(m_fullRect.width() - 50, m_fullRect.height() / 2 - 25, 50, 50); // 右方居中
    m_foldAnimation = new QPropertyAnimation(this, "geometry"); // 折叠动画
    m_foldAnimation->setDuration(300);

    // 设置窗口属性
    setWindowTitle("Fork桌面 - 十_OvO脱发开发中"); // 设置窗口标题
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint); // 无边框 | 窗口置底
    setAttribute(Qt::WA_TranslucentBackground); // 透明
    setGeometry(m_fullRect); // 初始窗口大小

    // 中心控件
    m_centralWidget = new CentralWidget(this);
    m_centralWidget->move(0, 0);

    // 折叠开关按钮
    m_foldSwitchBtn = new ThemeButton(this);
    m_foldSwitchBtn->move(0, 0);
    connect(m_foldSwitchBtn, &QPushButton::clicked, this, &MainWindow::changeFoldStatus); // 折叠切换

    // 添加窗口到缓存
    PublicCache* cache = PublicCache::instance();
    cache->addWidget(this);
    update();

    hideTaskBar(); // 隐藏任务栏
}

MainWindow::~MainWindow()
{
    showTaskBar(); // 显示任务栏
}

void MainWindow::changeFoldStatus()
{
    STD_DEBUG(MainWindow.cpp) << "changeFoldStatus";
    m_isFold = !m_isFold; // 切换折叠状态
    m_foldAnimation->setStartValue(this->geometry());
    m_foldAnimation->setEndValue(m_isFold ? m_foldRect : m_fullRect);
    m_foldAnimation->start(); // 开始动画

    if (m_isFold)
    {
        m_centralWidget->hide();
        showTaskBar();
    }
    else
    {
        m_centralWidget->show();
        hideTaskBar();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (m_isFold && (event->buttons() & Qt::RightButton)) // 折叠状态右键开始移动
    {
        m_startPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isFold && (event->buttons() & Qt::RightButton)) // 移动窗口并存储位置
    {
        move(event->globalPosition().toPoint() - m_startPos);
        m_foldRect = geometry();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    if (m_isFold) // 折叠绘制圆角
    {
        QPainterPath path;
        path.addRoundedRect(rect(), width() / 5, width() / 5);
        painter.setClipPath(path);
    }
    // 渐变背景
    QPixmap pixmap;
    QString theme = PublicCache::instance()->get("theme").toString();
    if (theme == "dark") painter.drawPixmap(this->rect(), QPixmap(":/res/desktop_1.svg"));
    else painter.drawPixmap(this->rect(), QPixmap(":/res/desktop_0.svg"));
    QMainWindow::paintEvent(event);
}

void MainWindow::hideTaskBar()
{
    HWND taskbar = FindWindow(L"Shell_TrayWnd", NULL);
    ShowWindow(taskbar, SW_HIDE);
}

void MainWindow::showTaskBar()
{
    HWND taskbar = FindWindow(L"Shell_TrayWnd", NULL);
    ShowWindow(taskbar, SW_SHOW);
}
