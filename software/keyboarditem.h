#ifndef KEYBOARDITEM_H
#define KEYBOARDITEM_H

// 置顶键盘元素

#include <QWidget>

class KeyboardItem : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardItem(QString str, QWidget *parent = nullptr);
    ~KeyboardItem();

    void setPressed(bool pressed); // 设置按下状态

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_str; // 文本
    bool m_pressed = false; // 是否按下
};

#endif // KEYBOARDITEM_H