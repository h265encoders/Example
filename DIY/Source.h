#ifndef SOURCE_H
#define SOURCE_H

#include "Link.h"
#include <QUdpSocket>

class Source : public LinkObject
{
    Q_OBJECT
public:
    explicit Source(QObject *parent = 0);
private:
    QUdpSocket dataSocket;
    QUdpSocket infoSocket;
    struct PktHeader{
        qint64 pts;
        qint64 dts;
        bool isIframe;
    };
signals:

public slots:
    void onStart();
    void onReadData();
    void onReadInfo();
};

#endif // SOURCE_H
