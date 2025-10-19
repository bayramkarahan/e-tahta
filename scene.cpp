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

#include "scene.h"
#include <QApplication>
#include <QMessageBox>
#include <QPoint>
#include <QDesktopWidget>
#include <QDebug>
#include<QFileDialog>
#include<QtPrintSupport/qprinter.h>
#include<QtPrintSupport/qprintdialog.h>
#include<QPainter>
#include<QGraphicsItem>
#include<QGraphicsView>
#include<QtMath>
#include<QGraphicsPixmapItem>
#include<gridlines.h>
#include<filecrud.h>
#include <QCursor>
#include <QTransform>
#include<QScreen>
#include<QHoverEvent>
#include<depo.h>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Scene::Scene(QObject* parent): QGraphicsScene(parent)
{
    sceneMode = NoMode;
    sceneModeTrue=NoModeTrue;
    itemToLineDraw = 0;
    itemToRectDraw = 0;
    tempCopyModeItemToRectDraw=0;

    //sampleLine=0;
    dragMove=false;
    drawing=false;
    myMousePress=true;
    //currentItem=nullptr;
    myPopMenuStatus=false;
   // timerPergel = new QTimer(this);
  //  connect(timerPergel, SIGNAL(timeout()), this, SLOT(donSlot()));
tv=0;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //qDebug()<<"scene press"<<depo::as;
   //int MainWindow::as{15};
   /// qDebug()<<"mousePress myMousePress:"<<myMousePress;
    //qDebug()<<"10";
    if(myMousePress){
    switch(sceneMode)
     {
     case DrawRectangle:{
      //  qDebug()<<"1";
         sceneModeTrue=DrawRectangleTrue;
         origPoint = event->scenePos();
         drawing=true;

         break;
     }
     case DrawPen:{sceneModeTrue=DrawPenTrue; sceneMoveState=false;
          drawing=true;dragMove=false;
          QGraphicsView::DragMode vMode =QGraphicsView::NoDrag;
          makeItemsControllable(false);
        //  vMode = QGraphicsView::RubberBandDrag;
         QGraphicsView* mView = views().at(0);
          if(mView)
           mView->setDragMode(vMode);
         origPoint = event->scenePos();
         points.clear();
        /*
         QGraphicsLineItem*  itemToPenDraw = new QGraphicsLineItem();
         this->addItem(itemToPenDraw);
         itemToPenDraw->setPen(QPen(myPenColor,myPenSize, myPenStyle, Qt::RoundCap ,Qt::RoundJoin));
         itemToPenDraw->setLine(origPoint.x(),origPoint.y() ,origPoint.x()+1,origPoint.y()+1);
         graphicsList.append(itemToPenDraw);
         graphicsListTemp.append(itemToPenDraw);
         graphicsListpoints.append(itemToPenDraw);
        */
         endPos=event->scenePos();
         points<<origPoint;
         //qDebug()<<"Fare Başlama Pozisyonu: "<<event->scenePos();
         startPos=event->scenePos();
         endPos=startPos;
         sx=startPos.x();
         sy=startPos.y();
         ex=startPos.x();
         ey=startPos.y();
       //  qDebug()<<"scene click";
         break;}
     case DrawPenFosfor:{
         sceneModeTrue=DrawPenFosforTrue; origPoint = event->scenePos();
         drawing=true;
         points.clear();

         points<<origPoint;
         break;
     }
     case CopyMode:{sceneModeTrue=CopyModeTrue;
         // qDebug()<<"crop başladı";
          origPoint = event->scenePos();
           QGraphicsView::DragMode vMode =QGraphicsView::NoDrag;
          vMode = QGraphicsView::RubberBandDrag;


          QGraphicsView* mView = views().at(0);
          if(mView)
           mView->setDragMode(vMode);
          break;}
     case EraseMode:{sceneModeTrue=EraseModeTrue;
         //qDebug()<<"silme tıklandı";
        drawing=true;
        makeItemsControllable(true);
       int boyut;
        boyut=myEraseSize*3;
        QRect rect(QPoint(event->scenePos().toPoint().x()-boyut,event->scenePos().toPoint().y()-boyut),QPoint(event->scenePos().toPoint().x()+boyut,event->scenePos().toPoint().y()+boyut) );
        QPainterPath pp;
        pp.addRect(rect);
        setSelectionArea(pp);
        // clearSelection();
        removeOddItem();
        update();
        break;}
     case SelectObject:{sceneModeTrue=SelectObjectTrue;
         // qDebug() <<"nesleler seçilmeye çalışılıyor";
          QTransform deviceTransform;
          QGraphicsItem *selectItem = itemAt(event->scenePos().x(),event->scenePos().y(), deviceTransform);
                   foreach(QGraphicsItem* item, items()){
                     VERectangle * selection = dynamic_cast<VERectangle *>(item);
                        if(selection!=nullptr&&selectItem==selection){
                            selection->fareState(true);
                            if(selection->rotateState){
//qDebug()<<"12";
                                tv=selection;
                                sceneModeTrue=DrawPenTrue;
                                sceneMoveState=false;
                                drawing=true;dragMove=false;
                                 origPoint =tv->scenePos();

                            }

                           // qDebug() <<"seçme modunda rentangle seçildi";
                        }
                        if(selection!=nullptr&&selectItem!=selection){
                             selection->fareState(false);
                           // qDebug() <<"seçme modunda rentangle seçilmedi";
                        }
                   }
         break;}

    }

    QGraphicsScene::mousePressEvent(event);
    }

}

