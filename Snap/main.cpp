#include <QCoreApplication>
#include "Link.h"
#include "../VIO/interface.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]=INTERFACE_VIDEO;
    vi->start(dataVi);

    LinkObject *encv=Link::create("EncodeV");
    QVariantMap dataEncV;
    dataEncV["codec"]="jpeg";
    dataEncV["snap"]=true;
    dataEncV["width"]=1280;
    dataEncV["height"]=720;
    encv->start(dataEncV);

    vi->linkV(encv);

    sleep(2);

    encv->invoke("snapSync","test.jpg");


    return a.exec();
}

