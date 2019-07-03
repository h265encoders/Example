#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "Link.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    LinkObject *dev;
signals:

public slots:
    void onEvent(QString type,QVariant msg);
};

#endif // WORKER_H
