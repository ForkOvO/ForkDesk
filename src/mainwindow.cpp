#include "mainwindow.h"
#include "publiccache.h"
#include "centralwidget.h"

#include <QScreen>
#include <QGuiApplication>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QPainter>
#include <QGradient>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 折叠展开数据
    m_fullRect = QGuiApplication::primaryScreen()->availableGeometry(); // 全屏不包含任务栏
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
    m_centralWidget->setFixedSize(size());
    m_centralWidget->move(0, 0);

    // 添加窗口到缓存
    PublicCache* cache = PublicCache::instance();
    cache->addWidget(this);
    update();
}

MainWindow::~MainWindow()
{
}

void MainWindow::changeFoldStatus()
{
    STD_DEBUG(MainWindow.cpp) << "changeFoldStatus";
    m_isFold = !m_isFold; // 切换折叠状态
    m_foldAnimation->setStartValue(this->geometry());
    m_foldAnimation->setEndValue(m_isFold ? m_foldRect : m_fullRect);
    m_foldAnimation->start(); // 开始动画
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
    QLinearGradient gradient(0, height(), width(), 0); // 从左下角到右上角
    PublicCache *cache = PublicCache::instance();
    if (cache->get("theme").toString() == "dark")
    {
        gradient.setColorAt(0, m_backColors[0]);
        gradient.setColorAt(1, m_backColors[1]);
    }
    else
    {
        gradient.setColorAt(0, m_backColors[2]);
        gradient.setColorAt(1, m_backColors[3]);
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient);
    if (m_isFold) painter.drawRoundedRect(rect(), 10, 10);
    else painter.drawRect(rect());
    QMainWindow::paintEvent(event);
}
