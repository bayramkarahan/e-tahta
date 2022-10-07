/*****************************************************************************
 *   Copyright (C) 2020 by Bayram KARAHAN                                    *
 *   <bayramk@gmail.com>                                                     *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          *
 *****************************************************************************/

//#include "mainwindow.h"
#include <QPalette>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QPixmap>
#include <QFileDialog>
#include <QtWidgets>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include <QGraphicsPolygonItem>
#include<QMessageBox>
#include<QFile>
#include<function.h>
#include<buttonclick.h>
#include<popmenu.h>
#include<kalemlayout.h>
//#include<popler-qt5-.h>


class QWidget;
class QPixmap;

MainWindow::MainWindow()
{

    QStringList args1;
    QProcess p1;
    args1 << "-e" << "eta-disable-gestures@pardus.org.tr";
    p1.execute("gnome-shell-extension-tool", args1);

    QStringList args2;
    QProcess p2;
    args2 << "set" << "org.gnome.mutter" << "overlay-key" << "''";
    p2.execute("gsettings", args2);


    /*****************Scene******************************/
    //qDebug()<<"inital scene property";
    scene = new Scene();
    _scene=scene;
    scene->setParent(this);
    scene->setSekilZeminColor(QColor(0,0,0,0));
    //sceneSayfa.append(scene);
    sceneSayfaNumber=0;
    sceneSayfaActiveNumber=0;
    sceneSayfa.append(_scene);
       /*****************view ************************/
    //qDebug()<<"inital view property";
    view = new QGraphicsView(scene);
   // view->setRenderHints(QPainter::Antialiasing);
    //QGraphicsView view(&scene);
     view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    view->setAttribute(Qt::WA_TranslucentBackground);
    view->viewport()->setAutoFillBackground(false);
    QSize screenSize = qApp->screens()[0]->size();

    view->setSceneRect(0,0,screenSize.width(),screenSize.height());
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(view);
/********************************************/
    screenClickDrm=false;
    initPen();
    createButton();
    //this->setMinimumSize(0,0);

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::X11BypassWindowManagerHint);

    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowIcon(QIcon(":icons/screenpen.png"));
      /*****************************************/

    saat = new QTimer(this);
    connect(saat, SIGNAL(timeout()), this, SLOT(saatslot()));

    timerCopy = new QTimer(this);
    connect(timerCopy, SIGNAL(timeout()), this, SLOT(timerCopySlot()));


    timerGizle = new QTimer(this);
    connect(timerGizle, SIGNAL(timeout()), this, SLOT(timerGizleSlot()));
           // timerGizle->start(5000);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(zamanlama()));
    timer->start(1000);


//qDebug() <<"zamanlama";
    setUnifiedTitleAndToolBarOnMac(true);
/*********************************/
    buyukKutu = new QWidget(this);
    buyukKutu->setObjectName("buyukKutu");
    buyukKutu->setStyleSheet("QWidget#buyukKutu{"
                          "border: 1px solid rgb(62, 140, 183);"
                          "border-radius: 5px;"
                          "background-color:rgb(240,240,240,250);"
                          "}");

//setStyleSheet("QLabel{color: rgb(62, 140, 183);}");

    palette = new QPalette();
    palette->setColor(QPalette::Background, QColor(240,240,240,250));
    buyukKutu->setPalette(*palette);
    buyukKutu->setAutoFillBackground(true);
    setWindowTitle("E-Tahta 1.8.1");
/***********************************/
    kokLayot=new QVBoxLayout();
    kokLayot->setContentsMargins(0,0,0,0);
    buyukKutu->setLayout(kokLayot);
    kalemLayout();


    buyukKutu->setGeometry(QRect(kutuLeft,kutuTop,kutuWidth,kutuHeight));
    scene->setMode(Scene::Mode::NoMode, DiagramItem::DiagramType::NoType);
    currentScreenMode=Scene::Mode::NoMode;

    /*********************scene screen capture******/
 palette = new QPalette();
 //palette->setColor(QPalette::Window, QColor(128,128,128,50));

    pageListwg=new QWidget(this);
    pageListwg->resize(this->width()/2,boy);
   /// pageListwg->setPalette(*palette);
    pageListwg->move(this->width()/4,this->height()-boy);
    //pageListwg->setAutoFillBackground(true);
    pageListwg->setObjectName("pageListwg");

    pageListwg->setStyleSheet("QWidget#pageListwg{"
                          "border: 0.5px solid rgb(62, 140, 220,20);"
                          "border-radius: 5px;"
                          "background-color:rgb(255,255,255,0);"
                          "}");

    screenlayout = new QHBoxLayout(pageListwg);
    screenlayout->setContentsMargins(0, 0, 0, 0);



 ekleSayfaButtonClick(-1,false,-1);///İlk Sayfa ekleniyor Açıldığında göünen sayfa
 wsol=new QWidget(this);
 wsol->resize(boy*1.1,screenSize.height());
