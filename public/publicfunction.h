#ifndef PUBLICFUNCTION_H
#define PUBLICFUNCTION_H

// 单例模式 公共函数

#include <QObject>
#include <mutex>

class PublicFunction
{
public:
    // 单例模式 禁止拷贝构造和赋值操作
    PublicFunction(const PublicFunction&) = delete;
    PublicFunction& operator=(const PublicFunction&) = delete;

    static PublicFunction* instance();

    // 否客岛通知
    void DynamicIslandNotification(QString content);
    void setDynamicIslandNotification(std::function<void(QString)> func);

    // 主题窗口软件窗口管理
    void CentralWidgetAddSoftware(QString name, QWidget* widget);
    void setCentralWidgetAddSoftware(std::function<void(QString, QWidget*)> func);
    void CentralWidgetRemoveSoftware(QString name);
    void setCentralWidgetRemoveSoftware(std::function<void(QString)> func);

private:
    explicit PublicFunction() = default;
    static std::atomic<PublicFunction*> m_instance; // 单例实例指针
    static std::mutex m_mutex; // 保证线程安全

    std::function<void(QString)> m_dynamicIslandNotification = nullptr; // 否客岛通知
    // 主题窗口软件窗口管理
    std::function<void(QString, QWidget*)> m_centralWidgetAddSoftware = nullptr;
    std::function<void(QString)> m_centralWidgetRemoveSoftware = nullptr;
};

#endif // PUBLICFUNCTION_H