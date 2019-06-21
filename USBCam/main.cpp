#include <QCoreApplication>
#include "Link.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *cam=Link::create("InputV4l2");
    QVariantMap dataCam;
    dataCam["path"]="/dev/video0";
    dataCam["format"]="mjpeg";
    dataCam["width"]=1280;
    dataCam["height"]=720;
    cam->start(dataCam);

    LinkObject *decV=Link::create("DecodeV");
    decV->start();

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);

    cam->linkV(decV)->linkV(vo);

    LinkObject *alsa=Link::create("InputAlsa");
    QVariantMap dataAlsa;
    dataAlsa["path"]="hw:0,0";
    dataAlsa["channels"]=1;
    alsa->start(dataAlsa);

    LinkObject *ao=Link::create("OutputAo");
    QVariantMap dataAo;
    dataAo["interface"]="HDMI-OUT";
    ao->start(dataAo);

    LinkObject *res=Link::create("Resample");
    res->start();

    alsa->linkA(res)->linkA(ao);

    return a.exec();
}