// screenSize.width(),screenSize.height()
 wsol->move(0,0);
 wsol->setStyleSheet("QWidget {"
                     "background-color:rgb(240,240,240);"
                  //   "border: 0.5px solid rgb(62, 140, 220,20);"
                     "}");
 wsol->setStyleSheet("background:rgb(56,56,56);");
 wsol->lower();
 QFont f( "Helvetica", 10, QFont::Bold);
 QLabel *leftTextLabel = new QLabel(wsol);
 leftTextLabel->setText("\n\n\n\n\n\nE\n-\nT\nA\nH\nT\nA");
 leftTextLabel->setAlignment(Qt::AlignCenter);
 leftTextLabel->setStyleSheet("color:white;font-size:35px;");
 leftTextLabel->setFont(f);
 leftTextLabel->move(boy/5,0);
///qDebug()<<"wsol gösteri durumum:"<<wsolVisible;
 wsol->hide();

 iconButton();
 buttonColorClear();
 kalemButtonClick();///önemli
 timerGizleSlot();///önemli
// ileriGeriSayfa();
 ekranButtonClick();///önemli

 drawingMain = false;
 img.fill(qRgba(0, 0, 0, 0));


}
void MainWindow::resizeSlot()
{
    if(screenDesktop)
    {

        QSize screenSize = qApp->screens()[0]->size();

        setGeometry(0,
                    0,
                    screenSize.width(),
                    screenSize.height());
  //  qDebug()<<"degişti";
       update();
    }


    if (width() > img.width() || height() > img.height()) {
        int newWidth = qMax(width() + 128, img.width());
        int newHeight = qMax(height() + 128, img.height());
        resizeImage(&img, QSize(newWidth, newHeight));
     //   resizeImage(&imageAlt, QSize(newWidth, newHeight));
             update();
      }
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    resizeSlot();
  ///  currentGeometry = this->geometry();
    QWidget::resizeEvent(event);
}

void MainWindow::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_ARGB32);
    newImage.fill(qRgba(0, 0,0 , 0));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;

  }

