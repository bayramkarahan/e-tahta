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
#ifndef BUTTONCLICK_H
#define BUTTONCLICK_H
#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include<mainwindow.h>
#include<depo.h>
#include<popmenu.h>
#include<QMenu>
#include<QDialog>
class ExceptionEx; // Class which is inherited std::exception
void MainWindow::screenClickButtonClick()
{
    /*QDialog * dialog = new QDialog;
    dialog->setModal(true);
       dialog->setWindowModality(Qt::ApplicationModal);

    dialog->show();
*/

 iconButton();
    buttonColorClear();

    if(screenClickDrm)
    {  //qDebug()<<"pasif";
        screenClickDrm=false;
        currentScreenModeSlot();
        palette->setColor(QPalette::Button, QColor(0,0,0,0));
        screenClickButton->setPalette(*palette);
        screenClickButton->setAutoFillBackground(true);
        //currentScreenMode=tempcurrentScreenMode;
        scene->setMode(currentScreenMode, DiagramItem::DiagramType::NoType);
        scene->setMousePressStatus(true);
        //
    }else
    {
        //qDebug()<<"aktif";
        screenClickDrm=true;
        palette->setColor(QPalette::Button, QColor(212,0,0,255));
        screenClickButton->setPalette(*palette);
        screenClickButton->setAutoFillBackground(true);
       // tempcurrentScreenMode=currentScreenMode;
        scene->setMode(Scene::Mode::NoMode, DiagramItem::DiagramType::NoType);
    scene->setMousePressStatus(false);
    //currentScreenModeSlot();

    }
penWriteStatus=false;

}
void MainWindow::kalemRenkButtonClick()
{
    auto *colorMenus=colorMenu("pencolor");
    colorMenus->show();
    colorMenus->hide();
    currentScreenModeSlot();
    scene->setPopMenuStatus(true);
    colorMenus->exec(mapToGlobal(kalemRenkButton->pos() + QPoint(kutuLeft-colorMenus->width()-2,kutuTop+boy/2)));
    scene->setPopMenuStatus(false);
}
void MainWindow::geriAlButtonClick()
{
    Scene::Mode tempMode=currentScreenMode;
    scene->setMode(Scene::Mode::GeriAlMode, DiagramItem::DiagramType::NoType);
    scene->setMode(tempMode,mySekilType);

    currentScreenModeSlot();
    //kalemButtonClick();
}
void MainWindow::sekilZeminRenkButtonClick(){

    auto *colorMenus=colorMenu("mySekilZeminColor");
    colorMenus->show();
    colorMenus->hide();
    currentScreenModeSlot();
    scene->setPopMenuStatus(true);
    colorMenus->exec(mapToGlobal(sekilMenus->pos()-QPoint(colorMenus->width(),-colorMenus->height()/2)));
    scene->setPopMenuStatus(false);

    palette->setColor(QPalette::Button,mySekilZeminColor);
    sekilZeminRenkButton->setIcon(QIcon(":icons/sekilZeminRenk.png"));
    sekilZeminRenkButton->setAutoFillBackground(true);
    sekilZeminRenkButton->setPalette(*palette);
    sekilZeminRenkButton->update();
    scene->setSekilZeminColor(mySekilZeminColor);

}
void MainWindow::sekilKalemRenkButtonClick(){
    auto *colorMenus=colorMenu("mySekilKalemColor");
    colorMenus->show();
    colorMenus->hide();
    currentScreenModeSlot();
    scene->setPopMenuStatus(true);
    colorMenus->exec(mapToGlobal(sekilMenus->pos()-QPoint(colorMenus->width(),-colorMenus->height()/2)));
    scene->setPopMenuStatus(false);

    sekilKalemRenkButton->setIcon(QIcon(":icons/sekilKalemRenk.png"));
    sekilKalemRenkButton->setAutoFillBackground(true);
    palette->setColor(QPalette::Button,mySekilKalemColor);
    sekilKalemRenkButton->setPalette(*palette);
    sekilKalemRenkButton->update();
    scene->setSekilKalemColor(mySekilKalemColor);

   }
void MainWindow::kirmiziButtonClick(){
    QColor newColor = QColor(255,0,0); setPenColor(newColor);currentScreenModeSlot();//kalemButtonClick();
}
void MainWindow::maviButtonClick(){
    QColor newColor = QColor(0,0,255); setPenColor(newColor);currentScreenModeSlot();//kalemButtonClick();
}
void MainWindow::siyahButtonClick(){
    QColor newColor = QColor(0,0,0); setPenColor(newColor);currentScreenModeSlot();//kalemButtonClick();
}
void MainWindow::kalemButtonClick(){
    scene->setMode(Scene::Mode::DrawPen, DiagramItem::DiagramType::NoType);
    currentScreenMode=Scene::Mode::DrawPen;
    iconButton();
    buttonColorClear();
    palette->setColor(QPalette::Button, QColor(212,0,0,255));
    setPenAlpha(250);
    setPenColor(myPenColor);
    //setPenSize(0);
    scene->setPenSize(myPenSize);
    setPenStyle(myPenStyle);
    setPenAlpha(myPenAlpha);
    kalemButton->setIcon(QIcon(":icons/pen.png"));
    scene->setSekilTanimlamaStatus(false);
    currentScreenModeSlot();
}
void MainWindow::kalemPopButtonClick(){}
void MainWindow::silPopButtonClick(){}
void MainWindow::silMenuButtonClick(){/*silButtonClick'e bağlıdır*/}
void MainWindow::temizleMenuButtonClick(){/*temizleButtonClick'e bağlıdır*/}
void MainWindow::kalemMenuButtonClick(){/*kalemButtonClick'e bağlıdır*/}
void MainWindow::pagePopButtonClick(){}
//void MainWindow::pageButtonClick(){/*silButtonClick'e bağlıdır*/}
void MainWindow::zeminButtonClick(){}
void MainWindow::zeminPopButtonClick(){}
void MainWindow::sekilButtonIconSlot(){
    DiagramItem *ditem=new DiagramItem();
    int ken=300;
    if(DiagramItem::DiagramType::Cember==mySekilType)
    {
        QPixmap pixmap(imageEllipse(ditem->sekilStore(mySekilType,QRectF(QPointF(20,50),QPointF(ken-50,ken-50))),ken,ken));
        sekilButton->setIcon(pixmap);
    }
    else  if(DiagramItem::DiagramType::Pergel==mySekilType)    {sekilButton->setIcon(QIcon(":icons/pergel.png")); }
    else  if(DiagramItem::DiagramType::Cetvel==mySekilType)   {sekilButton->setIcon(QIcon(":icons/cetvel.png")); }
    else  if(DiagramItem::DiagramType::Gonye==mySekilType)    {sekilButton->setIcon(QIcon(":icons/gonye.png")); }
    else  if(DiagramItem::DiagramType::Iletki==mySekilType)    {sekilButton->setIcon(QIcon(":icons/iletki.png")); }
    else  if(DiagramItem::DiagramType::Kup==mySekilType)    {sekilButton->setIcon(QIcon(":icons/kup.png")); }
    else  if(DiagramItem::DiagramType::Silindir==mySekilType)   {sekilButton->setIcon(QIcon(":icons/silindir.png")); }
    else  if(DiagramItem::DiagramType::Pramit==mySekilType)    {sekilButton->setIcon(QIcon(":icons/pramit.png")); }
    else  if(DiagramItem::DiagramType::Kure==mySekilType)    {sekilButton->setIcon(QIcon(":icons/kure.png")); }
    else  if(DiagramItem::DiagramType::NDogru==mySekilType)    {
        sekilButton->setIconSize(QSize(50,50));
        sekilButton->setIcon(QIcon(":icons/ndogru.png"));}
    else  if(DiagramItem::DiagramType::NKoordinat==mySekilType)    {sekilButton->setIcon(QIcon(":icons/nkoordinat.png")); }
    else  if(DiagramItem::DiagramType::NNKoordinat==mySekilType)    {sekilButton->setIcon(QIcon(":icons/nnkoordinat.png")); }
    else  if(DiagramItem::DiagramType::HNKoordinat==mySekilType)    {sekilButton->setIcon(QIcon(":icons/hnkoordinat.png")); }

    else
    {
        QPixmap pixmap(image(ditem->sekilStore(mySekilType,QRectF(QPointF(20,50),QPointF(ken-50,ken-50))),ken,ken));
        sekilButton->setIcon(pixmap);
    }
}

