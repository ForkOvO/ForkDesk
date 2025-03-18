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

    m_defaultButton = new QPushButton("默认键盘", this);
    m_defaultButton->setGeometry(200, 100, 100, 50);
    connect(m_defaultButton, &QPushButton::clicked, this, [&]{
        if (m_currKeyboard) delete m_currKeyboard;
        m_currKeyboard = new Keyboard(Keyboard::Default);
        m_currKeyboard->show();
    });

    m_xiaoheButton = new QPushButton("小鹤双拼", this);
    m_xiaoheButton->setGeometry(200, 200, 100, 50);
    connect(m_xiaoheButton, &QPushButton::clicked, this, [&]{
        if (m_currKeyboard) delete m_currKeyboard;
        m_currKeyboard = new Keyboard(Keyboard::XiaoHe);
        m_currKeyboard->show();
    });


    STD_DEBUG(KeyboardSetting.cpp) << "create keyboard setting widget";
}

KeyboardSetting::~KeyboardSetting()
{
    STD_DEBUG(KeyboardSetting.cpp) << "destroy keyboard setting widget";
}
