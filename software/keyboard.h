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
    explicit Keyboard(QWidget *parent = nullptr);
    ~Keyboard();

    void onKeyPress(QString key);
    void onKeyRelease(QString key);

private:
    QMap<QString, KeyboardItem*> m_keyMap; // 键盘元素映射

    KeyboardListener* m_listener = nullptr; // 键盘监听器
};

#endif // KEYBOARD_H