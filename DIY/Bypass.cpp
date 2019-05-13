#include "Bypass.h"

Bypass::Bypass(QObject *parent) : LinkObject(parent)
{

}


void Bypass::onNewInfoA(LinkObject::StreamInfo info)
{
    //此处可以获得输入的流类型、参数等，比如samplerate、extradata等
    //如果手动创建一个数据，比如来自自定义的网络或文件，那么也应该手动构建这些信息。
    //其他参数参见LinkObject::StreamInfo结构体
    qDebug()<<info.info;

    //设定本模块的输出流信息，在LinkA操作时会自动传递到下游模块。
    infoSelfA=info;

    //手动发送一次流信息，每次InfoSelfA发生变化时，都应该主动发送一次。
    sendInfoA(infoSelfA);
}

void Bypass::onNewPacketA(LinkObject::Packet pkt)
{
    //此处可以获取到裸流数据 pkt.data
    qDebug()<<pkt.pts<<pkt.len;

    //向下游发送数据
    sendPacketA(pkt);
}

void Bypass::onNewInfoV(LinkObject::StreamInfo info)
{
    //同onNewInfoA
    qDebug()<<info.info;
    infoSelfV=info;
    sendInfoV(infoSelfV);
}

void Bypass::onNewPacketV(LinkObject::Packet pkt)
{
    //同onNewPacketV
    qDebug()<<pkt.pts<<pkt.len;
    sendPacketV(pkt);
}
