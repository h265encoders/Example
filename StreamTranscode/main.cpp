#include <QCoreApplication>
#include "Link.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *net=Link::create("InputNet");
    QVariantMap dataNet;
    dataNet["path"]="rtsp://admin:admin@192.168.1.23/cam/realmonitor?channel=1&subtype=0";
    net->start(dataNet);

    LinkObject *dec=Link::create("DecodeV");
    dec->start();

    LinkObject *encV=Link::create("EncodeV");
    QVariantMap dataEncV;
    dataEncV["codec"]="h265";
    dataEncV["width"]=-1;
    dataEncV["height"]=-1;
    dataEncV["rcmode"]="vbr";
    dataEncV["bitrate"]=1000;
    encV->start(dataEncV);

    LinkObject *rtspServer=Link::create("Rtsp");
    rtspServer->start();

    LinkObject *rtsp=Link::create("Mux");
    QVariantMap dataRtsp;
    dataRtsp["path"]="mem://test";
    dataRtsp["format"]="rtsp";
    rtsp->start(dataRtsp);

    net->linkA(rtsp)->linkA(rtspServer);
    net->linkV(dec)->linkV(encV)->linkV(rtsp)->linkV(rtspServer);

    return a.exec();
}

