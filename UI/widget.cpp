#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPalette pal = palette();
    pal.setBrush(QPalette::Base, Qt::transparent);
    setPalette(pal);
    setAttribute(Qt::WA_TranslucentBackground, true);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    ai_1=Link::create("InputAi");
    QVariantMap dataAi_1;
    dataAi_1["interface"]="HDMI-A";
    ai_1->start(dataAi_1);

    ai_2=Link::create("InputAi");
    QVariantMap dataAi_2;
    dataAi_2["interface"]="HDMI-B";
    ai_2->start(dataAi_2);

    vi_1=Link::create("InputVi");
    QVariantMap dataVi_1;
    dataVi_1["interface"]="HDMI-A";
    vi_1->start(dataVi_1);

    vi_2=Link::create("InputVi");
    QVariantMap dataVi_2;
    dataVi_2["interface"]="HDMI-B";
    vi_2->start(dataVi_2);

    mixA=Link::create("MixA");
    QVariantMap dataMixA;
    dataMixA["main"]=ai_1->name();
    mixA->start(dataMixA);

    mixV=Link::create("MixV");
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

    ao=Link::create("OutputAo");
    QVariantMap dataAo;
    dataAo["interface"]="HDMI-OUT";
    ao->start(dataAo);

    ai_1->linkA(mixA);
    ai_2->linkA(mixA)->linkA(ao);

    vi_1->linkV(mixV);
    vi_2->linkV(mixV)->linkV(vo);

}

void Widget::on_pushButton_clicked()
{
    QVariantList list;
    list<<vi_1->name()<<vi_2->name();
    mixV->invoke("swap",list);
}
