#ifndef BYPASS_H
#define BYPASS_H

#include "Link.h"

class Bypass : public LinkObject
{
    Q_OBJECT
public:
    explicit Bypass(QObject *parent = 0);

signals:

public slots:
    void onNewPacketA(Packet pkt);
    void onNewPacketV(Packet pkt);
    void onNewInfoA(StreamInfo info);
    void onNewInfoV(StreamInfo info);

};

#endif // BYPASS_H
