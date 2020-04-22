#include "Encoder.h"
#include "../VIO/interface.h"

Encoder::Encoder(QObject *parent) : QObject(parent)
{

}

void Encoder::init()
{
    ai=Link::create("InputAi");
    QVariantMap dataAi;
    dataAi["interface"]=INTERFACE_AUDIO;
    ai->start(dataAi);

    vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]=INTERFACE_VIDEO;
    vi->start(dataVi);

    encA=Link::create("EncodeA");
    QVariantMap dataEncA;
    dataEncA["codec"]="aac";
    dataEncA["samplerate"]=48000;
    dataEncA["bitrate"]=128;
    encA->start(dataEncA);

    encV=Link::create("EncodeV");
    QVariantMap dataEncV;
    dataEncV["codec"]="h264";
    dataEncV["width"]=1920;
    dataEncV["height"]=1080;
    dataEncV["bitrate"]=4000;
    encV->start(dataEncV);

    rtmp=Link::create("Mux");
    QVariantMap dataRtmp;
    dataRtmp["path"]="rtmp://127.0.0.1/live/test";
    rtmp->start(dataRtmp);

    ai->linkA(encA)->linkA(rtmp);
    vi->linkV(encV)->linkV(rtmp);

    rtspServer=Link::create("Rtsp");
    rtspServer->start();

    rtsp=Link::create("Mux");
    QVariantMap dataRtsp;
    dataRtsp["path"]="mem://test";
    dataRtsp["format"]="rtsp";
    rtsp->start(dataRtsp);

    encA->linkA(rtsp)->linkA(rtspServer);
    encV->linkV(rtsp)->linkV(rtspServer);


    rpcServer=new jcon::JsonRpcTcpServer();
    QObjectList objs;
    objs<<this;
    rpcServer->registerServices(objs);
    rpcServer->listen(6001);
}

QVariantMap Encoder::getInputState()
{
    return vi->invoke("getReport").toMap();
}

bool Encoder::setConfig(QVariantMap data)
{
    encV->setData(data);
    return true;
}

