#include <QCoreApplication>
#include "Link.h"
#include "../VIO/interface.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Link::init();

    LinkObject *ai=Link::create("InputAi");
    QVariantMap dataAi;
    dataAi["interface"]=INTERFACE_AUDIO;
    ai->start(dataAi);

    LinkObject *ao=Link::create("OutputAo");
    QVariantMap dataAo;
    dataAo["interface"]="HDMI-OUT";
    ao->start(dataAo);

    ai->linkA(ao);

    return a.exec();
}

