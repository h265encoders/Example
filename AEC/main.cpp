#include <QCoreApplication>
#include "Link.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *far=Link::create("InputAi");
    QVariantMap dataFar;
    dataFar["interface"]="HDMI-A";
    far->start(dataFar);

    LinkObject *near=Link::create("InputAlsa");
    QVariantMap dataNear;
    dataNear["path"]="hw:0,0";
    near->start(dataNear);

    LinkObject *speaker=Link::create("OutputAo");
    QVariantMap dataSpk;
    dataSpk["interface"]="HDMI-OUT";
    speaker->start(dataSpk);

    LinkObject *aec=Link::create("AEC");
    QVariantMap dataAEC;
    dataAEC["far"]=far->name();
    dataAEC["near"]=near->name();
    dataAEC["delay"]=100;
    dataAEC["level"]=1;
    aec->start(dataAEC);

    LinkObject *encA=Link::create("EncodeA");
    encA->start();

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]="HDMI-A";
    vi->start(dataVi);

    LinkObject *vo=Link::create("OutputVo");
    vo->start();

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

    LinkObject *resample=Link::create("Resample");
    resample->start();

    vi->linkV(vo);
    far->linkA(speaker);

    aec->linkA(encA)->linkA(rtsp)->linkA(rtspServer);
    vi->linkV(encV)->linkV(rtsp)->linkV(rtspServer);
    near->linkA(resample);

    bool enable=true;
    while(true)
    {
        enable=!enable;

        getchar();
        if(enable)
        {
            qDebug("Enable AEC");
            resample->unLinkA(encA);
            aec->linkA(encA);
        }
        else
        {
            qDebug("Disable AEC");
            aec->unLinkA(encA);
            resample->linkA(encA);
        }
    }

    return a.exec();
}

