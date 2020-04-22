#include <QCoreApplication>
#include "Link.h"
#include "../VIO/interface.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *ai=Link::create("InputAi");
    QVariantMap dataAi;
    dataAi["interface"]=INTERFACE_AUDIO;
    ai->start(dataAi);

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]=INTERFACE_VIDEO;
    vi->start(dataVi);

    LinkObject *encA=Link::create("EncodeA");
    QVariantMap dataEncA;
    dataEncA["codec"]="aac";
    dataEncA["samplerate"]=48000;
    dataEncA["bitrate"]=128;
    encA->start(dataEncA);

    LinkObject *encV=Link::create("EncodeV");
    QVariantMap dataEncV;
    dataEncV["codec"]="h264";
    dataEncV["width"]=1920;
    dataEncV["height"]=1080;
    dataEncV["bitrate"]=4000;
    encV->start(dataEncV);

    LinkObject *overlay=Link::create("Overlay");
    QVariantMap dataOver;
    QVariantList lays;
    QVariantMap lay;
    lay["type"]="time";
    lay["enable"]=true;
    lay["font"]="/link/res/font.ttf";
    lay["content"]="yyyy年MM月dd日 hh:mm:ss";
    lay["x"]=0.1;
    lay["y"]=0.1;
    lay["scale"]=3;
    lay["color"]="#ffffff";
    lay["alpha"]=1;
    lays<<lay;
    dataOver["lays"]=lays;
    overlay->start(dataOver);


    LinkObject *mp4=Link::create("Mux");
    QVariantMap dataMP4;
    dataMP4["path"]="test_%d.mp4";
    dataMP4["segmentDuration"]=10000;//10s
    //dataMP4["segmentSize"]=5*1024*1024;//5M

    ai->linkA(encA)->linkA(mp4);
    vi->linkV(overlay)->linkV(encV)->linkV(mp4);

    mp4->start(dataMP4);

    qDebug()<<"Press any key to stop";
    getchar();
    mp4->stop();

    return a.exec();
}

