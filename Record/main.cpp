#include <QCoreApplication>
#include "Link.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *ai=Link::create("InputAi");
    QVariantMap dataAi;
    dataAi["interface"]="HDMI-A";
    ai->start(dataAi);

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]="HDMI-A";
    vi->start(dataVi);

    LinkObject *encA=Link::create("EncodeA");
    QVariantMap dataEncA;
    dataEncA["codec"]="aac";
    dataEncA["samplerate"]=48000;
    dataEncA["bitrate"]=32;
    encA->start(dataEncA);

    LinkObject *encV=Link::create("EncodeV");
    QVariantMap dataEncV;
    dataEncV["codec"]="h264";
    dataEncV["width"]=1920;
    dataEncV["height"]=1080;
    dataEncV["bitrate"]=4000;
    encV->start(dataEncV);

    LinkObject *mp4=Link::create("Mux");
    QVariantMap dataMP4;
    dataMP4["path"]="test.mp4";

    ai->linkA(encA)->linkA(mp4);
    vi->linkV(encV)->linkV(mp4);

    mp4->start(dataMP4);

    qDebug()<<"Press any key to stop";
    getchar();

    mp4->stop();

    return a.exec();
}

