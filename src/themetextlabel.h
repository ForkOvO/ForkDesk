#ifndef THEMETEXTLABEL_H
#define THEMETEXTLABEL_H

#include <QLabel>

class ThemeTextLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ThemeTextLabel(QWidget *parent = nullptr, QString text = "");
    ~ThemeTextLabel();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // THEMETEXTLABEL_H