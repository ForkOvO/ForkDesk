#ifndef KEYBOARDSETTING_H
#define KEYBOARDSETTING_H

// 键盘设置

#include <QWidget>

class KeyboardSetting : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardSetting(QWidget *parent = nullptr);
    ~KeyboardSetting();
};

#endif // KEYBOARDSETTING_H