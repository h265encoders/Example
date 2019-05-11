#include <QCoreApplication>
#include "Link.h"
#include "unistd.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    LinkObject *vi=Link::create("InputVi");
    QVariantMap dataVi;
    dataVi["interface"]="HDMI-A";
    vi->start(dataVi);

    LinkObject *encv=Link::create("EncodeV");
    QVariantMap dataEncV;
    dataEncV["codec"]="jpeg";
    dataEncV["snap"]=true;
    dataEncV["width"]=1280;
    dataEncV["height"]=720;
    encv->start(dataEncV);

    vi->linkV(encv);

    sleep(1);

    encv->invoke("snapSync","test.jpg");


    return a.exec();
}

