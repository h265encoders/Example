#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>
#include "Link.h"
#include <jcon/json_rpc_tcp_server.h>

class Encoder : public QObject
{
    Q_OBJECT
public:
    explicit Encoder(QObject *parent = 0);
    void init();
private:
    jcon::JsonRpcTcpServer *rpcServer;
    LinkObject *vi,*ai;
    LinkObject *encV,*encA;
    LinkObject *rtmp,*rtsp,*rtspServer;
signals:

public slots:
    QVariantMap getInputState();
    bool setConfig(QVariantMap data);
};

#endif // ENCODER_H
