#include "centralwidget.h"
#include "publiccache.h"
#include "themebutton.h"
#include "dockbar.h"
#include "dynamicisland.h"
#include "themetextlabel.h"

#include <QPushButton>
#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QScreen>
#include <QGuiApplication>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(parent->size()); // 固定和父窗口一样大
    setAttribute(Qt::WA_TranslucentBackground); // 透明背景
    setGeometry(QGuiApplication::primaryScreen()->availableGeometry()); // 屏幕大小
    setAcceptDrops(true); // 允许外界拖拽进入

    // 底部栏
    m_dockBar = new DockBar(this);

    // 否客岛
    m_dynamicIsland = new DynamicIsland(this);

    // 主题切换按钮
    m_themeSwitchBtn = new ThemeButton(this, "theme", 25);
    connect(m_themeSwitchBtn, &QPushButton::clicked, this, [&](){
        PublicCache *cache = PublicCache::instance();
        if (cache->get("theme").toString() == "dark") cache->set("theme", "white");
        else cache->set("theme", "dark");
    }); // 主题切换
    // github按钮
    m_githubBtn = new ThemeButton(this, "github", 25);
    connect(m_githubBtn, &QPushButton::clicked, this, [&](){ QDesktopServices::openUrl(QUrl("https://github.com/ForkOvO/ForkDesk")); }); // 打开github仓库
    // bilibili按钮
    m_bilibiliBtn = new ThemeButton(this, "bilibili", 25);
    connect(m_bilibiliBtn, &QPushButton::clicked, this, [&](){ QDesktopServices::openUrl(QUrl("https://space.bilibili.com/387426555")); }); // 打开bilibili
    // 时间标签
    m_timeLabel = new ThemeTextLabel(this, "xxxx-xx-xx xx:xx");
    m_timeLabel->setFixedSize(120, 25);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [&](){m_timeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm")); }); // 更新时间
    m_timer->start(1000); // 每秒更新时间

    // 布局
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(m_githubBtn);
    btnLayout->addWidget(m_bilibiliBtn);
    btnLayout->addWidget(m_themeSwitchBtn);
    btnLayout->addWidget(m_timeLabel);
    
    // 主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(btnLayout);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(0, 0, 0, 0); // 设置边距
}

void CentralWidget::dragEnterEvent(QDragEnterEvent *event)
{
    STD_DEBUG(CentralWidget.cpp) << "dragEnterEvent";
    // 如果是本地二进制可执行文件则接受拖拽
    if (event->mimeData()->hasUrls())
    {
        for (const QUrl &url : event->mimeData()->urls())
        {
            if (!url.isLocalFile() || !QFileInfo(url.toLocalFile()).isExecutable())
            {
                STD_DEBUG(MainWindow.cpp) << "one of the files is not executable";
                m_dynamicIsland->notification("其中一个文件不是可执行文件");
                return;
            }
        }
        event->acceptProposedAction();
    }
}

void CentralWidget::dropEvent(QDropEvent *event)
{
    STD_DEBUG(CentralWidget.cpp) << "dropEvent";
    // 获取拖拽的文件路径
    for (const QUrl &url : event->mimeData()->urls())
    {
        m_dockBar->addItem(url.toLocalFile());
        m_dynamicIsland->notification("成功拖入可执行文件");
    }
}

void CentralWidget::paintEvent(QPaintEvent *event)
{
    // 顶部菜单栏背景
    QPainterPath path;
    path.moveTo(0, 0); // 左上开始
    path.lineTo(width(), 0); // 右上角
    path.lineTo(width(), 25); // 右下角
    path.lineTo(60, 25); // 接壤圆弧右侧
    path.arcTo(50, 25, 20, 20, 90, 90); // 接壤圆弧
    path.lineTo(50, 40); // 折叠按钮右侧
    path.arcTo(30, 30, 20, 20, 0, -90); // 折叠按钮右下角圆弧
    path.lineTo(0, 50); // 左下角
    path.closeSubpath();
    
    QPainter painter(this);
    painter.fillPath(path, QBrush(QColor("#40808080")));
    QWidget::paintEvent(event);
}
