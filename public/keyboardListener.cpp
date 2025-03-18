#include "keyboardListener.h"

std::atomic<KeyboardListener*> KeyboardListener::m_instance = nullptr;
std::mutex KeyboardListener::m_mutex;
HHOOK KeyboardListener::m_hHook = nullptr;

KeyboardListener *KeyboardListener::instance()
{
    KeyboardListener* instance = m_instance.load(); // 获取单例
    if (!instance) // 如果单例不存在，则创建单例
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 加锁
        instance = m_instance.load(); // 再次获取单例
        if (!instance) // 双重检查，确保单例不存在
        {
            instance = new KeyboardListener();
            m_instance.store(instance); // 存储单例
        }
    }
    return instance;
}

KeyboardListener::KeyboardListener()
{
    m_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyHookProc, GetModuleHandle(NULL), 0); // 安装键盘钩子
}

KeyboardListener::~KeyboardListener()
{
    if (m_hHook != nullptr) // 卸载键盘钩子
    {
        UnhookWindowsHookEx(m_hHook);
    }
}

LRESULT CALLBACK KeyboardListener::keyHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode < 0) return CallNextHookEx(m_hHook, nCode, wParam, lParam);

    QString emitStr = "暂未添加"; // 按键字符串
    unsigned int code = ((KBDLLHOOKSTRUCT*)lParam)->vkCode; // 按键码

    if (code >= 65 && code <= 90) // A-Z
        emitStr = QString(char(code));
    else if (code >= 112 && code <= 123) // F1-F12
        emitStr = QString("F%1").arg(code - 111);
    else if (code >= 48 && code <= 57) // 0-9
        emitStr = QString(char(code));
    else
    {
        switch (code) {
        case 8:
            emitStr = "Backspace";
            break;
        case 9:
            emitStr = "TAB";
            break;
        case 13:
            emitStr = "Enter";
            break;
        case 20:
            emitStr = "CAPS";
            break;
        case 27:
            emitStr = "ESC";
            break;
        case 32:
            emitStr = "Space";
            break;
        case 33:
            emitStr = "Page Up";
            break;
        case 34:
            emitStr = "Page Down";
            break;
        case 35:
            emitStr = "End";
            break;
        case 36:
            emitStr = "Home";
            break;
        case 37:
            emitStr = "Left";
            break;
        case 38:
            emitStr = "Up";
            break;
        case 39:
            emitStr = "Right";
            break;
        case 40:
            emitStr = "Down";
            break;
        case 45:
            emitStr = "Insert";
            break;
        case 46:
            emitStr = "Delete";
            break;
        case 75:
            emitStr = "Delete";
            break;
        case 91:
        case 92:
            emitStr = "Win";
            break;
        case 160: // 左shift
        case 161: // 右shift
            emitStr = "Shift";
            break;
        case 162: // 左Control
        case 163: // 右Control
            emitStr = "Control";
            break;
        case 164: // 左Alt
        case 165: // 右Alt
            emitStr = "Alt";
            break;
        case 186:
            emitStr = ";:";
            break;
        case 187:
            emitStr = "=+";
            break;
        case 188:
            emitStr = ",<";
            break;
        case 189:
            emitStr = "-_";
            break;
        case 190:
            emitStr = ".>";
            break;
        case 191:
            emitStr = "/?";
            break;
        case 192:
            emitStr = "`~";
            break;
        case 219:
            emitStr = "[{";
            break;
        case 220:
            emitStr = "\\|";
            break;
        case 221:
            emitStr = "]}";
            break;
        case 222:
            emitStr = "'\"";
            break;
        default:
            emitStr = "暂未添加";
            break;
        }
    }

    if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) emit instance()->keyPress(emitStr); // 键盘按下
    else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) emit instance()->keyRelease(emitStr); // 键盘抬起

    return CallNextHookEx(m_hHook, nCode, wParam, lParam);
}