void MainWindow::sekilButtonClick(){
    sekilButtonIconSlot();

    scene->setMode(Scene::Mode::DrawRectangle, mySekilType);
    currentScreenMode=Scene::Mode::DrawRectangle;
    scene->setSekilPenSize(mySekilPenSize);
    scene->setSekilKalemColor(mySekilKalemColor);
    scene->setSekilPenStyle(mySekilPenStyle);
    buttonColorClear();
    currentScreenModeSlot();

}
void MainWindow::sekilPopButtonClick(){}
void MainWindow::fosforluKalemButtonClick(){
    scene->setMode(Scene::Mode::DrawPenFosfor, DiagramItem::DiagramType::NoType);
     currentScreenMode=Scene::Mode::DrawPenFosfor;
    iconButton();
    buttonColorClear();

    //myPenAlpha=35;
    setPenAlpha(100);
    setPenColor(myPenColor);
    iconButton();
    buttonColorClear();
    palette->setColor(QPalette::Button, QColor(212,0,0,255));
    fosforluKalemButton->setPalette(*palette);
    fosforluKalemButton->setAutoFillBackground(true);
    kalemButton->setPalette(*palette);
    kalemButton->setAutoFillBackground(true);
    kalemButton->setIcon(QIcon(":icons/fosforlupen.png"));
    scene->setSekilTanimlamaStatus(false);
    currentScreenModeSlot();


}
void MainWindow::silButtonClick(){
    /*QPixmap p(":/icons/erase.png");
    QPixmap pResult;
    QTransform trans = QTransform();
    trans.rotate(0);
    pResult = p.transformed(trans);
    setCursor(pResult.scaled(24,24,Qt::KeepAspectRatio));
*/
    scene->setMode(Scene::Mode::EraseMode, DiagramItem::DiagramType::NoType);
    currentScreenMode=Scene::Mode::EraseMode;
    iconButton();
    buttonColorClear();
    palette->setColor(QPalette::Button, QColor(212,0,0,255));
    silButton->setPalette(*palette);
    silButton->setAutoFillBackground(true);
    scene->setEraseSize(myEraseSize);
    currentScreenModeSlot();

    //
    /* QPixmap pd(":/icons/erase.png");
    QPixmap pResult;
    QTransform trans = QTransform();
   pResult = pd.transformed(trans);
   setCursor(pResult.scaled(50,50,Qt::KeepAspectRatio));
*/

}
void MainWindow::temizleButtonClick(){
    Scene::Mode tempMode=currentScreenMode;

    scene->setMode(Scene::Mode::ClearMode, DiagramItem::DiagramType::NoType);
    scene->setMode(tempMode,mySekilType);

    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    QPalette palet;
    palet.setBrush(QPalette::Background,pixMap);
    this->setPalette(palet);
    //kalemButtonClick();
    //    qDebug()<<"as:"<<depo::as;
}
void MainWindow::ekranButtonClick(){

    buttonColorClear();
    //scene->setMode(Scene::Mode::ScreenMode, DiagramItem::DiagramType::NoMode);

    if(screenDesktop)
    {
       // wust->hide();
        wsol->hide();
        //  qDebug()<<"ekran aktif";
        screenDesktop=false;
        if(gizleGoster)
        {
            timerGizle->stop();
            //  qDebug()<<"dur"<<gizleGoster<<screenDesktop;
        }

        this->resize(0,0);
        // this->move(kutuLeft,kutuHeight-boy-boy/2);
        // this->setGeometry(QRect(kutuLeft,kutuHeight-boy-boy/2,kutuWidth,boy));
        view->hide();
        /*Qt::WindowFlags flags = 0;
        flags |= Qt::Window;
        flags |= Qt::X11BypassWindowManagerHint;
        flags |= Qt::WindowStaysOnTopHint;
        this->setWindowFlags(flags);
        this->show();
        */
        this->setMinimumSize(0,0);
        QSize screenSize = qApp->screens()[0]->size();
        if(gizleGoster==false)
        {
            //qDebug()<<"hehe";
            //this->setGeometry(QRect(screenSize.width()-kutuWidth-15,kutuTop,kutuWidth,kutuHeight-boy*0.75*6));
            this->setGeometry(QRect(kutuLeft,kutuTop,kutuWidth,kutuHeight-boy*0.75*6));

            buyukKutu->setGeometry(0,0,kutuWidth,kutuHeight-boy*0.75*6);
        }
        else
        {
            // qDebug()<<"hihi";
            // this->setGeometry(QRect(screenSize.width()-kutuWidth-15,kutuTop,kutuWidth,kutuHeight));
            this->setGeometry(QRect(kutuLeft,kutuTop,kutuWidth,kutuHeight));

            buyukKutu->setGeometry(0,0,kutuWidth,kutuHeight);
        }

        /*  tasiButton->hide();
                                        colorButton->hide();
                                             clockButton->hide();
                                            secButton->hide();

                                           gizleGosterButton->hide();
                                           */
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        ///   view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ///  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        /* kalemKapatButton->hide();

                                            hideButton();

*/
        ///  buyukKutu->setGeometry(QRect(0,0,kutuWidth,kutuHeight));
        // buyukKutu->setGeometry(QRect(kutuLeft,kutuTop,kutuWidth,kutuHeight));

        ekranButton->setIcon(QIcon(":icons/screenpen.png"));
        palette->setColor(QPalette::Button, QColor(212,0,0,255));
        ekranButton->setPalette(*palette);
        ekranButton->setAutoFillBackground(true);


    }
    else
    {
        //wust->show();
       ///// if(!wsolVisible) wsol->show();



        screenDesktop=true;
        if(gizleGoster)
        {
            timerGizle->start(15000);
            //  qDebug()<<"dur"<<gizleGoster<<screenDesktop;
        }

        if(gizleGoster==true)
        { //qDebug()<<"hehe";
            buyukKutu->setGeometry(QRect(kutuLeft,kutuTop,kutuWidth,kutuHeight));
        }
        else
        {
            // qDebug()<<"hihi";
            buyukKutu->setGeometry(QRect(kutuLeft,kutuTop,kutuWidth,kutuHeight-boy*0.75*6));
        }
        QSize screenSize = qApp->screens()[0]->size();

        setGeometry(0,0,screenSize.width(),screenSize.height());
        ekranButton->setIcon(QIcon(":icons/screendesktop.png"));
        /*  tasiButton->show();
                                        colorButton->show();
                                        clockButton->show();

                                        secButton->show();



                                          gizleGosterButton->show();
                                          kalemKapatButton->show();
                                            showPenButton();
                                          showZeminButton();
                                          showPcButton();
                                          */
        view->show();
        ///  view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        /// view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        //ScreenMode;
        //scene->setMode(Scene::Mode::GeriAlMode, DiagramItem::DiagramType::NoType);


        if(myZeminType==0) zeminSeffafButtonClick();
        if(myZeminType==1) zeminSiyahButtonClick();
        if(myZeminType==2) zeminBeyazButtonClick();
        if(myZeminType==3) zeminCustomColorInitButtonClick();

    }

}
void MainWindow::kalemKapatButtonClick(){
   // sayfaListeView->close();
    QCoreApplication::exit(0);
}

