#include <QCoreApplication>
#include "Link.h"
#include "../VIO/interface.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Link::init();

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]=INTERFACE_VIDEO;
    vi->start(dataVi);

    LinkObject *crop=Link::create("Crop");
    QVariantMap dataCrop;
    dataCrop["x"]=0.2;
    dataCrop["y"]=0.2;
    dataCrop["width"]=0.5;
    dataCrop["height"]=0.5;
    crop->start(dataCrop);

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);

    vi->linkV(crop)->linkV(vo);

    return a.exec();
}

