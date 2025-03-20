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

private:
    explicit PublicFunction() = default;
    static std::atomic<PublicFunction*> m_instance; // 单例实例指针
    static std::mutex m_mutex; // 保证线程安全

    std::function<void(QString)> m_dynamicIslandNotification = nullptr; // 否客岛通知
};

#endif // PUBLICFUNCTION_H