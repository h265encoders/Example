#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Link.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void init();
    LinkObject *ai_1,*ai_2,*vi_1,*vi_2;
    LinkObject *mixA,*mixV,*ao,*vo;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
