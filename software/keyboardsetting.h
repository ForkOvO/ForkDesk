#ifndef KEYBOARDSETTING_H
#define KEYBOARDSETTING_H

// 键盘设置

#include <QWidget>

class QPushButton;

class KeyboardSetting : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardSetting(QWidget *parent = nullptr);
    ~KeyboardSetting();

private:
    QPushButton* m_switchButton = nullptr; // 开关按钮
};

#endif // KEYBOARDSETTING_H