void Scene::donSlot()
{
    qDebug()<<"Dön Slot";
    QSize screenSize = qApp->screens()[0]->size();

    if(!itemToRectDraw){
      //  qDebug()<<"3";

        itemToRectDraw = new VERectangle(this);
        itemToRectDraw->sekilTur(mySekilType);
        itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
        itemToRectDraw->setBrush(mySekilZeminColor);
        //myImage.setToolTip("d-selee");
        itemToRectDraw->setImage(myImage);
///        itemToRectDraw->setPos(qFabs(screenSize.width()/3),qFabs(screenSize.height()/3));
//qDebug()<<qFabs(this->width()/2);
        this->addItem(itemToRectDraw);
        graphicsList.append(itemToRectDraw);
        graphicsListTemp.append(itemToRectDraw);
        historyBack.append(itemToRectDraw);
        historyBackAction.append("added");
       // itemToRectDraw->setToolTip("d-selee");
}
if(mySekilType==DiagramItem::DiagramType::Cetvel){
    itemToRectDraw->setPos(qFabs(screenSize.width()/2)-300,qFabs(screenSize.height()/2)-100);
 itemToRectDraw->setRect(0,0,600,100);}
else if(mySekilType==DiagramItem::DiagramType::Gonye){
    itemToRectDraw->setPos(qFabs(screenSize.width()/2)-180,qFabs(screenSize.height()/2)-175);
 itemToRectDraw->setRect(0,0,360,250);}
else if(mySekilType==DiagramItem::DiagramType::Iletki){
    itemToRectDraw->setPos(qFabs(screenSize.width()/2)-200,qFabs(screenSize.height()/2)-175);
 itemToRectDraw->setRect(0,0,400,250);
}
else if(mySekilType==DiagramItem::DiagramType::Pergel){
    itemToRectDraw->setPos(qFabs(screenSize.width()/2)-65,qFabs(screenSize.height()/2)-115);
 itemToRectDraw->setRect(0,0,130,130);
}

else if(mySekilType==DiagramItem::DiagramType::NDogru){
    itemToRectDraw->setPos(qFabs(screenSize.width()/2)-300,qFabs(screenSize.height()/2));

    itemToRectDraw->setRect(0,0,600,30);
}
else if(mySekilType==DiagramItem::DiagramType::NKoordinat){
    itemToRectDraw->setPos(qFabs(screenSize.width()/2)-300,qFabs(screenSize.height()/2)-350);
      itemToRectDraw->setRect(0,0,600,600);
}
else if(mySekilType==DiagramItem::DiagramType::NNKoordinat){
    itemToRectDraw->setPos(qFabs(screenSize.width()/2)-300,qFabs(screenSize.height()/2)-350);
     itemToRectDraw->setRect(0,0,600,600);
}
else if(mySekilType==DiagramItem::DiagramType::HNKoordinat){
    itemToRectDraw->setPos(qFabs(screenSize.width()/2)-205,qFabs(screenSize.height()/2)-255);
     itemToRectDraw->setRect(0,0,411,411);
}

//else itemToRectDraw->setRect(0,0,event->scenePos().x() - origPoint.x(),event->scenePos().y() - origPoint.y());
makeItemsControllable(false);
itemToRectDraw->fareState(true);
this->setMode(Scene::Mode::SelectObject, DiagramItem::DiagramType::NoType);
itemToRectDraw=0;


}
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    //qDebug()<<"scene move";

  ///  qDebug()<<"mouseMove myMousePress:"<<myMousePress;
     if(myMousePress){
   switch(sceneModeTrue)
   {
   case DrawRectangleTrue:{
 //qDebug()<<"move rectangle"<<mySekilType<<mySekilKalemColor<< mySekilPenSize<< mySekilPenStyle;
       if(!itemToRectDraw){

           itemToRectDraw = new VERectangle(this);
           itemToRectDraw->sekilTur(mySekilType);
           itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
           itemToRectDraw->setBrush(mySekilZeminColor);
           itemToRectDraw->setImage(myImage);
           itemToRectDraw->setPos(origPoint);
           this->addItem(itemToRectDraw);

           graphicsList.append(itemToRectDraw);
           graphicsListTemp.append(itemToRectDraw);
           historyBack.append(itemToRectDraw);
           historyBackAction.append("added");
   }




if(mySekilType==DiagramItem::DiagramType::Cetvel) itemToRectDraw->setRect(0,0,600,100);
else if(mySekilType==DiagramItem::DiagramType::Gonye) itemToRectDraw->setRect(0,0,360,250);
else if(mySekilType==DiagramItem::DiagramType::Iletki) itemToRectDraw->setRect(0,0,400,250);
else if(mySekilType==DiagramItem::DiagramType::NDogru) itemToRectDraw->setRect(0,0,600,30);
else if(mySekilType==DiagramItem::DiagramType::NKoordinat) itemToRectDraw->setRect(0,0,600,600);
else if(mySekilType==DiagramItem::DiagramType::NNKoordinat) itemToRectDraw->setRect(0,0,600,600);
else if(mySekilType==DiagramItem::DiagramType::Kup) itemToRectDraw->setRect(0,0,qFabs(event->scenePos().x() - origPoint.x()),qFabs(event->scenePos().y() - origPoint.y()));
else if(mySekilType==DiagramItem::DiagramType::Silindir) itemToRectDraw->setRect(0,0,qFabs(event->scenePos().x() - origPoint.x()),qFabs(event->scenePos().y() - origPoint.y()));
else if(mySekilType==DiagramItem::DiagramType::Pramit) itemToRectDraw->setRect(0,0,qFabs(event->scenePos().x() - origPoint.x()),qFabs(event->scenePos().y() - origPoint.y()));
else if(mySekilType==DiagramItem::DiagramType::Kure) itemToRectDraw->setRect(0,0,qFabs(event->scenePos().x() - origPoint.x()),qFabs(event->scenePos().y() - origPoint.y()));
else
    itemToRectDraw->setRect(0,0,event->scenePos().x() - origPoint.x(),event->scenePos().y() - origPoint.y());

makeItemsControllable(false);

//itemToRectDraw->fareState(true);

       break;}
   case DrawPenTrue:{

       sceneMoveState=true;
       QGraphicsLineItem*  itemToPenDraw = new QGraphicsLineItem();
       this->addItem(itemToPenDraw);
       itemToPenDraw->setPen(QPen(myPenColor,myPenSize, myPenStyle, Qt::RoundCap ,Qt::RoundJoin));
      auto *point=new QGraphicsLineItem();
      addItem(point);
      point->setPen(QPen(myPenColor,myPenSize, myPenStyle, Qt::RoundCap ,Qt::RoundJoin));
       //  qDebug()<<"1";
       if(tv!=0){
        //qDebug()<<"2";
       if(tv->rotateState&&(tv->sekilTr==DiagramItem::DiagramType::Pergel)){//pergel işlemleri yapılıyor
           //qDebug()<<"3";
             /*  itemToPenDraw->setLine(
               tv->scenePos().x(),tv->scenePos().y()
              ,tv->scenePos().x()+1,tv->scenePos().y()+1 );
              */

      itemToPenDraw->setLine(origPoint.x(),origPoint.y()
                             ,tv->scenePos().x(),tv->scenePos().y() );
      origPoint =tv->scenePos();
if(tv->centerPoint==false)
{
      point->setLine(
   tv->scenePos().x()+tv->boundingRect().width(),tv->scenePos().y()+tv->boundingRect().height()
 ,tv->scenePos().x()+tv->boundingRect().width()+1,tv->scenePos().y()+tv->boundingRect().height()+1
                  );
      tv->centerPoint=true;
       }

       }

       }else{
          // qDebug()<<"4";
           itemToPenDraw->setLine(origPoint.x(),origPoint.y(),event->scenePos().x(),event->scenePos().y() );
           origPoint = event->scenePos();
           endPos=event->scenePos();
            points<<event->scenePos();

            graphicsListTemp.append(itemToPenDraw);
            graphicsListpoints.append(itemToPenDraw);
           if(sx>endPos.x()) sx=endPos.x();
           if(sy>endPos.y()) sy=endPos.y();
           if(ex<endPos.x()) ex=endPos.x();
           if(ey<endPos.y()) ey=endPos.y();

       }


       itemToPenDraw=nullptr;
       // qDebug()<<"5";
       break;
   }
   case DrawPenFosforTrue:{

         //  QGraphicsTextItem*  textDraw = new QGraphicsTextItem();
       //textDraw->setPlainText();
       QGraphicsLineItem*  itemToPenDraw = new QGraphicsLineItem();
       this->addItem(itemToPenDraw);
       itemToPenDraw->setPen(QPen(myPenColor,myPenSize, myPenStyle, Qt::RoundCap ,Qt::RoundJoin));
       itemToPenDraw->setLine(origPoint.x(),origPoint.y(),event->scenePos().x(),event->scenePos().y() );

       graphicsList.append(itemToPenDraw);
       graphicsListTemp.append(itemToPenDraw);
       ///historyBack.append(itemToRectDraw);
       ///historyBackAction.append("added");


       origPoint = event->scenePos();
       graphicsListpoints.append(itemToPenDraw);


       points<<event->scenePos();
       itemToPenDraw=nullptr;
         endPos=event->scenePos();
       if(sx>endPos.x()) sx=endPos.x();
       if(sy>endPos.y()) sy=endPos.y();
       if(ex<endPos.x()) ex=endPos.x();
       if(ey<endPos.y()) ey=endPos.y();

       break;}
  // case CopyModeTrue:{ break;}
   case EraseModeTrue:{
      // qDebug()<<"move siliniyor";
       int boyut;

              boyut=myEraseSize*3;
              QRect rect(QPoint(event->scenePos().toPoint().x()-boyut,event->scenePos().toPoint().y()-boyut),QPoint(event->scenePos().toPoint().x()+boyut,event->scenePos().toPoint().y()+boyut) );
              QPainterPath pp;
              pp.addRect(rect);
              setSelectionArea(pp);
              removeOddItem();

       break;}
   //case SelectObjectTrue:{ break;}
   }
update();

    QGraphicsScene::mouseMoveEvent(event);
     }

}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
  ///  qDebug()<<"mouseRelease myMousePress:"<<myMousePress;
 // qDebug()<<"3";
 if(myMousePress){
    switch (sceneModeTrue)
    {
    case DrawRectangleTrue:{

         //if(mySekilType==DiagramItem::DiagramType::Resim)
        // {
            // this->setMode(tempSceneMode, tempSekilType);
        // }
         //else
        if(mySekilType==DiagramItem::DiagramType::Cizgi)
         {
             //itemToRectDraw->fareState(true);
             //this->setMode(Scene::Mode::SelectObject, DiagramItem::DiagramType::NoType);
         }
         else if(mySekilType==DiagramItem::DiagramType::Ok)
         {
             //itemToRectDraw->fareState(true);
             //this->setMode(Scene::Mode::SelectObject, DiagramItem::DiagramType::NoType);
         }
         else if(mySekilType==DiagramItem::DiagramType::CiftOk)
         {
             //itemToRectDraw->fareState(true);
             //this->setMode(Scene::Mode::SelectObject, DiagramItem::DiagramType::NoType);
         }

         else
         { if(itemToRectDraw!=0) itemToRectDraw->fareState(true);
              this->setMode(Scene::Mode::SelectObject, DiagramItem::DiagramType::NoType);


             //  this->setMode(Scene::Mode::SelectObject, DiagramItem::DiagramType::NoType);

         }
        //this->setMode(Scene::Mode::SelectObject, DiagramItem::DiagramType::NoType);

         itemToRectDraw = 0;
         //
          drawing = false;

           dragMove=true;
         //mwindow->sekilButtonClick();
        break;}
    case DrawPenTrue:{
       // qDebug()<<"6";
           // qDebug()<<"scene realese"<< sceneMoveState<<points.count();
            drawing = false;
            QPixmap *pixmap4;
            if(tv!=0){
            if(tv->rotateState){
               // tv->rotateState = false;

                   dragMove=true;
                sceneMoveState=false;
                tv=0;
               //  qDebug()<<"7";
                break;}
            }
      /*  if(mySekilTanimlamaStatus) {
            //sekilTanimlama();
            //removeOddItem();

            QRect selection;
            selection.setRect(sx,sy,ex , ey );
            QPixmap temp=myImage.copy(selection);
            this->addPixmap(temp);
            break;
            }*/
        /******************************************************/
 //qDebug()<<"8";

        QPen pen(myPenColor,myPenSize, myPenStyle, Qt::RoundCap ,Qt::RoundJoin);
        QPainterPath path;
        path.moveTo(points.at(0));
qDebug()<<"tek tıklama "<<points.size();
        if(points.size()<3)
        {
           // qDebug()<<"scene realese----------------------------"<< sceneMoveState<<points.count();

            sx=sx-1;
            sy=sy-1;
            ex=ex+1;
            ey=ey+1;
            QPointF temppoint=points.at(0);
                        points.clear();
            points<<QPointF(temppoint.x()-1,temppoint.y()-1)<<temppoint<<
                    QPointF(temppoint.x()+1,temppoint.y()+1);
            path.lineTo(points.at(0));
            path.lineTo(points.at(1));
            path.lineTo(points.at(2));
            // QPointF(temppoint.x(),temppoint.y())<</
            qDebug()<<"tek tıklama ";
        }


        if(points.size()>2)
        {

        int i=1;
        int k=3;
      int  kx=qFabs(sx-ex)/points.count();
      int  ky=qFabs(sy-ey)/points.count();
      //  qDebug()<<"path"<<points.count()<<"g:"<<kx<<"y:"<<ky;       // qDebug()<<qFabs(sx-ex);
qDebug()<<"point sayısı: "<<points.size();
      if(sceneMoveState) //eğer move olayı olmussa
        {

          while (i +3< points.size()) {
              if (kx<1||ky<1)
                  path.lineTo(points.at(i+k));
              else path.cubicTo(points.at(i), points.at(i+1), points.at(i+2));

              //path.cubicTo(points.at(i)+startPos, points.at(i+3)+startPos, points.at(i+6)+startPos);

              /// path.cubicTo(points.at(i), points.at(i+1), points.at(i+2));
           //  qDebug()<<i<<i+1<<i+2;
              i +=k;
          }
       //   if ((points.size()-i)==0){qDebug()<<points.size()<<i<<"0 eksik";path.cubicTo(points.at(i-1), points.at(i), points.at(i+1));}
          if ((points.size()-i)==1){/*qDebug()<<points.size()<<i<<"1 eksik";*/path.cubicTo(points.at(i-1), points.at(i), points.at(i));}
          if ((points.size()-i)==2){/*qDebug()<<points.size()<<i<<"2 eksik";*/path.cubicTo(points.at(i), points.at(i+1), points.at(i+1));}
          if ((points.size()-i)==3){/*qDebug()<<points.size()<<i<<"3 eksik";*/path.cubicTo(points.at(i+1), points.at(i+2), points.at(i+2));}
         // if ((points.size()-i)>3){qDebug()<<points.size()<<i<<"dikkattttttt eksik";}
         // qDebug()<<"path"<<path;
         // qDebug()<<"point"<<points;

            }

          while(!graphicsListpoints.isEmpty())
          {
          removeItem(graphicsListpoints.last());
          delete graphicsListpoints.last();
          graphicsListpoints.removeLast();
 //qDebug()<<"deneme";
          }update();

        }
        else
        {
            graphicsListpoints.clear();
        }
       // addPath(path,pen);
        //path.clear();

/******************************************/
        QPixmap pixmap(qFabs(sx-ex)+myPenSize*2, qFabs(sy-ey)+myPenSize*2);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        painter.setWindow(QRect(sx-myPenSize, sy-myPenSize,qFabs(sx-ex)+myPenSize*2, qFabs(sy-ey)+myPenSize*2));
        painter.setPen(pen);
        painter.strokePath(path,pen);
/**********************************************/
        if(mySekilTanimlamaStatus) {
            QPixmap pixmap1(qFabs(sx-ex)+myPenSize*2, qFabs(sy-ey)+myPenSize*2);
            pixmap1.fill(Qt::white);
            QPainter painter1(&pixmap1);
            painter1.setRenderHint(QPainter::Antialiasing, true);
            painter1.setRenderHint(QPainter::SmoothPixmapTransform, true);
            painter1.setWindow(QRect(sx-myPenSize, sy-myPenSize,qFabs(sx-ex)+myPenSize*2, qFabs(sy-ey)+myPenSize*2));
            painter1.setPen(pen);
            painter1.strokePath(path,pen);
           QString sonuc=shapeDetect(pixmap1);
          /// qDebug()<<"Algılanan Şekil: "<<sonuc;
           //DiagramItem *ditem=new DiagramItem();
         //  scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Ucgen);
           itemToRectDraw = new VERectangle(this);
           bool std=false;
           if (sonuc=="0") {std=false;}
           if (sonuc=="1") {std=false;}
           if (sonuc=="2")  {std=false;}
           if (sonuc=="3"){itemToRectDraw->sekilTur(DiagramItem::DiagramType::Ucgen);std=true;}
           if (sonuc=="4"){itemToRectDraw->sekilTur(DiagramItem::DiagramType::Dortgen);std=true;}
           if (sonuc=="5"){itemToRectDraw->sekilTur(DiagramItem::DiagramType::Besgen);std=true;}
           if (sonuc=="6"){itemToRectDraw->sekilTur(DiagramItem::DiagramType::Altigen);std=true;}
           if (sonuc=="7"){itemToRectDraw->sekilTur(DiagramItem::DiagramType::Cember);std=true;}
           if (sonuc=="8"){itemToRectDraw->sekilTur(DiagramItem::DiagramType::Cember);std=true;}
           if(std==true)
           {
           itemToRectDraw->setPen(pen);
          // itemToRectDraw->setImage(pixmap);
           itemToRectDraw->setPos(sx-myPenSize,sy-myPenSize);
           this->addItem(itemToRectDraw);
           graphicsList.append(itemToRectDraw);
           graphicsListTemp.append(itemToRectDraw);
           historyBack.append(itemToRectDraw);
           historyBackAction.append("added");
           }else{
               itemToRectDraw=0;
           }
           // break;
            }

        /****************************************************************/
         if(!itemToRectDraw){
             itemToRectDraw = new VERectangle(this);
             itemToRectDraw->sekilTur(DiagramItem::DiagramType::Resim);
             itemToRectDraw->setPen(pen);
             itemToRectDraw->setImage(pixmap);
             itemToRectDraw->setPos(sx-myPenSize,sy-myPenSize);
             this->addItem(itemToRectDraw);
             graphicsList.append(itemToRectDraw);
             graphicsListTemp.append(itemToRectDraw);
             historyBack.append(itemToRectDraw);
             historyBackAction.append("added");

            // addPath(path,pen);
            // addPixmap(pixmap);
     }
        /// qDebug()<<"eklendi**********************";
         itemToRectDraw->setRect(0,0,qFabs(sx-ex)+2*myPenSize,qFabs(sy-ey)+2*myPenSize);

         //  itemToRectDraw->setRect(0,0,qFabs(startPos.x()),qFabs(event->scenePos().y() - origPoint.y()));
     itemToRectDraw->fareState(false);
       // }
     itemToRectDraw = 0;

        dragMove=true;
     sceneMoveState=false;

     /******************************************************/
        //itemToLineDraw = 0;
       // itemToPenDraw=0;
         //  qDebug()<<"Fare Bitiş Pozisyonu: "<<event->scenePos();
       //    if(mySekilTanimlamaStatus) sekilTanimlama();
        break;
    }
    case DrawPenFosforTrue:{
        drawing = false;
       // qDebug()<<"fosforlu kalem..................";
        /******************************************************/
        QPainterPath path;
        path.moveTo(points.at(0));
        int i=1;
          while (i +4 < points.size()) {
              path.cubicTo(points.at(i), points.at(i+2), points.at(i+4));
             // path.cubicTo(points.at(i)+startPos, points.at(i+3)+startPos, points.at(i+6)+startPos);

              i += 4;
          }
         QPen pen(myPenColor,myPenSize, myPenStyle, Qt::RoundCap ,Qt::RoundJoin);
        /// addPath(path,pen);

         /****************************************************************/

          while(!graphicsListpoints.isEmpty())
          {
          removeItem(graphicsListpoints.last());
          delete graphicsListpoints.last();
          graphicsListpoints.removeLast();

          }update();

          QPixmap pixmap(qFabs(sx-ex)+myPenSize*2, qFabs(sy-ey)+myPenSize*2);
          pixmap.fill(Qt::transparent);
          QPainter painter(&pixmap);
          painter.setRenderHint(QPainter::Antialiasing, true);
          painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
          painter.setWindow(QRect(sx-myPenSize, sy-myPenSize,qFabs(sx-ex)+myPenSize*2, qFabs(sy-ey)+myPenSize*2));
          painter.setPen(pen);
          painter.strokePath(path,pen);

          if(!itemToRectDraw){
              itemToRectDraw = new VERectangle(this);
              itemToRectDraw->sekilTur(DiagramItem::DiagramType::Resim);
              itemToRectDraw->setPen(pen);
              itemToRectDraw->setImage(pixmap);
              itemToRectDraw->setPos(sx-myPenSize,sy-myPenSize);
              this->addItem(itemToRectDraw);
              graphicsList.append(itemToRectDraw);
              graphicsListTemp.append(itemToRectDraw);
              historyBack.append(itemToRectDraw);
              historyBackAction.append("added");

             // addPath(path,pen);
             // addPixmap(pixmap);
      }
          itemToRectDraw->setRect(0,0,qFabs(sx-ex)+2*myPenSize,qFabs(sy-ey)+2*myPenSize);

          //  itemToRectDraw->setRect(0,0,qFabs(startPos.x()),qFabs(event->scenePos().y() - origPoint.y()));
      itemToRectDraw->fareState(false);
        // }
      itemToRectDraw = 0;
        //itemToLineDraw = 0;
        break;}
    case CopyModeTrue:{

        if(!itemToRectDraw){

             itemToRectDraw = new VERectangle(this);
            itemToRectDraw->sekilTur(DiagramItem::DiagramType::Copy);
            itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
            itemToRectDraw->setBrush(mySekilZeminColor);
            //painter->drawPixmap(0,0,desk.scaled(rect.width(),rect.height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation).copy(selection));
            //itemToRectDraw->setImage()QPixmap::fromImage(imgmm.copy(selection));
            QRect selection;
            selection.setRect(origPoint.x(),origPoint.y(),event->scenePos().x()-origPoint.x() , event->scenePos().y()-origPoint.y() );
            QPixmap temp=myImage.copy(selection);


            itemToRectDraw->setPos(QPoint(origPoint.x()-1,origPoint.y()-1));
            itemToRectDraw->setImage(temp);

            itemToRectDraw->setRect(0,0,event->scenePos().x() - origPoint.x(),event->scenePos().y() - origPoint.y());
         ///   this->addItem(itemToRectDraw);
             itemToRectDraw->fareState(false);

            tempCopyModeItemToRectDraw=itemToRectDraw;///Çok önemli
            makeItemsControllable(false);
            itemToRectDraw->fareState(true);
            //myImage;
            itemToRectDraw = 0;
            drawing = false;
            this->setMode(Scene::Mode::SelectObject, DiagramItem::DiagramType::NoType);
            dragMove=true;
            //this->removeItem(text);
            //this->removeItem(text1);

            /**********************************/
            FileCrud *fc=new FileCrud();
            fc->dosya="E-Tahta.copy.ini";
            if(fc->fileexists()) fc->fileremove();
            fc->fileWrite("copy=1");

            /********************************/
        }
      //  qDebug()<<"copy bitti";

        break;}
    case EraseModeTrue:{
        //mw->setCursor(Qt::ArrowCursor);
         drawing = false;
         makeItemsControllable(false);

        break;
    }
    //case SelectObjectTrue:{break;}
    }
    depo::historyBackCount=historyBack.count();
    depo::historyNextCount=historyNext.count();
    origPoint = event->scenePos();
    this->update();
    sceneModeTrue=NoModeTrue;
 //_sekil=DiagramItem::DiagramType::NoType;
 QGraphicsScene::mouseReleaseEvent(event);

 }
}

