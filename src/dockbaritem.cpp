#include "dockbaritem.h"
#include "definestd.h"

#include <QPainter>
#include <QPainterPath>
#include <QProcess>

DockBarItem::DockBarItem(QWidget *parent, QString name, bool isSystem)
    : QPushButton(parent)
    , m_name(name)
{
    setMouseTracking(true); // 启用鼠标跟踪
    if (isSystem) systemConnect(); // 系统应用
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
    QPixmap pixmap(":/res/" + m_name + ".png");
    painter.drawPixmap(rect(), pixmap);
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
