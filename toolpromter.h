#ifndef TOOLPROMTER_H
#define TOOLPROMTER_H
#include <QWidget>
#include<QGridLayout>
#include<QPushButton>
#include<QLabel>
#include<QProgressBar>
#include<QTimer>
#include<QTime>
#include<QDebug>
#include<QSlider>
#include<QTextEdit>
#include<QEventLoop>
#include<QColorDialog>
#include<QFontDialog>
#include <QApplication>
#include<QPoint>
#include<QMouseEvent>
#include<QPainterPath>
#include<QPainter>
#include<QStyleOption>

class toolPromter : public QWidget
{
    Q_OBJECT
public:
    explicit toolPromter(int w, int h, QWidget *parent = nullptr);
    QSlider *sure;
protected slots:

    void paintEvent(QPaintEvent *pe) override;

protected:
    bool mouseClickState;
    QPoint oldPos;
    QLabel *baslik;
    void mousePressEvent(QMouseEvent *event)Q_DECL_OVERRIDE
    {
        if (QLabel *w =(QLabel*) qApp->widgetAt(QCursor::pos())) {
            if(w->objectName()=="baslik")
            {
                mouseClickState=true;
                oldPos = event->globalPos();
                //qDebug()<<"press"<<mouseClickState;
            }
        }
    }
    void mouseMoveEvent(QMouseEvent *event)Q_DECL_OVERRIDE
    {
        // qDebug()<<"move"<<mouseClickState;
        if(mouseClickState)
        {
            /// qDebug()<<"başlıktan tutup sürükleniyor";
            const QPoint delta = event->globalPos() - oldPos;
            move(x()+delta.x(), y()+delta.y());
            oldPos = event->globalPos();
        }
    }
    void mouseReleaseEvent(QMouseEvent *event)Q_DECL_OVERRIDE
    {

        mouseClickState=false;
        //  qDebug()<<"release"<<mouseClickState;
    }

signals:
    void promterCloseSignal(QString text);

private:
    bool startStatus;
    QLabel *suresayacLabel;
    int suresayac=180;
    QProgressBar *bar;
   // QLabel  *sayac;
     QLabel  *timerTextLabel;
    qint64 saniye;
    QEventLoop loop;
    QTimer timer;
 //   QTimer timerText;
    QTextEdit *text;
    QString actual_text_;
    int pos_;
     QTimer  *timerText;
};


#endif // TOOLPROMTER_H