void MainWindow::gridDisableButtonClick(){
    scene->sceneGridYatay=false;
    scene->sceneGridDikey=false;
    scene->sceneGuzelYazi=false;
    myZeminColor=QColor(0,0,0,0);
    gridLines = new GridLines (this->width(), this->height(),myPenSize*10,scene->sceneGridYatay,scene->sceneGridDikey,scene->sceneGuzelYazi,myZeminColor, myGridColor);
    QSize screenSize = qApp->screens()[0]->size();

    QPixmap bkgnd=gridLines->PixItem(gridLines,screenSize.width(),screenSize.height());
    scene->setForegroundBrush(bkgnd);

    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    QPalette palet;
    palet.setBrush(QPalette::Background,pixMap);
    this->setPalette(palet);
   }
void MainWindow::gridYatayButtonClick(bool toggle){
//qDebug()<<toggle;
    if(toggle)scene->sceneGridYatay=true;
    else scene->sceneGridYatay=!scene->sceneGridYatay;
    scene->sceneGuzelYazi=false;
    myZeminColor=QColor(0,0,0,0);
    gridLines = new GridLines (this->width(), this->height(),myGridSize*10,scene->sceneGridYatay,scene->sceneGridDikey,scene->sceneGuzelYazi,myZeminColor, myGridColor);
    QSize screenSize = qApp->screens()[0]->size();
    QPixmap bkgnd=gridLines->PixItem(gridLines,this->width(), this->height());
    scene->setForegroundBrush(bkgnd);

    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    QPalette palet;
    palet.setBrush(QPalette::Background,pixMap);
    this->setPalette(palet);
}
void MainWindow::gridDikeyButtonClick(bool toggle){

    if(toggle) scene->sceneGridDikey=true;
    else scene->sceneGridDikey=!scene->sceneGridDikey;
    scene->sceneGuzelYazi=false;

    myZeminColor=QColor(0,0,0,0);
    gridLines = new GridLines (this->width(), this->height(),myGridSize*10,scene->sceneGridYatay,scene->sceneGridDikey,scene->sceneGuzelYazi,myZeminColor, myGridColor);
    QSize screenSize = qApp->screens()[0]->size();

    QPixmap bkgnd=gridLines->PixItem(gridLines,this->width(), this->height());
    scene->setForegroundBrush(bkgnd);

    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    QPalette palet;
    palet.setBrush(QPalette::Background,pixMap);
    this->setPalette(palet);

}