void Scene::sekilTanimlama()
{
     qDebug()<<"deneme";
    bool nsx=false,nex=false;
    bool ds=false,de=false;
int mj=0;
int alan=0;
// qDebug()<<"Alan: "<<sx<<sy<<ex<<ey<<"xu:"<<qFabs(sx-ex)<<"yu:"<<qFabs(sy-ey);
if(qFabs(sx-ex)>qFabs(sy-ey)) mj=qFabs(sx-ex); else mj=qFabs(sy-ey);

for(int i=sy;i<=ey;i+=5)
{
    nsx=false;nex=false;
    ds=false;
    de=false;
    for(int j=sx;j<=ex;j+=5)
    {

      //  QGraphicsItem *item = itemAt(i,j, QTransform);4
        QGraphicsItem *item = itemAt(j,i, QTransform());
        QGraphicsItem *item1 = itemAt(j+5,i, QTransform());


        if((item)&&(nsx==false)&&(nex==false)) {nsx=true;ds=true;}
        if ((item1)&&(nex==false)&&(nsx==true)&&(ds==true)) {nex=true;}

      if((nsx==true)&&(item==0)&&(nex==false))
       {
          alan=alan+25;
           item=0;
 /*QGraphicsLineItem*  itemToPenDraw = new QGraphicsLineItem();
 this->addItem(itemToPenDraw);
 itemToPenDraw->setPen(QPen(QColor(0,0,50,20),myPenSize, myPenStyle, Qt::RoundCap ,Qt::RoundJoin));
 itemToPenDraw->setLine(j,i,j+1,i);
*/
    }
   }
}
alan=alan+qFabs(sy-ey)*5;
/************ALANI SİLME*********************/
 makeItemsControllable(true);//
QRect rect(QPoint(sx-35,sy-35),QPoint(ex+35,ey+35));
QPainterPath pp;
pp.addRect(rect);
setSelectionArea(pp);
//removeOddItem();
//clearSelection();
/**********************************/
//qDebug()<<"mj eksen"<<mj;
//qDebug()<<"alan "<<alan;
float k=(3.1416*mj*mj)/(4*alan);
qDebug()<<"K:"<<k;
mySekilType=DiagramItem::DiagramType::NoType;
 if(k>0&&k<1.4) mySekilType=DiagramItem::DiagramType::Dortgen;
 else if(k>1.5&&k<2) mySekilType=DiagramItem::DiagramType::Cember;
else if(k>2&&k<2.9) mySekilType=DiagramItem::DiagramType::Ucgen;
else if(k>2.9&&k<6) mySekilType=DiagramItem::DiagramType::Dortgen;
else if(k>6) mySekilType=DiagramItem::DiagramType::Cember;

 //origPoint = event->scenePos();
/**********************************************/
 if(mySekilType!=DiagramItem::DiagramType::NoType)
 {
     itemToRectDraw = new VERectangle(this);
     itemToRectDraw->sekilTur(mySekilType);
     itemToRectDraw->setPen(QPen(QColor(0,0,0,255), 4, Qt::SolidLine));
     itemToRectDraw->setBrush(mySekilZeminColor);
     itemToRectDraw->setPos(sx,sy);

     this->addItem(itemToRectDraw);

     itemToRectDraw->setRect(0,0,qFabs(sx-ex),qFabs(sy-ey));
     itemToRectDraw->fareState(true);
 }
/*************************************************/


}
void Scene::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete)
        foreach(QGraphicsItem* item, selectedItems()){
            removeItem(item);
            delete item;
        }
    else
        QGraphicsScene::keyPressEvent(event);
}

