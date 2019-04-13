#include <QCoreApplication>
#include "Link.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Link::init();

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]="HDMI-A";
    vi->start(dataVi);

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi|vga";
    vo->start(dataVo);

    vi->linkV(vo);

    return a.exec();
}

