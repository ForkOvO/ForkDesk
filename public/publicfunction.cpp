#include "publicfunction.h"

std::atomic<PublicFunction*> PublicFunction::m_instance = nullptr;
std::mutex PublicFunction::m_mutex;

PublicFunction *PublicFunction::instance()
{
    PublicFunction* instance = m_instance.load(); // 获取单例
    if (!instance) // 如果单例不存在，则创建单例
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 加锁
        instance = m_instance.load(); // 再次获取单例
        if (!instance) // 双重检查，确保单例不存在
        {
            instance = new PublicFunction();
            m_instance.store(instance); // 存储单例
        }
    }
    return instance; // 返回单例
}

void PublicFunction::DynamicIslandNotification(QString content)
{
    if (m_dynamicIslandNotification) m_dynamicIslandNotification(content);
}

void PublicFunction::setDynamicIslandNotification(std::function<void(QString)> func)
{
    m_dynamicIslandNotification = func;
}

void PublicFunction::CentralWidgetAddSoftware(QString name, QWidget *widget)
{
    if (m_centralWidgetAddSoftware) m_centralWidgetAddSoftware(name, widget);
}

void PublicFunction::setCentralWidgetAddSoftware(std::function<void(QString, QWidget *)> func)
{
    m_centralWidgetAddSoftware = func;
}

void PublicFunction::CentralWidgetRemoveSoftware(QString name)
{
    if (m_centralWidgetRemoveSoftware) m_centralWidgetRemoveSoftware(name);
}

void PublicFunction::setCentralWidgetRemoveSoftware(std::function<void(QString)> func)
{
    m_centralWidgetRemoveSoftware = func;
}