void Scene::removeOddItem(){
        /* foreach(QGraphicsItem* item, selectedItems()){
            removeItem(item);
            delete item;
        }*/
    foreach(QGraphicsItem* item, selectedItems()){
        VERectangle * selection = dynamic_cast<VERectangle *>(item);

        if(selection)
        {
            if(selection->sekilTr!=DiagramItem::DiagramType::Pdf&&
               selection->sekilTr==DiagramItem::DiagramType::Kalem){
            qDebug()<<"silinecek:"<<selection->sekilTr;

            //*************************************/
           /* if(!graphicsListHistoryBack.isEmpty())
            {
           graphicsListHistoryBack.removeAll(selection);

            }
            graphicsListHistoryNext.append(selection);
*/
            historyBack.append(selection);
            historyBackAction.append("deleted");
            removeItem(selection);
           // delete selection;
            update();
            //  qDebug()<<"Renctange  Modify Silindi.";
            /*****************************************/
            }
        }


    }
    /***************************************************************/
    foreach(QGraphicsItem* item, selectedItems()){
        VERectangle * selection = dynamic_cast<VERectangle *>(item);

        if(!selection)
        {

            if(!item->parentItem())
             {
            //*************************************/
            if(!graphicsList.isEmpty())
            {
           graphicsList.removeAll(item);

            }
        //    qDebug()<<item<<"Line Silindi.";
            removeItem(item);
            delete item;
            update();

            /*****************************************/
            }
        }


    }

    depo::historyBackCount=this->historyBack.count();
    depo::historyNextCount=this->historyNext.count();

}