void MainWindow::zeminSeffafButtonClick(){
    myZeminType=0;
    myZeminColor=QColor(0,0,0,0);
    scene->sceneGridYatay=false;
    scene->sceneGridDikey=false;
    scene->sceneGuzelYazi=false;
    ///qDebug()<<myGridSize<<gridYatay<<gridDikey<<guzelYazi<<myZeminColor<< myGridColor;
    gridLines = new GridLines (this->width(), this->height(),myGridSize*10,scene->sceneGridYatay,scene->sceneGridDikey,scene->sceneGuzelYazi,myZeminColor, myGridColor);
    QSize screenSize = qApp->screens()[0]->size();
    QPixmap bkgnd=gridLines->PixItem(gridLines,screenSize.width(),screenSize.height());
    //bkgnd.show();
    scene->setBackgroundBrush(bkgnd);

    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setAttribute(Qt::WA_NoSystemBackground, false);
    //this->setAttribute(Qt::WA_NoBackground,true);
    this->repaint();
    QPalette palet;
    palet.setBrush(QPalette::Background, QColor(0,0,0,1));
    this->setPalette(palet);  //setZeminColor(myZeminColor);

    QPixmap pixMap = view->grab(view->sceneRect().toRect());
   // QPalette palet;
    palet.setBrush(QPalette::Background,pixMap);
    this->setPalette(palet);


}
void MainWindow::zeminSiyahButtonClick(){
    myZeminType=1;
    myZeminColor=QColor(0,0,0,255);
    scene->sceneGridYatay=false;
    scene->sceneGridDikey=false;
    scene->sceneGuzelYazi=false;

    gridLines = new GridLines (this->width(), this->height(),myGridSize*10,scene->sceneGridYatay,scene->sceneGridDikey,scene->sceneGuzelYazi,myZeminColor, myGridColor);
    QSize screenSize = qApp->screens()[0]->size();

    QPixmap bkgnd=gridLines->PixItem(gridLines,screenSize.width(),screenSize.height());
    scene->setBackgroundBrush(bkgnd);
    QPixmap pixMap = view->grab(view->sceneRect().toRect());

    QPalette palet;
    palet.setBrush(QPalette::Background,pixMap);
    this->setPalette(palet);


}
void MainWindow::zeminBeyazButtonClick(){
    myZeminType=2;

    myZeminColor=QColor(255,255,255,255);
    scene->sceneGridYatay=false;
    scene->sceneGridDikey=false;
    scene->sceneGuzelYazi=false;

    gridLines = new GridLines (this->width(), this->height(),myGridSize*10,scene->sceneGridYatay,scene->sceneGridDikey,scene->sceneGuzelYazi,myZeminColor, myGridColor);
    QSize screenSize = qApp->screens()[0]->size();

    QPixmap bkgnd=gridLines->PixItem(gridLines,screenSize.width(),screenSize.height());
    scene->setBackgroundBrush(bkgnd);

    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    QPalette palet;
    palet.setBrush(QPalette::Background,pixMap);
    this->setPalette(palet);

}
void MainWindow::zeminCustomColorButtonClick(){

    myZeminType=3;
    scene->sceneGridYatay=false;
    scene->sceneGridDikey=false;
    scene->sceneGuzelYazi=false;


    auto *colorMenus=colorMenu("myZeminColor");
    colorMenus->show();
    colorMenus->hide();
    currentScreenModeSlot();
    scene->setPopMenuStatus(true);
    colorMenus->exec(mapToGlobal(zeminMenus->pos()-QPoint(colorMenus->width(),0)));
    scene->setPopMenuStatus(false);

    palette->setColor(QPalette::Button, myZeminColor);
    zeminCustomColorButton->setPalette(*palette);
    zeminCustomColorButton->update();

    gridLines = new GridLines (this->width(), this->height(),myGridSize*10,scene->sceneGridYatay,scene->sceneGridDikey,scene->sceneGuzelYazi,myZeminColor, myGridColor);
    QSize screenSize = qApp->screens()[0]->size();

    QPixmap bkgnd=gridLines->PixItem(gridLines,screenSize.width(),screenSize.height());
    scene->setBackgroundBrush(bkgnd);

    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    QPalette palet;
    palet.setBrush(QPalette::Background,pixMap);
    this->setPalette(palet);


}
void MainWindow::zeminCustomColorInitButtonClick(){
    ///   qDebug()<<"zeminCustomColorInitButtonClick çalıştı";
    scene->sceneGridYatay=false;
    scene->sceneGridDikey=false;
    scene->sceneGuzelYazi=false;

    gridLines = new GridLines (this->width(), this->height(),myPenSize*10,scene->sceneGridYatay,scene->sceneGridDikey,scene->sceneGuzelYazi,myZeminColor, myGridColor);
    QSize screenSize = qApp->screens()[0]->size();
    QPixmap bkgnd=gridLines->PixItem(gridLines,screenSize.width(),screenSize.height());
    scene->setBackgroundBrush(bkgnd);
    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    QPalette palet;
    palet.setBrush(QPalette::Background,pixMap);
    this->setPalette(palet);
    /* this->setAttribute(Qt::WA_TranslucentBackground, false);
        this->setAttribute(Qt::WA_NoSystemBackground, false);

        this->repaint();
        QPalette palet;
        palet.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palet);

*/
}
void MainWindow::zeminGuzelYaziButtonClick(bool toggle){
    // qDebug()<<"zeminGuzelYaziButtonClick";
   // gridDisableButtonClick();
    //gridDikey=false;
    scene->sceneGridYatay=false;
    scene->sceneGridDikey=false;
    if(toggle) scene->sceneGuzelYazi=true;
    else scene->sceneGuzelYazi=!scene->sceneGuzelYazi;

    myZeminColor=QColor(0,0,0,0);
    gridLines = new GridLines (this->width(), this->height(),myGridSize*10,scene->sceneGridYatay,scene->sceneGridDikey,scene->sceneGuzelYazi,myZeminColor, myGridColor);
    QSize screenSize = qApp->screens()[0]->size();

    QPixmap bkgnd=gridLines->PixItem(gridLines,screenSize.width(),screenSize.height());
    scene->setForegroundBrush(bkgnd);

    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    QPalette palet;
    palet.setBrush(QPalette::Background,pixMap);
    this->setPalette(palet);

}
void MainWindow::zeminMuzikButtonClick(){
    myZeminColor=QColor(0,0,0,0);
    DiagramItem *ditem=new DiagramItem();
    mySekilType=DiagramItem::DiagramType::Muzik;
    QPixmap pim(zeminImage(ditem->sekilStore(mySekilType,QRectF(QPointF(0,0),QPointF(this->width(),this->height()))),this->width(),this->height(),myGridColor,2));
    scene->setForegroundBrush(pim);
    //gridOnOffButtonClick();

    VERectangle*  itemToRectDraw = new VERectangle(scene);
    itemToRectDraw->sekilTur(DiagramItem::DiagramType::Copy);
    itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
    itemToRectDraw->setBrush(mySekilZeminColor);
    QPixmap temp(":icons/musicikon.png");
    itemToRectDraw->setPos(QPoint(50,this->height()/3*0));
    itemToRectDraw->setImage(temp);
    itemToRectDraw->setRect(0,0,75,250);
    scene->addItem(itemToRectDraw);
    itemToRectDraw->fareState(false);
    itemToRectDraw = 0;

   // VERectangle*
            itemToRectDraw = new VERectangle(scene);
    itemToRectDraw->sekilTur(DiagramItem::DiagramType::Copy);
    itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
    itemToRectDraw->setBrush(mySekilZeminColor);
  //  QPixmap temp(":icons/musicikon.png");
    itemToRectDraw->setPos(QPoint(50,this->height()/3*1));
    itemToRectDraw->setImage(temp);
    itemToRectDraw->setRect(0,0,75,250);
    scene->addItem(itemToRectDraw);
    itemToRectDraw->fareState(false);
    itemToRectDraw = 0;

    //VERectangle*
            itemToRectDraw = new VERectangle(scene);
    itemToRectDraw->sekilTur(DiagramItem::DiagramType::Copy);
    itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
    itemToRectDraw->setBrush(mySekilZeminColor);
  //  QPixmap temp(":icons/musicikon.png");
    itemToRectDraw->setPos(QPoint(50,this->height()/3*2));
    itemToRectDraw->setImage(temp);
    itemToRectDraw->setRect(0,0,75,250);
    scene->addItem(itemToRectDraw);
    itemToRectDraw->fareState(false);
    itemToRectDraw = 0;

    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    QPalette palet;
    palet.setBrush(QPalette::Background,pixMap);
    this->setPalette(palet);


}

void MainWindow::ileriSayfaButtonClick(){
    pdfPageList++;int start,end;
  ///  qDebug()<<"ileri: pdfPageList"<<pdfPageList<<"pdfPageCount"<<pdfPageCount<<"ekliSayfa"<<ekliSayfa;
    start=pdfPageList*15-15;
    end=pdfPageList*15;
    if(pdfPageList>=((pdfPageCount+ekliSayfa)/15)+1)
    {   start=pdfPageList*15-15;    end=pdfPageCount+ekliSayfa; pdfPageList=(pdfPageCount+ekliSayfa)/15; }

    for(int i=start;i<end;i++)
    {
        //// qDebug()<<"ileri:"<<start<<end<<i;
        if(i>=ekliSayfa){
            //qDebug()<<"ileri:"<<i;
            if(pageList.count()>i)
            {
               pageList[i]->show();
            }
            else
            {

                ekleSayfaButtonClick(-1,true,i-ekliSayfa);
            }
        }
    }

    for(int i=0;i<pageList.length();i++)
    {
        pageList[i]->hide();
    }

    for(int i=start;i<end;i++)
    {
        palette->setColor(QPalette::Button, QColor(225,225,225,100));
        pageList[i]->setPalette(*palette);
        pageList[i]->setAutoFillBackground(true);
        //pageList[i]->update();

        pageList[i]->show();
    }

  pageButtonClick(start); //ilk sayfa gösteriliyor

}
void MainWindow::geriSayfaButtonClick(){
    pdfPageList--;
  //  qDebug()<<"geri: pdfPageList"<<pdfPageList<<"pdfPageCount"<<pdfPageCount<<"ekliSayfa"<<ekliSayfa;
    int start=pdfPageList*15;
    int end=pdfPageList*15+15;
    if(pdfPageList<=1)
    { pdfPageList=1;  start=pdfPageList*15-15;    end=pdfPageList*15;  }


    for(int i=0;i<pageList.length();i++)
    {
        pageList[i]->hide();
    }

        for(int i=start;i<end;i++)
        {
            palette->setColor(QPalette::Button, QColor(225,225,225,100));
            pageList[i]->setPalette(*palette);
            pageList[i]->setAutoFillBackground(true);
            //pageList[i]->update();
            pageList[i]->show();
        }
        pageButtonClick(start); //ilk sayfa gösteriliyor
   }

