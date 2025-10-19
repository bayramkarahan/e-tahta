#include "toolpromter.h"

toolPromter::toolPromter(int w, int h, QWidget *parent)
    : QWidget{parent}
{


    setFixedSize(w,h/3);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    // setWindowFlags(Qt::X11BypassWindowManagerHint);
    setAttribute(Qt::WA_StaticContents);
    // setAttribute(Qt::WA_TranslucentBackground, true);
    // this->setAttribute(Qt::WA_NoSystemBackground, false);
    QGridLayout *mainlayout = new QGridLayout(this);
    mainlayout->setAlignment(Qt::AlignCenter);
    mainlayout->setMargin(0);
    //mainlayout->addWidget(ml);
    setObjectName("promter");
    setStyleSheet("QWidget#promter{"
                  "border: 2px solid rgb(53, 132, 228);"
                  "border-radius: 5px;"
                  "background-color:rgba(250,250,250,255);"
                  "}");


    int en=w/20;
    int boy=h/20;
    //qDebug()<<en<<boy;
    /************************************************************************/
        QPainterPath path;
        path.addRoundedRect(this->rect(), 5,5);//border-radius value:5 refer
        this->setMask(path.toFillPolygon().toPolygon());

        baslik=new QLabel(this);
        baslik->setText("Metin Ekle");
        baslik->setObjectName("baslik");
        baslik->setFixedSize(this->width()-4,boy);
        baslik->move(2,2);
        baslik->setAlignment(Qt::AlignCenter);
        int fnt=10;
        baslik->setStyleSheet("font-size:"+QString::number(fnt)+"px; border: 0.5px solid rgba(230, 220, 230,100);"
                              "border-radius: 5px;"
                                                                "background: rgba(0, 0, 0,30);");
                              //"background: qradialgradient(cx:0.5, cy:0.5, radius: 2.5,"
                              //"fx:0.5, fy:0.5, stop:0 white, stop:1 gray);");
    /************************************************************************/
    text=new QTextEdit(this);
    //text->setText(" Bir millet irfan ordusuna sahip olmadıkça, muharebe meydanlarında ne kadar parlak zaferler elde ederse etsin, o zaferlerin kalıcı sonuçlar vermesi ancak irfan ordusuna bağlıdır. -Mustafa Kemal Atatürk ");
    text->setFixedSize(this->width()-20, boy*5);
    text->move(10,boy+10);


    QPushButton *sayacExitButton= new QPushButton(this);
    sayacExitButton->setFixedSize(en*0.5, boy*1);
    sayacExitButton->setIconSize(QSize(en*1,boy*1));
    sayacExitButton->setFlat(true);
    sayacExitButton->setIcon(QIcon(":icons/exit.svg"));
    sayacExitButton->move(width()-sayacExitButton->width(),0);
    connect(sayacExitButton, &QPushButton::clicked, [=]() {
        emit promterCloseSignal(text->toPlainText());
        this->close();
    });


}

void toolPromter::paintEvent(QPaintEvent *pe)
{
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
