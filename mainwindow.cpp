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
 //palette->setColor(QPalette::Window, QColor(128,128,128));

    pageListwg=new QWidget(this);
    pageListwg->resize(this->width()/2,boy);
   /// pageListwg->setPalette(*palette);
    pageListwg->move(this->width()/4,this->height()-boy-boy);
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

        /*if (msx>event->pos().x()) msx=event->pos().x();
        if(msy>event->pos().y()) msy=event->pos().y();
        if(mex<event->pos().x()) mex=event->pos().x();
        if(mey<event->pos().y()) mey=event->pos().y();
        */
            msx=(msx>event->pos().x()?event->pos().x():msx);
            msy=(msy>event->pos().y()?event->pos().y():msy);
            mex=(mex<event->pos().x()?event->pos().x():mex);
            mey=(mey<event->pos().y()?event->pos().y():mey);

            wpoints<<event->pos();
            drawLineTo(event->pos());
            /*   float factor=10;
        factor=myEraseSize;
      //  qDebug()<<"main mouse  move"<<event->pos()<<myEraseSize;
        bool drm=(wpoints.count() > 1  && (distance(wpoints.last(), event->pos()) < factor));
       if (!drm)
        {
        wpoints<<event->pos();
        drawLineTo(event->pos());
        }
       */
        }
       // update();
   }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
  //  setCursor(QCursor(Qt::BlankCursor));
   // QCursor(Qt::BlankCursor);
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
            wpoints<<event->pos();
            }
    }

    if ((event->buttons() & Qt::LeftButton)&& tasi==true) {
       qDebug()<<"move main press";
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
  //  setCursor(QCursor(Qt::ArrowCursor));
    if(penWriteStatus)
    {
   //qDebug()<<"main mouse release"<<event->pos();
  if(lastPoint==startPoint)
   {
      /// qDebug()<<"bastın çektin";
       wpoints<<QPoint(wpoints.at(0).x()-1,wpoints.at(0).y()-1);
       wpoints<<QPoint(wpoints.at(0).x()+1,wpoints.at(0).y()+1);
       drawingMain=true;
       penWriteStatus=true;
       QPainter painter(&img);

       painter.setPen(QPen(myPenColor, myPenSize, myPenStyle, Qt::RoundCap ,Qt::RoundJoin));
       painter.setRenderHint(QPainter::Antialiasing, true);
       painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
       painter.drawPoint(lastPoint);
       painter.drawPoint(lastPoint.x()-1,lastPoint.y()-1);
       painter.drawPoint(lastPoint.x()+1,lastPoint.y()+1);
       painter.drawPoint(lastPoint.x()-1,lastPoint.y()+1);
       painter.drawPoint(lastPoint.x()+1,lastPoint.y()-1);

       int rad = (myPenSize / 2) + 2;
       update(QRect(lastPoint, lastPoint).normalized()
              .adjusted(-rad, -rad, +rad, +rad));
   }
    if (event->button() == Qt::LeftButton && drawingMain&&penWriteStatus) {
        wpoints<<event->pos();

       /* QPainterPath path;
        path.moveTo(wpoints.at(0));
        for(int i=0;i<wpoints.size()-2;i=i+1)
        {
        path.cubicTo(wpoints.at(i), wpoints.at(i+1), wpoints.at(i+2));
        //path.CurveToElemenwpoints.at(i));
          //  path.lineTo(wpoints.at(i));
        }
        scene->addPath(path,QPen(QColor(255,0,0,255), 5,Qt::SolidLine,Qt::RoundCap ,Qt::RoundJoin));
       // wpoints.clear();
       /*************************************Denenecek*************************************************/
          /*    int n=wpoints.length()-1;
           for(double u = 0.0 ; u <= 1.0 ; u += 0.01)
            {
                //calculate x coordinate
                double xu=0.0;
                for (int i = n; i >= 0; i--) {
                    xu+=wpoints[i].x()*((factorial(n)/(factorial(i)*factorial((n-i))))*pow(u,i)*pow((1-u),(n-i)));
                  }

               //calculate y coordinate
               double yu=0.0;
                for (int i = n; i >= 0; i--) {
                    yu+=wpoints[i].y()*((factorial(n)/(factorial(i)*factorial((n-i))))*pow(u,i)*pow((1-u),(n-i)));
                }
               /// drawLineTo(QPoint((int)xu , (int)yu));
              //  path.lineTo((int)xu , (int)yu);
               // path.cubicTo(QPoint((int)xu , (int)yu), QPoint((int)xu , (int)yu), QPoint((int)xu , (int)yu));
                img.setPixel((int)xu , (int)yu , qRgb(0,255, 0));
             //   setPixmap(QPixmap::fromImage(res));//set image to label
            }
           //pen=QPen(myPenColor, myPenSize, Qt::SolidLine, Qt::RoundCap ,Qt::RoundJoin);
///
         scene->addPath(path,QPen(QColor(255,0,0,255), myPenSize, Qt::SolidLine, Qt::RoundCap ,Qt::RoundJoin));
          //   wpoints.clear();
        /************************************************************************************/
       // https://stackoverflow.com/questions/40764011/how-to-draw-a-smooth-curved-line-that-goes-through-several-points-in-qt
    /*    float factor=10;
        QList<QPointF> points;
           QPointF p;
           for (int i = 0; i < wpoints.size() - 1; i++) {
               p = QPointF(wpoints[i].x(), wpoints[i].y());

               // Except for first and last points, check what the distance between two
               // points is and if its less then min, don't add them to the list.
               if (points.count() > 1 && (i <wpoints.size() - 2) && (distance(points.last(), p) < factor)) {
                   continue;
               }
               points.append(p);
           }

           // Don't proceed if we only have 3 or less points.
           if (points.count() < 3) {
               return;
           }

           QPointF pt1;
           QPointF pt2;
           QPainterPath path1;//= new QPainterPath();
           for (int i = 0; i < points.count() - 1; i++) {
               pt1 = getLineStart(points[i], points[i + 1]);
               if (i == 0) {
                   path1.moveTo(pt1);
               } else {
                   path1.quadTo(points[i], pt1);
               }
               pt2 = getLineEnd(points[i], points[i + 1]);
               path1.lineTo(pt2);
           }

          // delete mPath;
          // path.clear();
          // path = path1;
        ///   prepareGeometryChange();
           pen=QPen(myPenColor, myPenSize, Qt::SolidLine, Qt::RoundCap ,Qt::RoundJoin);

     //    scene->addPath(path1,QPen(QColor(0,255,0,255), myPenSize, Qt::SolidLine, Qt::RoundCap ,Qt::RoundJoin));
         /// path1.clear();

       /*************************************************************************************/
       // lastPoint=event->pos();
        drawLineTo(event->pos());
        wpoints.clear();
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
        startPoint=QPointF(msx,msy);
      //  qDebug()<<"sayfa sayısı:"<<sceneSayfaNumber;
      //      startPoint=QPointF(msx,msy);
    /*    if(sceneSayfaNumber>0)
            startPoint=QPointF(msx,msy);
       else
    */

        /*qDebug()<<"resim oluşturulsu"<<myPenSize;
         QPixmap pix1(qFabs(msx-mex), qFabs(msy-mey));
         pix1.fill(Qt::transparent);
         QPainter painter(&pix1);
         painter.setRenderHint(QPainter::Antialiasing, true);
         painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.setWindow(QRect(msx, msy,qFabs(msx-mex), qFabs(msy-mey)));
         painter.setPen(pen);
         painter.strokePath(path1,pen);
*/
         VERectangle*  itemToRectDraw = new VERectangle(scene);
        itemToRectDraw->sekilTur(DiagramItem::DiagramType::Kalem);
        //itemToRectDraw->sekilTur(DiagramItem::DiagramType::Resim);
        //itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
        //itemToRectDraw->setBrush(mySekilZeminColor);
        ///QPixmap temp=QPixmap::fromImage(copyImage(img,QRect(QPoint(msx,msy),QPoint(mex,mey))));
        QRect selection;
        selection.setRect(msx,msy,mex-msx,mey-msy);
        QPixmap temp=QPixmap::fromImage(img.copy(selection));


        itemToRectDraw->setPos(startPoint);
        itemToRectDraw->setImage(temp);
        //itemToRectDraw->setImage(pix1);
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
    QPainter painter(&img);

    painter.setPen(QPen(myPenColor, myPenSize, myPenStyle, Qt::RoundCap ,Qt::RoundJoin));
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHints(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::Qt4CompatiblePainting);
    painter.setRenderHint(QPainter::NonCosmeticDefaultPen);


   QPointF pt1;
    QPointF pt2;
    QPainterPath path1;//= new QPainterPath();
    //painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
   /* for (int i = 0; i < wpoints.count() - 1; i++) {
        pt1 = getLineStart(wpoints[i], wpoints[i + 1]);
        if (i == 0) {
            path1.moveTo(pt1);
        } else {
            path1.quadTo(wpoints[i-1], pt1);
        }
        pt2 = getLineEnd(wpoints[i], wpoints[i + 1]);
        path1.lineTo(pt2);
    }
    painter.drawPath(path1);
*/
   painter.drawLine(lastPoint, endPoint);

    int rad = (myPenSize / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
           .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
  /*  pen=QPen(QColor(0,0,255,255), myPenSize, Qt::SolidLine, Qt::RoundCap ,Qt::RoundJoin);
       rad = (myPenSize / 2)+2;

    QPainter painter(&img);
    painter.setPen(pen);
    // painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
   //  painter.setRenderHint(QPainter::HighQualityAntialiasing);
   // painter.setRenderHint(QPainter::Qt4CompatiblePainting);
    // painter.setRenderHint(QPainter::NonCosmeticDefaultPen);
  //  painter.setRenderHint(QPainter::SmoothPixmapTransform);
qDebug()<<"deneme"<<endPoint;

///painter.drawLine(lastPoint, endPoint);
/************************************************************************************/
/*
    QPainterPath path;
   /// path.moveTo(wpoints.at(0));
 QPointF pt1;
 QPointF pt2;
 QPainterPath path1;//= new QPainterPath();
 painter.setRenderHint(QPainter::Antialiasing, true);
 painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
 for (int i = 0; i < wpoints.count() - 1; i++) {
     pt1 = getLineStart(wpoints[i], wpoints[i + 1]);
     if (i == 0) {
         path1.moveTo(pt1);
     } else {
         path1.quadTo(wpoints[i], pt1);
     }
     pt2 = getLineEnd(wpoints[i], wpoints[i + 1]);
     path1.lineTo(pt2);
 }
 painter.drawPath(path1);
 /**************************************************************************************/
 /*int rad = (myPenSize / 2) + 2;
 update(QRect(lastPoint, endPoint).normalized()
        .adjusted(-rad, -rad, +rad, +rad));
 lastPoint = endPoint;*/

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