void MainWindow::ekleSayfaButtonClick(int inserIndex,bool pdfObjectAdded,int pdfPageIndex){
    bool initprg=false;
   // qDebug()<<"ekle sayfa1"<<sceneSayfaNumber<<sceneSayfaActiveNumber<<pdfObjectAdded<<pdfobjectnumber;
    if(sceneSayfaNumber==0&&sceneSayfaActiveNumber==0)
    {
        initprg=true;
        sceneSayfaNumber++;
        sceneSayfaActiveNumber=0;
        sceneSayfa.removeAt(0);
        //if(pdfobjectnumber==1&&pdfObjectAdded==false) pdfObjectAdded=true;
    }else
    {
        initprg=false;
        sceneSayfaNumber++;

      if(inserIndex==-1)sceneSayfaActiveNumber=sceneSayfaNumber-1;
      else sceneSayfaActiveNumber++;
    }
  ///  qDebug()<<"ekle sayfa2"<<sceneSayfaNumber<<sceneSayfaActiveNumber<<pdfObjectAdded;
    _scene = new Scene(this);
    _scene->pdfObjectAdded=pdfObjectAdded;
    _scene->pdfPageNumber=pdfPageIndex;
    //sceneSayfa.append(_scene);
    sceneSayfa.insert(sceneSayfaActiveNumber,_scene);
    scene=_scene;
    view->setScene(scene);
    // pageNumberPopLabel->setText("Sayfa( "+QString::number(sceneSayfaNumber+1)+" / "+QString::number(sceneSayfaActiveNumber+1)+" )");
    kalemButtonClick();
    auto _screenbtn = new QToolButton(pageListwg);
    _screenbtn->setFixedSize(QSize(boy,boy));
    _screenbtn->setIconSize(QSize(boy*0.7,boy*0.7));
    _screenbtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    _screenbtn->setText(QString::number(sceneSayfaActiveNumber+1));
    _screenbtn->setToolTip(QString::number(sceneSayfaActiveNumber));


    // screenlayout->addWidget(_screenbtn);
    screenlayout->insertWidget(sceneSayfaActiveNumber,_screenbtn);
    // pageList.append(_screenbtn);
    pageList.insert(sceneSayfaActiveNumber,_screenbtn);


   for(int i=0;i<pageList.count();i++){

        pageList[i]->setText(QString::number(i+1));
        pageList[i]->setToolTip(QString::number(i));

    }
   //if(pdfPageList>1) pdfPageList--;
  // ileriSayfaButtonClick();

      connect(_screenbtn, &QPushButton::clicked, [=]() {
        sceneSayfaActiveNumber=_screenbtn->toolTip().toInt();
        clearImage();
       // qDebug()<<"tooltip:"<<_screenbtn->toolTip();
        /******************************************************/
        /// sceneSayfaActiveNumber=_screenbtn->toolTip().toInt();
         scene=sceneSayfa[sceneSayfaActiveNumber];
         view->setScene(scene);

        /// qDebug()<<"ekle button click"<<sceneSayfaNumber<<sceneSayfaActiveNumber<<scene->pdfObjectAdded<<scene->pdfObjectShow<<scene->pdfPageNumber;

         setPenColor(scene->myPenColor);             ///çok önemli işlem
         myPenSize=(scene->myPenSize);               ///çook önemli
         setPenStyle(scene->myPenStyle);             ///çook önemli
         setPenAlpha(scene->myPenAlpha);             ///çook önemli
         mySekilType=scene->mySekilType;           ///çok önemli
         mySekilZeminColor=scene->mySekilZeminColor; ///çok önemli
         mySekilPenSize=scene->mySekilPenSize;       ///çok önemli
         mySekilKalemColor=scene->mySekilKalemColor; ///çok önemli
         setSekilPenStyle(scene->mySekilPenStyle);   ///çok önemli
         myEraseSize=scene->myEraseSize;             ///çok önemli
        // currentScreenMode=scene->sceneMode;         ///çok önemli
         scene->sceneMode=currentScreenMode;         ///çok önemli

        ///ileriGeriSayfa();
       /// qDebug()<<"sayı:"<<pageList.length();
        /**********************************************/
        for(int i=0;i<pageList.length();i++)
        {
            palette->setColor(QPalette::Button, QColor(225,225,225,255));
            pageList[i]->setPalette(*palette);
            pageList[i]->setAutoFillBackground(true);

        }
        palette->setColor(QPalette::Button, QColor(255,0,0,100));
        _screenbtn->setPalette(*palette);
        _screenbtn->setAutoFillBackground(true);
        /**************pdf loader page**** çok önemli***********/
           if(scene->pdfObjectAdded&&scene->pdfObjectShow==false&&scene->pdfPageNumber<=pdfPageCount-1) pdfLoaderPage(scene->pdfPageNumber);///pdf page loader
    currentScreenModeSlot();
        /************************************************/
    });
    /*****************Sayfa Eklenince mutlaka Çalışmalı*****************************/
    for(int i=0;i<pageList.length();i++)
    {
        palette->setColor(QPalette::Button, QColor(225,225,225,255));
        pageList[i]->setPalette(*palette);
        pageList[i]->setAutoFillBackground(true);

    }

    palette->setColor(QPalette::Button, QColor(255,0,0,100));
    _screenbtn->setPalette(*palette);
    _screenbtn->setAutoFillBackground(true);
    scene->sceneGridYatay=false;///?isteğe bağlı
    scene->sceneGridDikey=false;///?isteğe bağlı
    scene->sceneGuzelYazi=false;///?isteğe bağlı
    /**********************************************/

    iconButton();
    buttonColorClear();
    sekilButtonIconSlot();
    scene->myPenAlpha=myPenAlpha;                ///çook önemli
    scene->myPenColor=myPenColor;                ///çok önemli işlem
    scene->myPenSize=myPenSize;                  ///çook önemli
    scene->myPenStyle=myPenStyle;                ///çook önemli
    scene->mySekilType=mySekilType;              ///çok önemli
    scene->mySekilZeminColor=mySekilZeminColor;  ///çok önemli
    scene->mySekilPenSize= mySekilPenSize;       ///çok önemli
    scene->mySekilKalemColor=mySekilKalemColor;  ///çok önemli
    scene->myEraseSize=myEraseSize;              ///çok önemli
    scene->mySekilPenStyle=mySekilPenStyle;      ///çok önemli
    scene->sceneMode=currentScreenMode;          ///çok önemli
    currentScreenModeSlot();
    /************************************************/

      if(initprg==false)
      {
           if(pdfobjectnumber==1)
          {
              // qDebug()<<"sayfa ekle8";
              nextSayfaButton->show();
              backSayfaButton->show();
              zoompozitifSayfaButton->show();
              zoomnegatifSayfaButton->show();
              zoomfitSayfaButton->show();

          }else
          {
              ///     qDebug()<<"sayfa ekle9";
              nextSayfaButton->hide();
              ///  qDebug()<<"sayfa ekle10";
              backSayfaButton->hide();
              zoompozitifSayfaButton->hide();
              zoomnegatifSayfaButton->hide();
              zoomfitSayfaButton->show();

          }

          //  qDebug()<<"sayfa ekle11";
          if(sceneSayfaNumber>1)
          {

              ///ileriGeriSayfaLabel->show();
              delSayfaButton->setEnabled(true);
              //addSayfaButton->show();
          }
          else
          {
              ///ileriGeriSayfaLabel->hide();
              //delSayfaButton->hide();
              delSayfaButton->setEnabled(false);
              // addSayfaButton->hide();
          }
      }
}
void MainWindow::silSayfaButtonClick(){
 //qDebug()<<"sil sayfa-0"<<sceneSayfaActiveNumber;
  /// if(sceneSayfaNumber>0)sceneSayfaNumber--;
    if(sceneSayfaActiveNumber>0){
       // qDebug()<<"sil sayfa-1"<<sceneSayfaActiveNumber;
        //sceneSayfaActiveNumber--;
        delete pageList[sceneSayfaActiveNumber];
        pageList.removeAt(sceneSayfaActiveNumber);
        sceneSayfa.removeAt(sceneSayfaActiveNumber);
        sceneSayfaActiveNumber--;
        sceneSayfaNumber--;
        scene=sceneSayfa[sceneSayfaActiveNumber];
        view->setScene(scene);
     ///sceneSayfaActiveNumber--;
    }
    else if(sceneSayfaActiveNumber==0){
        if(sceneSayfaNumber>0)
        {
           // qDebug()<<"sil sayfa-2"<<sceneSayfaActiveNumber;
            delete pageList[sceneSayfaActiveNumber];
            pageList.removeAt(sceneSayfaActiveNumber);

            sceneSayfa.removeAt(sceneSayfaActiveNumber);
            // sceneSayfaActiveNumber--;
            scene=sceneSayfa[sceneSayfaActiveNumber];
            view->setScene(scene);
            sceneSayfaNumber--;

        }
    }
   // qDebug()<<"sil sayfa-1"<<sceneSayfaNumber<<sceneSayfaActiveNumber;
    /***********************************************/
    for(int i=0;i<pageList.length();i++)
    {
        pageList[i]->setToolTip(QString::number(i));
        pageList[i]->setText(QString::number(i));
        palette->setColor(QPalette::Button, QColor(225,225,225,255));
        pageList[i]->setPalette(*palette);
        pageList[i]->setAutoFillBackground(true);


    }
    palette->setColor(QPalette::Button, QColor(255,0,0,100));
    pageList[sceneSayfaActiveNumber]->setPalette(*palette);
    pageList[sceneSayfaActiveNumber]->setAutoFillBackground(true);
    /**********************************************/
    //   kalemButtonClick();
    Scene::Mode tempMode=currentScreenMode;
    //scene->setMode(Scene::Mode::GeriAlMode, DiagramItem::DiagramType::NoType);
    scene->setMode(tempMode,mySekilType);
    scene->setSekilZeminColor(mySekilZeminColor);
    //sayfaLabel->setText("Sayfa\n( "+QString::number(sceneSayfaNumber+1)+" / "+QString::number(sceneSayfaActiveNumber+1)+" )");
    //  pageNumberPopLabel->setText("Sayfa( "+QString::number(sceneSayfaNumber+1)+" / "+QString::number(sceneSayfaActiveNumber+1)+" )");
    //qDebug()<<"--sayfa No="<<sceneSayfaNumber<<"Aktif Sayfa="<<sceneSayfaActiveNumber;
   /// ileriGeriSayfa();

    ///  qDebug()<<"sayfa ekle6";
      int pdfobject=pdfobjectnumber;
      bool pdfobjectadded=false;
        foreach(QGraphicsItem* item, scene->items()){
            VERectangle * selection = dynamic_cast<VERectangle *>(item);
            if(selection)
            {
                if(selection->sekilTr==DiagramItem::DiagramType::Pdf){ pdfobject++;pdfobjectadded=true;}
            }
        }
        ///qDebug()<<"ekran işlemm"<<pdfobject;
       /// qDebug()<<"sayfa ekle7";
        if(pdfobject>0)
        {
      ///       qDebug()<<"sayfa ekle8";
        nextSayfaButton->show();
        backSayfaButton->show();
        zoompozitifSayfaButton->show();
        zoomnegatifSayfaButton->show();
        zoomfitSayfaButton->show();

        }else
        {
        ///     qDebug()<<"sayfa ekle9";
         nextSayfaButton->hide();
        ///  qDebug()<<"sayfa ekle10";
         backSayfaButton->hide();
         zoompozitifSayfaButton->hide();
         zoomnegatifSayfaButton->hide();
         zoomfitSayfaButton->hide();

        }
      ///  qDebug()<<"sayfa ekle11";
  if(sceneSayfaNumber>1)
  {

  ///ileriGeriSayfaLabel->show();
  delSayfaButton->setEnabled(true);
  //addSayfaButton->show();
  }
  else
  {
       ///ileriGeriSayfaLabel->hide();
      //delSayfaButton->hide();
      delSayfaButton->setEnabled(false);
     // addSayfaButton->hide();
  }
      /*****************************************************************/
  QPixmap pixMap = view->grab(view->sceneRect().toRect());
  QPalette palet;
  palet.setBrush(QPalette::Background,pixMap);
  this->setPalette(palet);
  this->repaint();
}
void MainWindow::zoomfitSayfaButtonClick()
{
    foreach(QGraphicsItem* item, scene->items()){
        VERectangle * selection = dynamic_cast<VERectangle *>(item);

        if(selection)
        {
            if(selection->sekilTr==DiagramItem::DiagramType::Pdf)
            {
                selection->setRect(0,0,this->width()/4*3,this->height());
                selection->setPos(QPoint(this->width()/8,0));

/*
                selection->setRect(0,0,selection->rect().width()/6*7,selection->rect().height()/4*6);

                if(selection->rect().width()+boy<this->width())
                    selection->setPos(QPoint(this->width()/2-selection->rect().width()/2,0));


                if(selection->pos().x()-selection->rect().width()/12<boy)
                    selection->setPos(QPoint(boy*1.1,0));
                */
                 selection->fareState(false);
                scene->update();

              QPixmap pixMap = view->grab(view->sceneRect().toRect());
              QPalette palet;
              palet.setBrush(QPalette::Background,pixMap);
              this->setPalette(palet);

                //    else
               // selection->setPos(QPoint(selection->pos().x()-selection->rect().width()/12,0));

            }
        }


    }
}