void Scene::slotMove(QGraphicsItem *signalOwner, qreal dx, qreal dy)
{
    /*foreach (QGraphicsItem *item, selectedItems()) {
        if(item != signalOwner) item->moveBy(dx,dy);
    }*/
}

void Scene::removeAllItem(){
    //clear();
    QList<QGraphicsItem*> list=items();
   // list.rbegin();
    std::reverse(std::begin(list),std::end(list));
    foreach(QGraphicsItem* item, list){
        VERectangle * selection = dynamic_cast<VERectangle *>(item);

        if(selection)
        {
           //  qDebug()<<" nesne"<<item;
           if(selection->sekilTr!=DiagramItem::DiagramType::Pdf){
             //    qDebug()<<"benim nesne"<<selection->sekilTr<<DiagramItem::DiagramType::Pdf;
                //*************************************/
                if(!graphicsList.isEmpty())
                {
                    graphicsList.removeAll(selection);

                }
                //   graphicsListNext.insert(0,selection);
                //historyBack.insert(0,selection);
                // historyBackAction.insert(0,"deleted");
                historyBack.append(selection);
                historyBackAction.append("deleted");

                removeItem(selection);
                // delete selection;
                update();
                /*****************************************/
            }
        }
    }
    foreach(QGraphicsItem* item, items()){
        VERectangle * selection = dynamic_cast<VERectangle *>(item);

        if(!selection)
        {

           if(!item->parentItem())
            {
            //qDebug()<<"diger nesne"<<item<<item->parentItem();
            removeItem(item);
            delete item;
            update();
            }
        }
    }


    depo::historyBackCount=this->historyBack.count();
    depo::historyNextCount=this->historyNext.count();


}

