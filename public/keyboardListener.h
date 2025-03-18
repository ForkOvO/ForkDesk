#ifndef KEYBOARDLISTENER_H
#define KEYBOARDLISTENER_H

// 单例模式 键盘监听器

#include <QObject>
#include <Windows.h>
#include <functional>
#include <mutex>

class KeyboardListener : public QObject
{
    Q_OBJECT
public:
    // 单例模式 禁止拷贝构造和赋值操作
    KeyboardListener(const KeyboardListener&) = delete;
    KeyboardListener& operator=(const KeyboardListener&) = delete;

    static KeyboardListener* instance(); // 获取单例实例

    static LRESULT CALLBACK keyHookProc(int nCode, WPARAM wParam, LPARAM lParam); // 键盘钩子回调函数

signals:
    void keyPress(QString key);
    void keyRelease(QString key);

private:
    explicit KeyboardListener();
    ~KeyboardListener();
    static std::atomic<KeyboardListener*> m_instance; // 单例实例指针
    static std::mutex m_mutex; // 保证线程安全
    static HHOOK m_hHook; // 键盘钩子句柄
};

#endif // KEYBOARDLISTENER_H