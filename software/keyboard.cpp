#include "keyboard.h"
#include "keyboarditem.h"
#include "keyboardlistener.h"
#include "publiccache.h"

#include <QGuiApplication>
#include <QScreen>

Keyboard::Keyboard(KeyboardType type, QWidget *parent)
    : QWidget(parent)
    , m_type(type)
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

    switch (type)
    {
    case KeyboardType::XiaoHe:
        xiaoHeInit();
        break;
    default:
        break;
    }

    // 键盘监听器
    m_listener = KeyboardListener::instance();
    connect(m_listener, &KeyboardListener::keyPress, this, &Keyboard::onKeyPress);
    connect(m_listener, &KeyboardListener::keyRelease, this, &Keyboard::onKeyRelease);

    PublicCache::instance()->addWidget(this);
}

Keyboard::~Keyboard()
{
    PublicCache::instance()->removeWidget(this);
}

void Keyboard::xiaoHeInit()
{
    if (m_xiaoHeCount== 0) // 声母
    {
        m_keyMap["Q"]->setStr("q");
        m_keyMap["W"]->setStr("w");
        m_keyMap["E"]->setStr("e");
        m_keyMap["R"]->setStr("r");
        m_keyMap["T"]->setStr("t");
        m_keyMap["Y"]->setStr("y");
        m_keyMap["U"]->setStr("sh");
        m_keyMap["I"]->setStr("ch");
        m_keyMap["O"]->setStr("o");
        m_keyMap["P"]->setStr("p");
        m_keyMap["A"]->setStr("a");
        m_keyMap["S"]->setStr("s");
        m_keyMap["D"]->setStr("d");
        m_keyMap["F"]->setStr("f");
        m_keyMap["G"]->setStr("g");
        m_keyMap["H"]->setStr("h");
        m_keyMap["J"]->setStr("j");
        m_keyMap["K"]->setStr("k");
        m_keyMap["L"]->setStr("l");
        m_keyMap["Z"]->setStr("z");
        m_keyMap["X"]->setStr("x");
        m_keyMap["C"]->setStr("c");
        m_keyMap["V"]->setStr("v");
        m_keyMap["B"]->setStr("b");
        m_keyMap["N"]->setStr("n");
        m_keyMap["M"]->setStr("m");
    }
    else // 韵母
    {
        m_keyMap["Q"]->setStr("iu");
        m_keyMap["W"]->setStr("ei");
        m_keyMap["E"]->setStr("e");
        m_keyMap["R"]->setStr("uan");
        m_keyMap["T"]->setStr("ue\nve");
        m_keyMap["Y"]->setStr("un");
        m_keyMap["U"]->setStr("u");
        m_keyMap["I"]->setStr("i");
        m_keyMap["O"]->setStr("o\nuo");
        m_keyMap["P"]->setStr("ie");
        m_keyMap["A"]->setStr("a");
        m_keyMap["S"]->setStr("iong\nong");
        m_keyMap["D"]->setStr("ai");
        m_keyMap["F"]->setStr("en");
        m_keyMap["G"]->setStr("eng");
        m_keyMap["H"]->setStr("ang");
        m_keyMap["J"]->setStr("an");
        m_keyMap["K"]->setStr("ing\nuai");
        m_keyMap["L"]->setStr("iang\nuang");
        m_keyMap["Z"]->setStr("ou");
        m_keyMap["X"]->setStr("ia\nua");
        m_keyMap["C"]->setStr("ao");
        m_keyMap["V"]->setStr("ui\nv");
        m_keyMap["B"]->setStr("in");
        m_keyMap["N"]->setStr("iao");
        m_keyMap["M"]->setStr("ian");
    }
}

void Keyboard::onKeyPress(QString key)
{
    if (m_keyMap.contains(key)) m_keyMap[key]->setPressed(true);
    switch (m_type)
    {
    case KeyboardType::XiaoHe:
    {
        m_xiaoHeCount = (m_xiaoHeCount + 1) % 2;
        if (key == "Space") m_xiaoHeCount = 0;
        xiaoHeInit();
    }
    default:
        break;
    }
}

void Keyboard::onKeyRelease(QString key)
{
    if (m_keyMap.contains(key)) m_keyMap[key]->setPressed(false);
}