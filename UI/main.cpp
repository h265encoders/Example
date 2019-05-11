#include "widget.h"
#include <QApplication>
#include "Link.h"

int main(int argc, char *argv[])
{
    Link::init();

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);

    QApplication a(argc, argv);

    Widget w;
    w.vo=vo;
    w.init();
    w.show();

    return a.exec();
}
