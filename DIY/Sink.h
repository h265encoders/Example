#ifndef SINK_H
#define SINK_H

#include "Link.h"
#include <QUdpSocket>

class Sink : public LinkObject
{
    Q_OBJECT
public:
    explicit Sink(QObject *parent = 0);
private:
    QHostAddress ip;
    int dataPort;
    int infoPort;
    QUdpSocket socket;
    struct PktHeader{
        qint64 pts;
        qint64 dts;
        bool isIframe;
    };
signals:

public slots:
    void onStart();
    void onStop();
    void onSetData(QVariantMap newData);
    void onNewInfoV(StreamInfo info);
    void onNewPacketV(Packet pkt);
};

#endif // SINK_H