void MainWindow::zoompozitifSayfaButtonClick()
{
    foreach(QGraphicsItem* item, scene->items()){
        VERectangle * selection = dynamic_cast<VERectangle *>(item);

        if(selection)
        {
            if(selection->sekilTr==DiagramItem::DiagramType::Pdf)
            {

                selection->setRect(0,0,selection->rect().width()/6*7,selection->rect().height()/4*6);

                if(selection->rect().width()+boy<this->width())
                    selection->setPos(QPoint(this->width()/2-selection->rect().width()/2,0));


                if(selection->pos().x()-selection->rect().width()/12<boy)
                    selection->setPos(QPoint(boy*1.1,0));
                 selection->fareState(false);
                scene->update();

              QPixmap pixMap = view->grab(view->sceneRect().toRect());
              QPalette palet;
              palet.setBrush(QPalette::Background,pixMap);
              this->setPalette(palet);

                //    else
               // selection->setPos(QPoint(selection->pos().x()-selection->rect().width()/12,0));

            }
        }


    }
}
void MainWindow::zoomnegatifSayfaButtonClick()
{
    foreach(QGraphicsItem* item, scene->items()){
        VERectangle * selection = dynamic_cast<VERectangle *>(item);

        if(selection)
        {
            if(selection->sekilTr==DiagramItem::DiagramType::Pdf)
            {

                selection->setRect(0,0,selection->rect().width()/7*6,selection->rect().height()/6*4);
                if(selection->rect().width()/7*6<this->width()+boy)
                    selection->setPos(QPoint(this->width()/2-selection->rect().width()/2,0));
                    else
                    selection->setPos(QPoint(selection->pos().x()+selection->rect().width()/12,0));
                     selection->fareState(false);
                 scene->update();

                 QPixmap pixMap = view->grab(view->sceneRect().toRect());
                 QPalette palet;
                 palet.setBrush(QPalette::Background,pixMap);
                 this->setPalette(palet);

            }
        }


    }
}
void MainWindow::secButtonClick(){
    scene->setMode(Scene::Mode::SelectObject, DiagramItem::DiagramType::NoType);
    iconButton();
    buttonColorClear();
    currentScreenMode=Scene::Mode::SelectObject;
    // secButton->setIcon(QIcon(":icons/selectpointer.png"));
    palette->setColor(QPalette::Button, QColor(212,0,0,255));
    secButton->setPalette(*palette);
    secButton->setAutoFillBackground(true);
    currentScreenModeSlot();
}
void MainWindow::tasiButtonClick(){
    tasi=true;  /* scene->setMode(Scene::Mode::MoveMode, DiagramItem::DiagramType::NoMode);*/
    iconButton();
    buttonColorClear();
    palette->setColor(QPalette::Button, QColor(212,0,0,255));
    tasiButton->setPalette(*palette);
    tasiButton->setAutoFillBackground(true);

}
void MainWindow::gizleGosterButtonClick(){
    /*  if(switched)
       {*/
    buttonColorClear();

    if(gizleGoster)
    {
        gizleGoster=false;
        gizleGosterButton->setIcon(QIcon(":icons/goster.png"));
            saveButton->hide();
        yazdirButton->hide();
        savePdfButton->hide();
        loadPdfButton->hide();
        addShapeButton->hide();
        ayarButton->hide();
        /*******************************************/
        //view->hide();
        //sayfaLabel->hide();
        // qDebug()<<"gizlendi";
        if (screenDesktop==false)
        {
            //  qDebug()<<"ekran seçili gizleme";

            QSize screenSize = qApp->screens()[0]->size();
            this->setGeometry(QRect(screenSize.width()-kutuWidth-15,kutuHeight+kutuTop-boy-boy,kutuWidth,boy*0.8));
            buyukKutu->setGeometry(QRect(0,0,kutuWidth,boy*0.8));
        }
        else
        {
            //                       qDebug()<<"e-tahta seçili gizleme";
            QSize screenSize = qApp->screens()[0]->size();
            buyukKutu->setGeometry(QRect(kutuLeft,kutuTop,kutuWidth,kutuHeight-boy*0.75*6));
        }

        // hideButton();
    }
    else
    {
        // view->hide();
        gizleGoster=true;
        gizleGosterButton->setIcon(QIcon(":icons/gizle.png"));


        tasiButton->show();
        kalemRenkButton->show();
        clockButton->show();
        // penSizeSelector->show();
        secButton->show();

        ekranButton->show();

        kalemKapatButton->show();

        showPenButton();
        showZeminButton();

        showPcButton();
        //sayfaLabel->show();
        if (screenDesktop==false)
        {
            //qDebug()<<"ekran seçili gosterme";
            QSize screenSize = qApp->screens()[0]->size();
            this->setGeometry(QRect(screenSize.width()-kutuWidth-15,kutuTop,kutuWidth,kutuHeight));

            buyukKutu->setGeometry(QRect(0,0,kutuWidth,kutuHeight));
            ekranButton->setIcon(QIcon(":icons/screenpen.png"));
            /*   palette->setColor(QPalette::Button, QColor(212,0,0,255));
                       ekranButton->setPalette(*palette);
                       ekranButton->setAutoFillBackground(true);
*/
        }
        else
        {
            // qDebug()<<"e-tahta seçili gosterme";
            buyukKutu->setGeometry(QRect(kutuLeft,kutuTop,kutuWidth,kutuHeight));

        }
        //kalemButtonClick();
        // Scene::Mode tempMode=currentScreenMode;
        //scene->setMode(Scene::Mode::GeriAlMode, DiagramItem::DiagramType::NoType);
        scene->setMode(currentScreenMode,mySekilType);


    }
  currentScreenModeSlot();
}
void MainWindow::klavyeButtonClick(){
    QFile data(QDir::homePath()+"/.config/eta/virtualkeyboard/config.ini");
    data.open(QIODevice::Text | QIODevice::ReadOnly);
    QString dataText = data.readAll();

    QRegularExpression re("AutoShow=true");
    QString replacementText("AutoShow=false");

    dataText.replace(re, replacementText);

    QFile newData(QDir::homePath()+"/.config/eta/virtualkeyboard/config.ini");
    if(newData.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&newData);
        out << dataText;
    }
    newData.close();
    /******************************************************/
     system("killall eta-keyboard");
    system("sleep 1");
       system("nohup eta-keyboard show &\n");
    system("sleep 1");
    QFile data1(QDir::homePath()+"/.config/eta/virtualkeyboard/config.ini");
    data1.open(QIODevice::Text | QIODevice::ReadOnly);
    QString dataText1 = data1.readAll();

    QRegularExpression re1("AutoShow=false");
    QString replacementText1("AutoShow=true");

    dataText1.replace(re1, replacementText1);

    QFile newData1(QDir::homePath()+"/.config/eta/virtualkeyboard/config.ini");
    if(newData1.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&newData1);
        out << dataText1;
    }
    newData1.close();
    /*******************************************************************/


}
void MainWindow::infoButtonClick(){
    QMessageBox msgBox;
    msgBox.setText("Bu uygulama etkileşimli tahtalarda kullanılmak üzere yazılmıştır."
                   "\n"
                   "\nYapılabilecek Eylemler:"
                   "\n\t* Çeşitli Kalem(Normal, Fosforlu)"
                   "\n\t* Tahta Rengi (Şeffaf, Beyaz, Siyah,Özel Renk)"
                   "\n\t* Tahta Desenleri(Yatay/Dikey Çizgi, Müzik,GüzelYazi)"
                   "\n\t* Otomatik Silgi Seçimi(Kalem Kalınlığına Uygun)"
                   "\n\t* Ekranda Taşıma Özelliği"
                   "\n\t* Tam Ekran Modunda Çalışmalarda Üstte Konumlanma"
                   "\n\t* Dışarıdan Arkaplan Resim Yükleme Özelliği"
                   "\n\t* Ekran Görüntüsünü Kaydetme Özelliği"
                   "\n\t* Geometrik Şekil Seçme,Taşıma,Boyutlandırma Özelliği"
                   "\n\t* Farklı Sanal Masaüstünde Çalışma Özelliği"
                   "\n\t* Geri ileri Alma Özelliği"
                   "\n\t* Ekranın Her Alanına Yazma Özelliği"
                   "\n\t* Pdf Dosyaları Yükleme ve Çalışma Kaydetme Özelliği"
                   "\n\t* Nesne Olarak Resim Ekleme Özelliği"
                   "\n\t* Yazdırma Özelliği"
                   "\n\t* Ekranın Bölgesini (Kesme,Taşıma,Büyültme) Özelliği"
                   "\n\t* Kullanıcı Ayarlarını Kaydetme ve Açma Özelliği"
                   "\n\t* Sınavlar için Sayaç Özelliği"
                   "\n*****************************************************************************"
                   "\n   Copyright (C) 2023 by Bayram KARAHAN                                    "
                   "\n\n\tkod.pardus.org.tr/karahan/e-tahta"
                   "\n\tgithub.com/bayramkarahan/E-Tahta"
                   "\n\tbayramkarahan.blogspot.com"
                   "\n\tbayramk@gmail.com  "
                    "\n\n   This program is free software; you can redistribute it and/or modify    "
                    "\n   it under the terms of the GNU General Public License as published by    "
                    "\n   the Free Software Foundation; either version 3 of the License, or       "
                    "\n   (at your option) any later version.                                     "
                    "\n                                                                           "
                    "\n   This program is distributed in the hope that it will be useful,         "
                    "\n   but WITHOUT ANY WARRANTY; without even the implied warranty of          "
                    "\n   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           "
                    "\n   GNU General Public License for more details.                            "
                    "\n                                                                           "
                    "\n   You should have received a copy of the GNU General Public License       "
                    "\n   along with this program; if not, write to the                          "
                    "\n   Free Software Foundation, Inc.,                                         "
                    "\n   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .          "

                   );
    msgBox.setWindowTitle("E-Tahta 1.8.8");
    QFont ff( "Arial", 10, QFont::Normal);
    msgBox.setFont(ff);


    msgBox.setStandardButtons(QMessageBox::Ok);
    Qt::WindowFlags flags = 0;
    flags |= Qt::Window;
    flags |= Qt::X11BypassWindowManagerHint;
    flags |= Qt::CustomizeWindowHint;
    this->setWindowFlags(flags);

    flags = 0;
    flags |= Qt::Window;

    //  QColorDialog abc;
    msgBox.setWindowFlags(flags);



    //msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.exec();
    //   kalemEgitim();
    flags |= Qt::Window;
    flags |= Qt::X11BypassWindowManagerHint;
    flags |= Qt::WindowStaysOnTopHint;
    this->setWindowFlags(flags);
    show();


}
void MainWindow::saveButtonClick(){
    QSize sSize = qApp->screens()[0]->size();
    QGraphicsTextItem *text = new QGraphicsTextItem(".");
    scene->addItem(text);
    text->setPos(0, 0);
    QGraphicsTextItem *text1 = new QGraphicsTextItem(".");
    scene->addItem(text1);
    text1->setPos(sSize.width()-2, sSize.height()-2);

    QPixmap pixmap(sSize.width(),sSize.height());
    pixmap.fill(Qt::transparent);     // Start all pixels transparent
    ///pixmap.fill(Qt::white);     // Start all pixels white
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter); //scene.render
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.end();
    QString os="";
    #ifdef WIN32
    // Windows code here
        os="windows";
    #else
    // UNIX code here
        os="linux";
    #endif

        if(os=="linux"){
        QDir directory(QDir::homePath()+"/Masaüstü");
        QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
        int deger=0;
        foreach(QString filename, images) {
            filename.chop(4);
            QString dosya=filename.right(filename.size()-10);
           /// qDebug() <<filename<<dosya;
            if(deger<dosya.toInt()) deger=dosya.toInt();
        }
        deger++;
        pixmap.save(QDir::homePath()+"/Masaüstü/screenshot"+QString::number(deger)+".png");
    }
     else{//windows işletim sistemi için
        QDir directory(QDir::homePath()+"/desktop");
        QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
        int deger=0;
        foreach(QString filename, images) {
            filename.chop(4);
            QString dosya=filename.right(filename.size()-10);
          ///  qDebug() <<filename<<dosya;
            if(deger<dosya.toInt()) deger=dosya.toInt();
        }
        deger++;
        pixmap.save(QDir::homePath()+"/desktop/screenshot"+QString::number(deger)+".png");

        }

    Qt::WindowFlags flags = 0;
    flags |= Qt::Dialog;
    flags |= Qt::X11BypassWindowManagerHint;

    QMessageBox messageBox(this);
    messageBox.setWindowFlags(flags);
    messageBox.setText("Bilgi\t\t\t");
    messageBox.setInformativeText("Ekran Görüntüsü Masaüstünüze Kaydedildi!");
    QAbstractButton *evetButton =messageBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
   // QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
    messageBox.setIcon(QMessageBox::Information);
            messageBox.exec();


}
void MainWindow::openButtonClick(){

    Qt::WindowFlags flags = 0;
    flags |= Qt::Window;
    flags |= Qt::X11BypassWindowManagerHint;
    flags |= Qt::CustomizeWindowHint;
    this->setWindowFlags(flags);

    QFileDialog abc;
   /// abc.setSidebarUrls(urls);
    abc.setFileMode(QFileDialog::AnyFile);

    flags |= Qt::SplashScreen;
    flags |= Qt::X11BypassWindowManagerHint;
    flags |= Qt::WindowStaysOnTopHint;
    // QFileDialog abc;
    abc.setWindowFlags(flags);
    QString os="";
#ifdef WIN32
    // Windows code here
    os="windows";
#else
    // UNIX code here
    os="linux";
#endif

    if(os=="linux"){
        //qDebug()<<"linux fileopen";
        abc.setWindowTitle("Resim Aç jpg png bmp");
        abc.setDirectory(QDir::homePath()+"/Masaüstü");
        abc.setNameFilter(tr("Image Files (*.png *.jpg *.bmp)"));
        if(abc.exec()) {
            if(abc.selectedFiles()[0]!="")
            {
                QPixmap image = QPixmap(abc.selectedFiles()[0]).scaled(this->width()*0.99,this->height()*0.99);
                scene->setBackgroundBrush(image);
            }
        }

    }
    else
    {
        //qDebug()<<"windows fileopen";
        abc.setWindowTitle("Resim Aç jpg png bmp");
        abc.setDirectory(QDir::homePath()+"/desktop");
        abc.setNameFilter(tr("Image Files (*.png *.jpg *.bmp)"));
        if(abc.exec()) {
            if(abc.selectedFiles()[0]!="")
            {
                QPixmap image = QPixmap(abc.selectedFiles()[0]).scaled(this->width()*0.99,this->height()*0.99);
                scene->setBackgroundBrush(image);
            }
        }

    }

    flags |= Qt::Window;
    flags |= Qt::X11BypassWindowManagerHint;
    flags |= Qt::WindowStaysOnTopHint;
    this->setWindowFlags(flags);
    show();
}
void MainWindow::buttonColorClear(){
    palette->setColor(QPalette::Button, QColor(212,0,0,0));
    silButton->setPalette(*palette);
    silButton->setAutoFillBackground(true);
    silPopButton->setPalette(*palette);
    silPopButton->setAutoFillBackground(true);
    kalemButton->setPalette(*palette);
    kalemButton->setAutoFillBackground(true);
    kalemMenuButton->setPalette(*palette);
    kalemMenuButton->setAutoFillBackground(true);
    kalemPopButton->setPalette(*palette);
    kalemPopButton->setAutoFillBackground(true);

    fosforluKalemButton->setPalette(*palette);
    fosforluKalemButton->setAutoFillBackground(true);
    tasiButton->setPalette(*palette);
    tasiButton->setAutoFillBackground(true);
    secButton->setPalette(*palette);
    secButton->setAutoFillBackground(true);
    ekranButton->setPalette(*palette);
    ekranButton->setAutoFillBackground(true);
    gizleGosterButton->setPalette(*palette);
    gizleGosterButton->setAutoFillBackground(true);

    sekilButton->setPalette(*palette);
    sekilButton->setAutoFillBackground(true);
    sekilPopButton->setPalette(*palette);
    sekilPopButton->setAutoFillBackground(true);



}

#endif // BUTTONCLICK_H
