#include <QCoreApplication>
#include "Link.h"
#include "Bypass.h"

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


    LinkObject *rtspServer=Link::create("Rtsp");
    rtspServer->start();

    LinkObject *rtsp=Link::create("Mux");
    QVariantMap dataRtsp;
    dataRtsp["path"]="mem://test";
    dataRtsp["format"]="rtsp";
    rtsp->start(dataRtsp);

    LinkObject *bypass=new Bypass();
    bypass->start();

    ai->linkA(encA)->linkA(bypass)->linkA(rtsp)->linkA(rtspServer);
    vi->linkV(encV)->linkV(bypass)->linkV(rtsp)->linkV(rtspServer);


    return a.exec();
}