void MainWindow::moveEvent(QMoveEvent *event)
{
    if(screenDesktop)
    {
        QSize screenSize = qApp->screens()[0]->size();


        setGeometry(0,
                    0,
                    screenSize.width(),
                    screenSize.height());
        update();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(penWriteStatus)
    {
        if ((event->buttons() & Qt::LeftButton) && drawingMain==true) {

      //  qDebug()<<"main mouse  move";

        drawLineTo(event->pos());
        if (msx>event->pos().x()) msx=event->pos().x();
        if(msy>event->pos().y()) msy=event->pos().y();
        if(mex<event->pos().x()) mex=event->pos().x();
        if(mey<event->pos().y()) mey=event->pos().y();

        }
        update();
   }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
   // qDebug()<<"main press";
    if(penWriteStatus)
        {
            if ((event->buttons() & Qt::LeftButton)) {

            lastPoint = event->pos();
            startPoint=event->pos();
            drawingMain = true;
            msx=event->pos().x();
            msy=event->pos().y();
            mex=event->pos().x();
            mey=event->pos().y();

            }
    }

    if ((event->buttons() & Qt::LeftButton)&& tasi==true) {
        //qDebug()<<"move main press";
        buyukKutu->setGeometry(QRect(event->pos().x(),kutuTop,kutuWidth,kutuHeight));
        kutuLeft=event->pos().x();
       /// kutuTop=50;
        tasi=false;
        kalemButtonClick();
    }
    if(screenClickDrm)
    {
      ///  qDebug()<<"main press sunu";
        ekranButtonClick();
        system("sleep 0.2&&xdotool click 1");

        ekranButtonClick();
       /// screenClickButtonClick();


}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(penWriteStatus)
    {
  //  qDebug()<<"main mouse release";
    if (event->button() == Qt::LeftButton && drawingMain&&penWriteStatus) {

        drawLineTo(event->pos());

        lastPoint=event->pos();
        drawingMain = false;

       if (msx>event->pos().x()) msx=event->pos().x();
        if(msy>event->pos().y()) msy=event->pos().y();
        if(mex<event->pos().x()) mex=event->pos().x();
        if(mey<event->pos().y()) mey=event->pos().y();
         if(mex<msx){int xtmp=msx;msx=mex;mex=xtmp;}
        if(mey<msy){int ytmp=msy;msy=mey;mey=ytmp;}

        msx=msx-(myPenSize/2)-2;
        msy=msy-(myPenSize/2)-2;
        mex=mex+(myPenSize/2)+2;
        mey=mey+(myPenSize/2)+2;

      //  qDebug()<<"sayfa sayısı:"<<sceneSayfaNumber;

        if(sceneSayfaNumber>0)
            startPoint=QPointF(msx,msy);
        else

            startPoint=QPointF(msx-1,msy-1);


        VERectangle*  itemToRectDraw = new VERectangle(scene);
        itemToRectDraw->sekilTur(DiagramItem::DiagramType::Kalem);
        //itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
        //itemToRectDraw->setBrush(mySekilZeminColor);
        ///QPixmap temp=QPixmap::fromImage(copyImage(img,QRect(QPoint(msx,msy),QPoint(mex,mey))));
        QRect selection;
        selection.setRect(msx,msy,mex-msx,mey-msy);
        QPixmap temp=QPixmap::fromImage(img.copy(selection));


        itemToRectDraw->setPos(startPoint);
        itemToRectDraw->setImage(temp);
        scene->addItem(itemToRectDraw);
        //qDebug()<<"eklendi**********************";
        /***************************************/

        scene->graphicsList.append(itemToRectDraw);
        scene->graphicsListTemp.append(itemToRectDraw);
        scene->historyBack.append(itemToRectDraw);
        scene->historyBackAction.append("added");
        depo::historyBackCount=scene->historyBack.count();
        depo::historyNextCount=scene->historyNext.count();


        /*******************************************/
        itemToRectDraw->setRect(0,0,mex - msx,mey - msy);

        itemToRectDraw->fareState(false);


        itemToRectDraw = 0;
 clearImage();
       // qDebug()<<"releaseMain";
        /*********************************************/
          QPixmap pixMap = view->grab(view->sceneRect().toRect());
          /**********************************************/
       // this->repaint();
        QPalette palet;
        palet.setBrush(QPalette::Background,pixMap);
        this->setPalette(palet);
        //**********************************************
        //QPixmap pixMap = view->grab(view->sceneRect().toRect());
        pageList[sceneSayfaActiveNumber]->setIcon(QIcon(pixMap));////önemli

        // view->show();
    }
    }

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
        QRect dirtyRect = event->rect();
        painter.drawImage(dirtyRect, img, dirtyRect);

}

void MainWindow::clearImage()
{ ///if(switched)
    //   {
   img.fill(qRgba(0,0, 0, 0));
   /*if(clearMode) {
       toggleClearMode();
       clearButton->setChecked(false);
   }*/
   update();
   // }

}

QImage MainWindow::copyImage(const QImage & input, const QRect & path){
    if(!input.isNull() && !path.isEmpty()){
        QRect r = path.intersected(input.rect());
        QImage tmp(input.size(), QImage::Format_ARGB32);
        tmp.fill(Qt::transparent);
        QPainter painter(&tmp);
        painter.setClipRect(path);
        painter.drawImage(QPoint{}, input, input.rect());
        painter.end();
        return tmp.copy(r);
    }
    return QImage();
}

void MainWindow::drawLineTo(const QPoint &endPoint)
{
    pen=QPen(myPenColor, myPenSize, Qt::SolidLine, Qt::RoundCap ,Qt::RoundJoin);
       rad = (myPenSize / 2)+2;

    QPainter painter(&img);
    painter.setPen(pen);
     painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
   //  painter.setRenderHint(QPainter::HighQualityAntialiasing);
   // painter.setRenderHint(QPainter::Qt4CompatiblePainting);
    // painter.setRenderHint(QPainter::NonCosmeticDefaultPen);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);


 painter.drawLine(lastPoint, endPoint);

 int rad = (myPenSize / 2) + 2;
 update(QRect(lastPoint, endPoint).normalized()
        .adjusted(-rad, -rad, +rad, +rad));
 lastPoint = endPoint;

}


MainWindow::~MainWindow()
{
    QStringList args3;
    QProcess p3;
    args3 << "-d" << "eta-disable-gestures@pardus.org.tr";
    p3.execute("gnome-shell-extension-tool", args3);

    QStringList args4;
    QProcess p4;
    args4 << "set" << "org.gnome.mutter" << "overlay-key" << "'SUPER_L'";
    p4.execute("gsettings", args4);
}
