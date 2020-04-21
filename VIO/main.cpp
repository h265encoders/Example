#include <QCoreApplication>
#include "Link.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Link::init();

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;

#ifdef HI3531D
    dataVi["interface"]="HDMI-A";
#elif defined HI3521D
    dataVi["interface"]="HDMI";
#elif defined HI3519A
    dataVi["interface"]="HDMI-L";
#endif
    vi->start(dataVi);

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);

    vi->linkV(vo);

    return a.exec();
}
