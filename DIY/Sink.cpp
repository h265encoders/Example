#include "Sink.h"
#include "Json.h"

Sink::Sink(QObject *parent) : LinkObject(parent),socket(this)
{    
    data["memSize"]=4096000;//4M
    data["dataPort"]=5000;
    data["infoPort"]=5001;
    dataPort=5000;
    infoPort=5001;
}

void Sink::onStart()
{
    socket.bind();
}

void Sink::onStop()
{
    socket.close();
}

void Sink::onSetData(QVariantMap newData)
{
    dataPort=data["dataPort"].toInt();
    infoPort=data["infoPort"].toInt();
    ip.setAddress(data["ip"].toString());
    if(!newData.isEmpty() && infoSrcV.type!=StreamInfo::UnKnow)
        onNewInfoV(infoSelfV);
}

void Sink::onNewInfoV(StreamInfo info)
{
    infoSrcV=info;

    if(!ip.isNull())
        socket.writeDatagram(Json::encode(info.info).toLatin1(),ip,infoPort);
}

void Sink::onNewPacketV(LinkObject::Packet pkt)
{
    if(ip.isNull())
        return;

    char *buf=bufferData(NULL,pkt.len+sizeof(PktHeader));
    PktHeader header;
    header.pts=pkt.pts;
    header.dts=pkt.dts;
    header.isIframe=(pkt.type==Packet::IFrame);
    memcpy(buf,&header,sizeof(PktHeader));
    memcpy(buf+sizeof(PktHeader),pkt.data,pkt.len);

    socket.writeDatagram(buf,pkt.len+sizeof(PktHeader),ip,dataPort);
}

