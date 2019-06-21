#include <QApplication>
#include "Link.h"
#include <QWebView>
#include <QWebFrame>
#include <unistd.h>

int main(int argc, char *argv[])
{
    Link::init();

    LinkObject *vo=Link::create("OutputVo");
    QVariantMap dataVo;
    dataVo["type"]="hdmi";
    vo->start(dataVo);
    sleep(3);
    QApplication a(argc, argv);

    LinkObject *ai_1=Link::create("InputAi");
    QVariantMap dataAi_1;
    dataAi_1["interface"]="HDMI-A";
    ai_1->start(dataAi_1);

    LinkObject *ai_2=Link::create("InputAi");
    QVariantMap dataAi_2;
    dataAi_2["interface"]="HDMI-B";
    ai_2->start(dataAi_2);

    LinkObject *vi_1=Link::create("InputVi","V1");
    QVariantMap dataVi_1;
    dataVi_1["interface"]="HDMI-A";
    vi_1->start(dataVi_1);

    LinkObject *vi_2=Link::create("InputVi","V2");
    QVariantMap dataVi_2;
    dataVi_2["interface"]="HDMI-B";
    vi_2->start(dataVi_2);

    LinkObject *mixA=Link::create("MixA");
    QVariantMap dataMixA;
    dataMixA["main"]=ai_1->name();
    mixA->start(dataMixA);

    LinkObject *mixV=Link::create("MixV");
    QVariantMap dataMixV;
    QVariantList srcs;
    QVariantList layouts;
    QVariantMap lay;
    lay["x"]=0;
    lay["y"]=0;
    lay["w"]=0.6;
    lay["h"]=0.6;
    lay["a"]=1;
    lay["index"]=0;
    layouts<<lay;
    lay["x"]=0.4;
    lay["y"]=0.4;
    lay["index"]=1;
    layouts<<lay;
    dataMixV["layout"]=layouts;
    srcs<<vi_1->name()<<vi_2->name();
    dataMixV["src"]=srcs;
    mixV->start(dataMixV);

    LinkObject *ao=Link::create("OutputAo");
    QVariantMap dataAo;
    dataAo["interface"]="HDMI-OUT";
    ao->start(dataAo);

    ai_1->linkA(mixA);
    ai_2->linkA(mixA)->linkA(ao);

    vi_1->linkV(mixV);
    vi_2->linkV(mixV)->linkV(vo);


    QWebView web;
    QPalette pal = web.page()->palette();
    pal.setBrush(QPalette::Base, Qt::transparent);
    web.setPalette(pal);
    web.setAttribute(Qt::WA_TranslucentBackground, true);
    web.resize(1920,1080);
    web.show();
    web.settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    web.load(QUrl("file:///root/demo/web.html"));

    web.page()->mainFrame()->addToJavaScriptWindowObject("mix", mixV);

    return a.exec();
}

