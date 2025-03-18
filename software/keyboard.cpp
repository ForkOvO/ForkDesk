#include "keyboard.h"
#include "keyboarditem.h"
#include "keyboardlistener.h"

#include <QGuiApplication>
#include <QScreen>

Keyboard::Keyboard(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool); // 无边框 | 置顶 | 无任务栏
    setAttribute(Qt::WA_TranslucentBackground); // 透明背景

    QRect rect = QGuiApplication::primaryScreen()->availableGeometry();
    setGeometry(rect.width() - 500, rect.height() - 200, 400, 120);

    m_keyMap["A"] = new KeyboardItem("A", this);
    m_keyMap["B"] = new KeyboardItem("B", this);
    m_keyMap["C"] = new KeyboardItem("C", this);
    m_keyMap["D"] = new KeyboardItem("D", this);
    m_keyMap["E"] = new KeyboardItem("E", this);
    m_keyMap["F"] = new KeyboardItem("F", this);
    m_keyMap["G"] = new KeyboardItem("G", this);
    m_keyMap["H"] = new KeyboardItem("H", this);
    m_keyMap["I"] = new KeyboardItem("I", this);
    m_keyMap["J"] = new KeyboardItem("J", this);
    m_keyMap["K"] = new KeyboardItem("K", this);
    m_keyMap["L"] = new KeyboardItem("L", this);
    m_keyMap["M"] = new KeyboardItem("M", this);
    m_keyMap["N"] = new KeyboardItem("N", this);
    m_keyMap["O"] = new KeyboardItem("O", this);
    m_keyMap["P"] = new KeyboardItem("P", this);
    m_keyMap["Q"] = new KeyboardItem("Q", this);
    m_keyMap["R"] = new KeyboardItem("R", this);
    m_keyMap["S"] = new KeyboardItem("S", this);
    m_keyMap["T"] = new KeyboardItem("T", this);
    m_keyMap["U"] = new KeyboardItem("U", this);
    m_keyMap["V"] = new KeyboardItem("V", this);
    m_keyMap["W"] = new KeyboardItem("W", this);
    m_keyMap["X"] = new KeyboardItem("X", this);
    m_keyMap["Y"] = new KeyboardItem("Y", this);
    m_keyMap["Z"] = new KeyboardItem("Z", this);

    QList<KeyboardItem*> firstFloor; // 第一层
    firstFloor << m_keyMap["Q"];
    firstFloor << m_keyMap["W"];
    firstFloor << m_keyMap["E"];
    firstFloor << m_keyMap["R"];
    firstFloor << m_keyMap["T"];
    firstFloor << m_keyMap["Y"];
    firstFloor << m_keyMap["U"];
    firstFloor << m_keyMap["I"];
    firstFloor << m_keyMap["O"];
    firstFloor << m_keyMap["P"];

    QList<KeyboardItem*> secondFloor; // 第二层
    secondFloor << m_keyMap["A"];
    secondFloor << m_keyMap["S"];
    secondFloor << m_keyMap["D"];
    secondFloor << m_keyMap["F"];
    secondFloor << m_keyMap["G"];
    secondFloor << m_keyMap["H"];
    secondFloor << m_keyMap["J"];
    secondFloor << m_keyMap["K"];
    secondFloor << m_keyMap["L"];

    QList<KeyboardItem*> thirdFloor; // 第三层
    thirdFloor << m_keyMap["Z"];
    thirdFloor << m_keyMap["X"];
    thirdFloor << m_keyMap["C"];
    thirdFloor << m_keyMap["V"];
    thirdFloor << m_keyMap["B"];
    thirdFloor << m_keyMap["N"];
    thirdFloor << m_keyMap["M"];

    QList<QList<KeyboardItem*>> m_items;
    m_items << firstFloor << secondFloor << thirdFloor;

    for (int i = 0; i < m_items.size(); i++)
    {
        for (int j = 0; j < m_items[i].size(); j++)
        {
            m_items[i][j]->move(j * 40 + i * 20, i * 40);
        }
    }

    // 键盘监听器
    m_listener = KeyboardListener::instance();
    connect(m_listener, &KeyboardListener::keyPress, this, &Keyboard::onKeyPress);
    connect(m_listener, &KeyboardListener::keyRelease, this, &Keyboard::onKeyRelease);
}

Keyboard::~Keyboard()
{
}

void Keyboard::onKeyPress(QString key)
{
    if (m_keyMap.contains(key)) m_keyMap[key]->setPressed(true);
}

void Keyboard::onKeyRelease(QString key)
{
    if (m_keyMap.contains(key)) m_keyMap[key]->setPressed(false);
}