void Scene::setParent(QMainWindow* _mwindow)
{
    mw=_mwindow;
}

void Scene::setMode(Mode mode,DiagramItem::DiagramType sekil){

    tempSekilType=mySekilType;
    mySekilType=sekil;
    tempSceneMode=sceneMode;
    sceneMode = mode;
     QGraphicsView::DragMode vMode =QGraphicsView::NoDrag;
    if(mode == DrawLine){
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
    }
    if(mode == DrawRectangle){
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
    }
    if(mode == DrawEllipse){
        makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
     }
    else if(mode == DrawPen){
         makeItemsControllable(false);
        vMode = QGraphicsView::NoDrag;
    }

   else if(mode == GeriAlMode){
    //qDebug()<<"Geri Al";
      //  qDebug()<<"Geri Al"<<"historycount"<<Scene::graphicsListHistoryBack.count();

        if(!historyBack.isEmpty())
        {
            // qDebug()<<graphicsList.last();
            if(historyBackAction.last()=="added"&&!historyBack.isEmpty())
            {
                historyNext.append(historyBack.last());
                historyNextAction.append(historyBackAction.last());

                removeItem(historyBack.last());

                historyBack.removeLast();
                historyBackAction.removeLast();
               // qDebug()<<"added calıştı";
            }
        }
        if(!historyBack.isEmpty())
        {
            if (historyBackAction.last()=="deleted")
            {
              //  historyNext.append(historyBack.last());
              //  historyNextAction.append(historyBackAction.last());

                addItem(historyBack.last());
                historyBack.removeLast();
                historyBackAction.removeLast();
                //qDebug()<<"deleted calıştı";

            }

            //graphicsListNext.append(graphicsList.last());
            //  delete graphicsList.last();

            update();
        }
        depo::historyBackCount=historyBack.count();
        depo::historyNextCount=historyNext.count();

    }
    else if(mode == IleriAlMode){
        //qDebug()<<"ileri Al";
        if(!historyNext.isEmpty())
        {
            VERectangle * selection = dynamic_cast<VERectangle *>(historyNext.last());
            this->addItem(selection);
            historyBack.append(selection);
            historyBackAction.append(historyNextAction.last());
           //graphicsListTemp.append(graphicsListNext.last());
            historyNext.removeLast();
            historyNextAction.removeLast();
            update();
        }
        depo::historyBackCount=historyBack.count();
        depo::historyNextCount=historyNext.count();

        }
    else if(mode == ScreenMode){

    }
    else if(mode == TransparanMode){
         }
    else if(mode == BlackBoardMode){

    }
    else if(mode == EraseMode){

        drawing=false;
        dragMove=true;
        makeItemsControllable(false);
       /* vMode = QGraphicsView::RubberBandDrag;
        */
    }
    else if(mode == ClearMode){

        removeAllItem();
    }
    else if(mode == SelectObject){
        drawing=false;
        dragMove=true;
        makeItemsControllable(true);
        vMode = QGraphicsView::RubberBandDrag;

}
           QGraphicsView* mView = views().at(0);
           if(mView)
            mView->setDragMode(vMode);
}

