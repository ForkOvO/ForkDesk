#ifndef THEMEBUTTON_H
#define THEMEBUTTON_H

#include "definestd.h"
#include <QPushButton>

class ThemeButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ThemeButton(QWidget *parent = nullptr, QString name = "ten_OvO", int size = 50);
    ~ThemeButton();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_name;
};

#endif // THEMEBUTTON_H
