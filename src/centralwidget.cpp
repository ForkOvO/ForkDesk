#include "centralwidget.h"
#include "mainwindow.h"
#include "publiccache.h"
#include "themebutton.h"
#include "dockbar.h"

#include <QPushButton>
#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QScreen>
#include <QGuiApplication>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    m_parent = static_cast<MainWindow*>(parent); // 折叠窗口
    setFixedSize(m_parent->size()); // 固定大小

    setAttribute(Qt::WA_TranslucentBackground); // 透明背景
    setGeometry(QGuiApplication::primaryScreen()->availableGeometry()); // 屏幕大小

    // 折叠开关按钮
    m_foldSwitchBtn = new ThemeButton(this);
    m_foldSwitchBtn->move(0, 0);
    connect(m_foldSwitchBtn, &QPushButton::clicked, m_parent, &MainWindow::changeFoldStatus); // 折叠切换

    // 底部栏
    m_dockBar = new DockBar(this);

    // 主题切换按钮
    m_themeSwitchBtn = new ThemeButton(this, "theme");
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
    // 布局
    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(m_githubBtn);
    btnLayout->addWidget(m_bilibiliBtn);
    btnLayout->addWidget(m_themeSwitchBtn);
    
    // 主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(btnLayout);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(0, 0, 0, 0); // 设置边距
}
