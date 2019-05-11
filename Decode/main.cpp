#include <QCoreApplication>
#include "Link.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);

    LinkObject *net=Link::create("InputNet");
    QVariantMap dataNet;
    dataNet["path"]="rtsp://admin:admin@192.168.1.23/cam/realmonitor?channel=1&subtype=0";
    net->start(dataNet);

    LinkObject *dec=Link::create("DecodeV");
    dec->start();

    net->linkV(dec)->linkV(vo);

    return a.exec();
}

