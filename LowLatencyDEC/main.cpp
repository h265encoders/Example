#include <QCoreApplication>
#include "Link.h"

//#define RTSP
//#define UDP
#define RTMP

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
#ifdef RTSP
    dataNet["path"]="rtsp://192.168.1.76/test";
#elif defined UDP
    dataNet["path"]="udp://@:1234";
#elif defined RTMP
    dataNet["path"]="rtmp://192.168.1.76/live/test";
#endif
    dataNet["protocol"]="udp";
    dataNet["buffer"]=false;
    dataNet["sync"]=false;
    net->start(dataNet);

    LinkObject *dec=Link::create("DecodeV");
    QVariantMap dataDec;
    dataDec["lowLatency"]=true;
    dec->start(dataDec);

    net->linkV(dec)->linkV(vo);

    return a.exec();
}

