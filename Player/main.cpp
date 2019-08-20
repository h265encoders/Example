#include <QCoreApplication>
#include "Link.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);

    LinkObject *file=Link::create("InputFile");
    QVariantMap dataFile;
    dataFile["path"]="test.mp4";
    file->start(dataFile);

    LinkObject *dec=Link::create("DecodeV");
    dec->start();

    file->linkV(dec)->linkV(vo);

    QObject::connect(file,&LinkObject::newEvent,[=](QString type,QVariant){
        if(type=="EOF")
        {
            exit(0);
        }
    });

    bool pause=false;
    while(true)
    {
        int key=getchar();
        if(key==32)//space
        {
            pause=!pause;
            file->invoke("pause",pause);
        }
        else if(key==68)//left
        {
            int cur=file->invoke("getPosition").toInt();
            qDebug()<<cur;
            cur-=5000;
            file->invoke("seek",cur);
        }
        else if(key==67)//right
        {
            int cur=file->invoke("getPosition").toInt();
            cur+=5000;
            file->invoke("seek",cur);
        }
        else if(key==97)//a
        {
            file->invoke("seek",5500);
        }
    }

    return a.exec();
}

