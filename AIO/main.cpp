#include <QCoreApplication>
#include "Link.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Link::init();

    LinkObject *ai=Link::create("InputAi");
    QVariantMap dataAi;
    dataAi["interface"]="HDMI-A";
    ai->start(dataAi);

    LinkObject *ao=Link::create("OutputAo");
    QVariantMap dataAo;
    dataAo["interface"]="HDMI-OUT";
    ao->start(dataAo);

    ai->linkA(ao);

    return a.exec();
}

