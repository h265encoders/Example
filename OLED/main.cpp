#include "Widget.h"
#include <QApplication>
#include <QDebug>
#include <LinkUI.h>

int main(int argc, char *argv[])
{
    Link::init();
    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);
    QApplication a(argc, argv);

    Widget w;
    LinkUI::initOLED(&w);
    w.setText("192.168.1.212");

    LinkUI::refreshOLED();

    return a.exec();
}
