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

    LinkObject *overlay=Link::create("Overlay");
    QVariantMap dataOver;
    QVariantList lays;
    QVariantMap lay;
    lay["type"]="text";
    lay["enable"]=true;
    lay["font"]="/link/res/font.ttf";
    lay["content"]="测试ABC";
    lay["x"]=0.1;
    lay["y"]=0.1;
    lay["scale"]=2;
    lay["color"]="#669900";
    lay["alpha"]=1;
    lays<<lay;
    lay.clear();
    lay["type"]="pic";
    lay["enable"]=true;
    lay["content"]="/link/res/logo.png";
    lay["x"]=0.1;
    lay["y"]=0.3;
    lay["scale"]=1;
    lay["alpha"]=0.7;
    lays<<lay;
    lay.clear();
    lay["type"]="time";
    lay["enable"]=true;
    lay["font"]="/link/res/font.ttf";
    lay["content"]="yyyy年MM月dd日 hh:mm:ss";
    lay["x"]=0.1;
    lay["y"]=0.5;
    lay["scale"]=2;
    lay["color"]="#ffffff";
    lay["alpha"]=1;
    lays<<lay;
    dataOver["lays"]=lays;
    overlay->start(dataOver);

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);

    vi->linkV(overlay)->linkV(vo);

    return a.exec();
}