void Scene::setImage(QPixmap _myImage){
    myImage=_myImage;
}

void Scene::setSekilTanimlamaStatus(bool _mySekilTanimlamaStatus)
{
    mySekilTanimlamaStatus=_mySekilTanimlamaStatus;
}

void Scene::setPopMenuStatus(bool _myPopMenuStatus)
{
myPopMenuStatus=_myPopMenuStatus;//qDebug()<<"sPopMenuStatus: "<<myPopMenuStatus;
}
void Scene::setMousePressStatus(bool _myMousePress)
{
    myMousePress=_myMousePress;
}

void Scene::setPenSize(int _myPenSize){
    myPenSize=_myPenSize;//qDebug()<<"sKalem Size: "<<myPenSize;
}
void Scene::setEraseSize(int _myEraseSize){
    myEraseSize=_myEraseSize;//qDebug()<<"sSilgi Size: "<<myEraseSize;
}
void Scene::setPenColor(QColor _myPenColor){
    myPenColor=_myPenColor;//qDebug()<<"sKalem Color: "<<myPenColor;
}
void Scene::setPenAlpha(int _myPenAlpha){
    myPenAlpha=_myPenAlpha;//qDebug()<<"sKalem Alpha: "<<myPenAlpha;
}
void Scene::setPenStyle(Qt::PenStyle _myPenStyle){
    myPenStyle=_myPenStyle;//qDebug()<<"sKalem Style: "<<myPenStyle;
}
void Scene::setSekilPenStyle(Qt::PenStyle _mySekilPenStyle)
{
     mySekilPenStyle=_mySekilPenStyle;//qDebug()<<"sSekilKalem Style: "<<mySekilPenStyle;
}
void Scene::setSekilPenSize(int _mySekilPenSize){
    mySekilPenSize=_mySekilPenSize;//qDebug()<<"sSekilKalem Size: "<<mySekilPenSize;
}
void Scene::setSekilKalemColor(QColor _mySekilKalemColor){
    mySekilKalemColor=_mySekilKalemColor;//qDebug()<<"sŞekil Kalem Color: "<<mySekilKalemColor;
}
void Scene::setSekilZeminColor(QColor _mySekilZeminColor){
    mySekilZeminColor=_mySekilZeminColor;//qDebug()<<"sŞekil Kalem Color: "<<mySekilZeminColor;
}
void Scene::makeItemsControllable(bool areControllable){
    foreach(QGraphicsItem* item, items()){
        VERectangle * selection = dynamic_cast<VERectangle *>(item);

        if(selection)
        {
            item->setFlag(QGraphicsItem::ItemIsSelectable,areControllable);
            item->setFlag(QGraphicsItem::ItemIsMovable,areControllable);
            if(!areControllable)selection->fareState(areControllable);
        }
        else
        {
            item->setFlag(QGraphicsItem::ItemIsSelectable,areControllable);
            item->setFlag(QGraphicsItem::ItemIsMovable,areControllable);
        }

    }
}

