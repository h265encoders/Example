#include "Worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
    dev=Link::create("Device");
    dev->start();
    connect(dev,SIGNAL(newEvent(QString,QVariant)),this,SLOT(onEvent(QString,QVariant)));
    dev->invoke("setBootMode","standby");
}

void Worker::onEvent(QString type, QVariant msg)
{
    if(type=="keyPress" && msg.toString()=="power")
    {
        dev->invoke("poweroff");
    }
}

