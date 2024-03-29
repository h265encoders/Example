#include <QCoreApplication>
#include "Link.h"
#include "interface.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Link::init();

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]=INTERFACE_VIDEO;
    vi->start(dataVi);

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);

    vi->linkV(vo);

    return a.exec();
}
