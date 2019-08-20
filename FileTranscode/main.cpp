#include <QCoreApplication>
#include "Link.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *file=Link::create("InputFile");
    LinkObject *dec=Link::create("DecodeV");
    QVariantMap dataDec;
    dataDec["block"]=true;
    dec->start(dataDec);

    LinkObject *encV=Link::create("EncodeV");
    QVariantMap dataEncV;
    dataEncV["codec"]="h265";
    dataEncV["width"]=-1;
    dataEncV["height"]=-1;
    dataEncV["rcmode"]="vbr";
    dataEncV["bitrate"]=1000;
    encV->start(dataEncV);

    LinkObject *mp4=Link::create("Mux");
    QVariantMap dataMP4;
    dataMP4["path"]="test2.mp4";
    mp4->start(dataMP4);
    file->linkV(dec)->linkV(encV)->linkV(mp4);
    file->linkA(mp4);

    QObject::connect(file,&LinkObject::newEvent,[=](QString type,QVariant){
        if(type=="EOF")
        {
            mp4->stop(true);
            exit(0);
        }
    });

    QVariantMap dataFile;
    dataFile["path"]="test.mp4";
    dataFile["sync"]=false;
    file->start(dataFile);

    return a.exec();
}

