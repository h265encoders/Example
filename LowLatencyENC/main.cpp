#include <QCoreApplication>
#include "Link.h"

//#define RTSP
//#define UDP
#define RTMP

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Link::init();

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]="HDMI-A";
    vi->start(dataVi);

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    dataVo["lowLatency"]=true;
    vo->start(dataVo);

    vi->linkV(vo);

    LinkObject *encV=Link::create("EncodeV");
    QVariantMap dataEncV;
    dataEncV["codec"]="h264";
    dataEncV["framerate"]=60;
    dataEncV["width"]=1920;
    dataEncV["height"]=1080;
    dataEncV["bitrate"]=8000;
    dataEncV["lowLatency"]=true;
    encV->start(dataEncV);

    LinkObject *mux=Link::create("Mux");
    QVariantMap dataRtsp;
#ifdef RTSP
    dataRtsp["path"]="mem://test";
    dataRtsp["format"]="rtsp";
#elif defined UDP
    dataRtsp["path"]="mem://test";
    dataRtsp["format"]="mpegts";
#elif defined RTMP
    dataRtsp["path"]="rtmp://127.0.0.1/live/test";
    dataRtsp["format"]="flv";
#endif
    dataRtsp["mute"]=true;
    mux->start(dataRtsp);



#ifdef RTSP
    LinkObject *rtspServer=Link::create("Rtsp");
    rtspServer->start();
    vi->linkV(encV)->linkV(mux)->linkV(rtspServer);
#elif defined UDP
    LinkObject *udp=Link::create("TSUdp");
    QVariantMap dataUDP;
    dataUDP["ip"]="192.168.1.77";
    dataUDP["port"]=1234;
    udp->start(dataUDP);
    vi->linkV(encV)->linkV(mux)->linkV(udp);
#elif defined RTMP
    vi->linkV(encV)->linkV(mux);
#endif

    return a.exec();
}
