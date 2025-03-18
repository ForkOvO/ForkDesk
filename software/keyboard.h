#ifndef KEYBOARD_H
#define KEYBOARD_H

// 置顶键盘

#include <QWidget>

class KeyboardItem;
class KeyboardListener;

class Keyboard : public QWidget
{
    Q_OBJECT
public:
    enum KeyboardType
    {
        Default,
        XiaoHe
    };

public:
    explicit Keyboard(KeyboardType type = Default, QWidget *parent = nullptr);
    ~Keyboard();

private:
    void xiaoHeInit();

    void onKeyPress(QString key);
    void onKeyRelease(QString key);

private:
    KeyboardType m_type; // 键盘类型
    int m_xiaoHeCount = 0; // 小鹤双拼按下次数

    QMap<QString, KeyboardItem*> m_keyMap; // 键盘元素映射

    KeyboardListener* m_listener = nullptr; // 键盘监听器
};

#endif // KEYBOARD_H