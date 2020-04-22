#include <QCoreApplication>
#include "Link.h"
#include "Encoder.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    Encoder enc;
    enc.init();

    return a.exec();
}

