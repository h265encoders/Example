#include <QCoreApplication>
#include "Link.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *gpio=Link::create("GPIO");
    gpio->start();

    if(gpio->invoke("registEvent","GPIO15_0").toBool())
    {
        QObject::connect(gpio,&LinkObject::newEvent,[=](QString type,QVariant info){
            QString name=info.toString();
            qDebug()<<name<<type;
        });
    }

    QVariantList args;
    args<<"GPIO20_1"<<false;
    gpio->invoke("setGPIO",args);

    gpio->invoke("getGPIO","GPIO20_2").toBool();

    return a.exec();
}

