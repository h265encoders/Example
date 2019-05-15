#include "Source.h"
#include "Json.h"

Source::Source(QObject *parent) : LinkObject(parent),dataSocket(this),infoSocket(this)
{
    data["memSize"]=4096000;//4M
}

void Source::onStart()
{
    dataSocket.bind(5000);
    infoSocket.bind(5001);
    connect(&dataSocket,SIGNAL(readyRead()),this,SLOT(onReadData()));
    connect(&infoSocket,SIGNAL(readyRead()),this,SLOT(onReadInfo()));

}

void Source::onReadData()
{
    while(dataSocket.hasPendingDatagrams())
    {
        char *buf=bufferData(NULL,dataSocket.pendingDatagramSize());
        int len=dataSocket.readDatagram(buf,dataSocket.pendingDatagramSize());

        PktHeader head;
        memcpy(&head,buf,sizeof(PktHeader));
        buf+=sizeof(PktHeader);
        len-=sizeof(PktHeader);

        Packet pkt;
        pkt.data=buf;
        pkt.len=len;
        pkt.pts=head.pts;
        pkt.dts=head.pts;
        pkt.type=head.isIframe?Packet::IFrame:Packet::PFrame;

        sendPacketV(pkt);
    }
}

void Source::onReadInfo()
{
    infoSelfV.type=StreamInfo::H264;
    QByteArray ba;
    ba.resize(infoSocket.pendingDatagramSize());
    infoSocket.readDatagram(ba.data(),ba.size());
    infoSelfV.info=Json::decode(ba).toMap();

    sendInfoV(infoSelfV);
}

