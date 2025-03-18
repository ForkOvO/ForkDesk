#ifndef KEYBOARDSETTING_H
#define KEYBOARDSETTING_H

// 键盘设置

#include <QWidget>

class QPushButton;
class Keyboard;

class KeyboardSetting : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardSetting(QWidget *parent = nullptr);
    ~KeyboardSetting();

private:
    QPushButton* m_defaultButton = nullptr; // 默认键盘按钮
    QPushButton* m_xiaoheButton = nullptr; // 小鹤双拼按钮

    Keyboard* m_currKeyboard = nullptr; // 键盘
};

#endif // KEYBOARDSETTING_H