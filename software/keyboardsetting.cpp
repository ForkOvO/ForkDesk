#include "keyboardsetting.h"
#include "definestd.h"
#include "keyboard.h"

#include <QPushButton>

KeyboardSetting::KeyboardSetting(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(500, 300);
    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("background-color: #ffffff");

    m_switchButton = new QPushButton("打开", this);
    connect(m_switchButton, &QPushButton::clicked, this, [&]{
        Keyboard* keyboard = new Keyboard;
        keyboard->show();
    });

    STD_DEBUG(KeyboardSetting.cpp) << "create keyboard setting widget";
}

KeyboardSetting::~KeyboardSetting()
{
    STD_DEBUG(KeyboardSetting.cpp) << "destroy keyboard setting widget";
}
