#include <QCoreApplication>
#include "Link.h"
#include "Worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link::init();

    Worker w;

    return a.exec();
}