/**
 * Helper function to find a cosine of angle between vectors
 * from pt0->pt1 and pt0->pt2
 */
double Scene::angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}
void Scene::setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
    int fontface = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 0.4;
    int thickness = 1;
    int baseline = 0;

    cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    cv::Rect r = cv::boundingRect(contour);

    cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));

#if (CV_VERSION_MAJOR >= 4)
    cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), cv::FILLED);
 #else
    cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), CV_FILLED);
 #endif


    cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, 8);
}
QString Scene::shapeDetect(QPixmap pixmap)
{
QString sekil="0";
 pixmap.save("/tmp/shape.png");
   /// qDebug()<<"shape detect";
    //cv::Mat src = cv::imread("polygon.png");
   /// cv::Mat src = cv::imread("../assets/ucgen.jpg");
    cv::Mat src = cv::imread("/tmp/shape.png");

    ///cv::Mat src(pixmap);
//     QImage image = pixmap.toImage();
  /*  QIcon icon(pixmap);
        QSize size(100,100);
        pixmap=icon.pixmap(size, QIcon::Disabled);
*/
    /// QImage image(pixmap.toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied));

     //cv::Mat src(image.height(),image.width(),CV_8UC4,(void *)image.constBits(),image.bytesPerLine());
    // cv::Mat src(pixmap.height(),pixmap.width(),CV_8UC3);
   ///  cv::Mat src(image.height(),image.width(),CV_8UC3,(void *)image.constBits(),image.bytesPerLine());
      //cv::Mat src(image.height(),image.width(),CV_8UC4,(void *)image.constBits(),image.bytesPerLine());

  //  cv::Mat src(image.height(), image.width(),CV_8UC3);
///cv::imshow("src", src);
    if (src.empty())
        return sekil;

    // Convert to grayscale
    cv::Mat gray;


#if (CV_VERSION_MAJOR >= 4)
    cv::cvtColor(src, gray, cv::COLOR_BGR2RGB);
 #else
     cv::cvtColor(src, gray, CV_BGR2GRAY);
 #endif


    // Use Canny instead of threshold to catch squares with gradient shading
    cv::Mat bw;
    cv::Canny(gray, bw, 0, 50, 5);

    // Find contours
    std::vector<std::vector<cv::Point> > contours;
  //



#if (CV_VERSION_MAJOR >= 4)
   cv::findContours(bw.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
 #else
      cv::findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
 #endif



    std::vector<cv::Point> approx;
    cv::Mat dst = src.clone();

    for (int i = 0; i < contours.size(); i++)
    {
        // Approximate contour with accuracy proportional
        // to the contour perimeter
        cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);

        // Skip small or non-convex objects
        if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
            continue;
///qDebug()<<"köşegen: "<<approx.size();
          sekil=QString::number(approx.size());
        if (approx.size() == 3)
        {
            setLabel(dst, "TRI", contours[i]);    // Triangles
            // qDebug()<<"algılanan şekil üçgen";
           /// sekil="ucgen";
        }
        else if (approx.size() >= 4 && approx.size() <= 6)
        {
            // Number of vertices of polygonal curve
            int vtc = approx.size();

            // Get the cosines of all corners
            std::vector<double> cos;
            for (int j = 2; j < vtc+1; j++)
                cos.push_back(angle(approx[j%vtc], approx[j-2], approx[j-1]));

            // Sort ascending the cosine values
            std::sort(cos.begin(), cos.end());

            // Get the lowest and the highest cosine
            double mincos = cos.front();
            double maxcos = cos.back();

            // Use the degrees obtained above and the number of vertices
            // to determine the shape of the contour

            if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
            {
                setLabel(dst, "RECT", contours[i]);
               //  qDebug()<<"algılanan şekil kare";

                ///sekil="dorgen";
            }
            else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27)
            {
                setLabel(dst, "PENTA", contours[i]);
               //  qDebug()<<"algılanan şekil beşgen";
                ///sekil="besgen";
            }
            else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45)
                setLabel(dst, "HEXA", contours[i]);
             //qDebug()<<"algılanan şekil altıgen";
            ///sekil="altigen";
        }
        else
        {
            // Detect and label circles
            double area = cv::contourArea(contours[i]);
            cv::Rect r = cv::boundingRect(contours[i]);
            int radius = r.width / 2;

            if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
                std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
                setLabel(dst, "CIR", contours[i]);
            //qDebug()<<"algılanan şekil daire";
            ///sekil="daire";
        }
    }

    //cv::imshow("src", src);
   // cv::imshow("dst", dst);
    //cv::waitKey(0);
    return sekil;
}
/**
 * Helper function to display text in the center of a contour
 */
