#include "dockbaritem.h"
#include "definestd.h"

#include <QPainter>
#include <QPainterPath>
#include <QProcess>
#include <QFileInfo>
#include <QFileIconProvider>

DockBarItem::DockBarItem(QWidget *parent, QString name, bool isSystem)
    : QPushButton(parent)
    , m_name(name)
{
    setMouseTracking(true); // 启用鼠标跟踪
    if (isSystem) // 系统应用
    {
        m_icon = QPixmap(":/res/" + m_name + ".svg");
        systemConnect();
    }
    else // 自定义应用
    {
        QFileInfo fileInfo(m_name);
        QFileIconProvider icon;
        m_icon = icon.icon(fileInfo).pixmap(100, 100);
        connect(this, &DockBarItem::clicked, this, [&]{
            QProcess::startDetached(m_name);
        });
    }
    show();
    update();
}

DockBarItem::~DockBarItem()
{
}

void DockBarItem::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    // 圆角
    QPainterPath path;
    path.addRoundedRect(rect(), width() / 5, width() / 5);
    painter.setClipPath(path);
    // 绘制图标
    painter.drawPixmap(rect(), m_icon);
}

void DockBarItem::systemConnect()
{
    if (m_name == "ten_OvO") // 打开此电脑
    {
        connect(this, &DockBarItem::clicked, this, [&]{
            QProcess process;
            process.startDetached("explorer");
            STD_DEBUG(DockBarItem.cpp) << "open explorer";
        });
    }
    if (m_name == "calculator") // 打开计算器
    {
        connect(this, &DockBarItem::clicked, this, [&]{
            QProcess process;
            process.startDetached("calc");
            STD_DEBUG(DockBarItem.cpp) << "open calculator";
        });
    }
    if (m_name == "recycleBin") // 打开回收站
    {
        connect(this, &DockBarItem::clicked, this, [&]{
            QProcess process;
            process.startDetached("explorer.exe", QStringList() << "shell:RecycleBinFolder");
            STD_DEBUG(DockBarItem.cpp) << "open recycleBin";
        });
    }
    if (m_name == "cmd") // 打开命令提示符
    {
        connect(this, &DockBarItem::clicked, this, [&]{
            QProcess process;
            process.startDetached("cmd.exe", QStringList() << "/K" << "start");
            STD_DEBUG(DockBarItem.cpp) << "open cmd";
        });
    }
}
