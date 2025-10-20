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

#ifndef FUNCTION_H
#define FUNCTION_H
#include<mainwindow.h>
#include<QMessageBox>

 void MainWindow::promterCloseSignalSlot(QString text)
{

     //qDebug()<<text;
    this->show();
    // zeminBeyazButtonClick();///burada zemin beyaz yapılıyor
    // View boyutu
    QSize viewSize = view->viewport()->size();
    currentScreenModeSlot();
    //Scene::Mode tempMode=currentScreenMode;
    scene->setMode(Scene::Mode::SelectObject, DiagramItem::DiagramType::NoType);
    //scene->setMode(tempMode,mySekilType);
    secButtonClick();
    DiagramTextItem* itemToTextDraw = new DiagramTextItem(nullptr);
    itemToTextDraw->setPlainText(text);
    itemToTextDraw->myTextColor=scene->myPenColor;
    itemToTextDraw->myBackgroundColor=scene->mySekilZeminColor;
    itemToTextDraw->setDefaultTextColor(scene->myPenColor);
    // Yazı düzenlemeyi etkinleştir
    // Seçilebilir ve odaklanabilir
    itemToTextDraw->setFlag(QGraphicsItem::ItemIsSelectable);
    itemToTextDraw->setFlag(QGraphicsItem::ItemIsFocusable);// 🔹 Odak alabilir
    itemToTextDraw->setTextInteractionFlags(Qt::TextEditorInteraction);

    itemToTextDraw->setFocus();                              // 🔹 Hemen odak ver
    // Varsayılan olarak seçili yap
    itemToTextDraw->setSelected(true);
    scene->graphicsList.append(itemToTextDraw);
    itemToTextDraw->setZValue(1000.0);
    scene->graphicsListTemp.append(itemToTextDraw);
    scene->graphicsListpoints.append(itemToTextDraw);

    // Fontu ayarla
    QFont font;
    font.setPointSize(myPenSize*6);
    itemToTextDraw->setFont(font);

    // Sahneye ekle
    scene->addItem(itemToTextDraw);

    // Yazıyı ekranın ortasına konumlandır
    QRectF textRect = itemToTextDraw->boundingRect();
    if(textRect.width()<10)
    {
    itemToTextDraw->setPos(
        (viewSize.width())  / 2,
        (viewSize.height()) / 2
        );
    }
    else
    {
        itemToTextDraw->setPos(
            (viewSize.width()  - textRect.width())  / 2,
            (viewSize.height() - textRect.height()) / 2
            );
    }
   // qDebug()<<textRect.width()<<textRect.height();
    view->setFocusPolicy(Qt::StrongFocus);
    view->setFocus();
 }
void MainWindow::timerGizleSlot()
{
    gizleGoster=true;
    gizleGosterButtonClick();
    timerGizle->stop();


//=!gizleGoster;
//qDebug()<<"gizle";
}
void MainWindow::loading()
{
/*gif_anim = new QLabel(this);
QMovie *movie = new QMovie(":icons/loading.gif");
gif_anim->setMovie(movie);
gif_anim->resize(boy*6,boy*4);
movie->setScaledSize(QSize(boy*6,boy*4));
gif_anim->move(this->width()/2-boy*1.5,this->height()/2-boy);

movie->start();*/
//gif_anim->hide();
}
void MainWindow::initPen()
{
    //ekliSayfa=3;
    //pdfPageCount=53;

 QSize screenSize = qApp->screens()[0]->size();
    /****************************************/
   // QDesktopWidget widget;
   // mainScreenSize = widget.availableGeometry(widget.primaryScreen());
    setGeometry(0,0,screenSize.width(),screenSize.height());
//    currentGeometry = this->geometry();
//    qDebug()<<"mainscreen"<<mainScreenSize;
    tasi=false;
    boy=(screenSize.height()/100)*5.70;

   //qDebug()<<"boy"<<boy;
    en=boy;
   // boy=40;
    //en=40;
    kutuHeight=boy*18.0;
    kutuWidth=en*1;

     myZeminType=0;
    FileCrud *fc=new FileCrud();
    fc->dosya="e-tahta.ini";
   if((fc->fileexists()))
    {
        QString strmyPenAlpha=fc->fileSearch("myPenAlpha");strmyPenAlpha.chop(1);
        QStringRef _strmyPenAlpha=strmyPenAlpha.rightRef(strmyPenAlpha.length()-11);
       // qDebug()<<_strmyPenAlpha;

        QString strmyPenColor=fc->fileSearch("myPenColor");strmyPenColor.chop(1);
        QStringRef _strmyPenColor=strmyPenColor.rightRef(strmyPenColor.length()-11);
      // qDebug()<<_strmyPenColor;

        QString strmyPenSize=fc->fileSearch("myPenSize");strmyPenSize.chop(1);
        QStringRef _strmyPenSize=strmyPenSize.rightRef(strmyPenSize.length()-10);
       // qDebug()<<_strmyPenSize;

        QString strmyGridSize=fc->fileSearch("myGridSize");strmyGridSize.chop(1);
        QStringRef _strmyGridSize=strmyGridSize.rightRef(strmyGridSize.length()-11);
        //qDebug()<<_strmyGridSize;

        QString strmyEraseSize=fc->fileSearch("myEraseSize");strmyEraseSize.chop(1);
        QStringRef _strmyEraseSize=strmyEraseSize.rightRef(strmyEraseSize.length()-12);
       // qDebug()<<_strmyEraseSize;

        QString strmyPenStyle=fc->fileSearch("myPenStyle");strmyPenStyle.chop(1);
        QStringRef _strmyPenStyle=strmyPenStyle.rightRef(strmyPenStyle.length()-11);
        //qDebug()<<_strmyPenStyle;

        QString strmySekilPenStyle=fc->fileSearch("mySekilPenStyle");strmySekilPenStyle.chop(1);
        QStringRef _strmySekilPenStyle=strmySekilPenStyle.rightRef(strmySekilPenStyle.length()-16);
        //qDebug()<<_strmySekilPenStyle;

        QString strmySekilZeminColor=fc->fileSearch("mySekilZeminColor");strmySekilZeminColor.chop(1);
        QStringRef _strmySekilZeminColor=strmySekilZeminColor.rightRef(strmySekilZeminColor.length()-18);
       // qDebug()<<_strmySekilZeminColor;

        QString strmySekilKalemColor=fc->fileSearch("mySekilKalemColor");strmySekilKalemColor.chop(1);
        QStringRef _strmySekilKalemColor=strmySekilKalemColor.rightRef(strmySekilKalemColor.length()-18);
        //qDebug()<<_strmySekilKalemColor;

        QString strmyGridColor=fc->fileSearch("myGridColor");strmyGridColor.chop(1);
        QStringRef _strmyGridColor=strmyGridColor.rightRef(strmyGridColor.length()-12);
        //qDebug()<<_strmyGridColor;

        QString strmyZeminColor=fc->fileSearch("myZeminColor");strmyZeminColor.chop(1);
        QStringRef _strmyZeminColor=strmyZeminColor.rightRef(strmyZeminColor.length()-13);
       // qDebug()<<_strmyZeminColor;

        QString strmySekilPenSize=fc->fileSearch("mySekilPenSize");strmySekilPenSize.chop(1);
        QStringRef _strmySekilPenSize=strmySekilPenSize.rightRef(strmySekilPenSize.length()-15);
//        qDebug()<<_strmySekilPenSize;

        QString strmyZeminType=fc->fileSearch("myZeminType");strmyZeminType.chop(1);
        QStringRef _strmyZeminType=strmyZeminType.rightRef(strmyZeminType.length()-12);
       // qDebug()<<_strmyZeminType;

        QString strgridYatay=fc->fileSearch("gridYatay");strgridYatay.chop(1);
        QStringRef _strgridYatay=strgridYatay.rightRef(strgridYatay.length()-10);
        //qDebug()<<_strgridYatay;

        QString strgridDikey=fc->fileSearch("gridDikey");strgridDikey.chop(1);
        QStringRef _strgridDikey=strgridDikey.rightRef(strgridDikey.length()-10);
//        qDebug()<<_strgridDikey;

        QString strclock=fc->fileSearch("clock");strclock.chop(1);
        QStringRef _strclock=strclock.rightRef(strclock.length()-6);
        //        qDebug()<<_strclock;
        QString strkutuTop=fc->fileSearch("kutuTop");strkutuTop.chop(1);
        QStringRef _strkutuTop=strkutuTop.rightRef(strkutuTop.length()-8);
        //        qDebug()<<_strkutuTop;
        QString strkutuLeft=fc->fileSearch("kutuLeft");strkutuLeft.chop(1);
        QStringRef _strkutuLeft=strkutuLeft.rightRef(strkutuLeft.length()-9);
//        qDebug()<<_strkutuLeft;
        QString strcopyState=fc->fileSearch("copyState");strcopyState.chop(1);
        QStringRef _strcopyState=strcopyState.rightRef(strcopyState.length()-10);
//        qDebug()<<_strcopyState;

        QString strwsolVisible=fc->fileSearch("wsolVisible");strwsolVisible.chop(1);
        QStringRef _strwsolVisible=strwsolVisible.rightRef(strwsolVisible.length()-12);
//        qDebug()<<_strwsolVisible;

        myPenAlpha=_strmyPenAlpha.toInt();
        myPenColor.setNamedColor(_strmyPenColor.toString());
        myPenSize=_strmyPenSize.toInt();
        myGridSize=_strmyGridSize.toInt();
        myEraseSize=_strmyEraseSize.toInt();
        myPenStyle=Qt::PenStyle(_strmyPenStyle.toInt());
        mySekilPenStyle=Qt::PenStyle(_strmySekilPenStyle.toInt());
        mySekilZeminColor.setNamedColor(_strmySekilZeminColor.toString());
        mySekilKalemColor.setNamedColor(_strmySekilKalemColor.toString());
        myGridColor.setNamedColor(_strmyGridColor.toString());
        mySekilPenSize=_strmySekilPenSize.toInt();
        myZeminColor.setNamedColor(_strmyZeminColor.toString());
        myZeminType=_strmyZeminType.toInt();
        scene->sceneGridYatay=_strgridYatay.toInt();
        scene->sceneGridDikey=_strgridDikey.toInt();
       // myZeminColor.setAlpha(0);
        mySekilZeminColor.setAlpha(0);
        clock=_strclock.toInt();

        kutuTop=_strkutuTop.toInt();
        kutuLeft=_strkutuLeft.toInt();
        copyState=_strcopyState.toInt();
        wsolVisible=_strwsolVisible.toInt();

        if (_strkutuLeft=="")
                kutuLeft=screenSize.width()-kutuWidth-screenSize.width()/100;

      // qDebug()<<"check"<<_strkutuLeft;

      /*  gridLines = new GridLines (this->width(), this->height(),myPenSize*10,gridYatay,gridDikey,myZeminColor, QColor(128,128,128,255));
        QPixmap bkgnd=gridLines->PixItem(gridLines,mainScreenSize.width(),mainScreenSize.height());
        this->setAttribute(Qt::WA_TranslucentBackground, false);
        this->setAttribute(Qt::WA_NoSystemBackground, false);
        this->repaint();
        QPalette palet;
        palet.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palet);
*/
    }
else{


    myPenAlpha=255;
    myPenColor=QColor(0,0,0,255);
    myPenSize=4;
    myGridSize=3;
    myEraseSize=3;
    myPenStyle=Qt::SolidLine;
    mySekilPenStyle=Qt::SolidLine;
    mySekilZeminColor=QColor(0,0,0,0);
    mySekilKalemColor=QColor(0,0,0,255);
    myGridColor=QColor(128,128,128,128);
    mySekilPenSize=3;
    myZeminColor=QColor(0,0,0,0);
    scene->sceneGridYatay=false;
    scene->sceneGridDikey=false;
    scene->sceneGuzelYazi=false;
    clock=true;
    myZeminType=0;

    kutuLeft=screenSize.width()-kutuWidth-screenSize.width()/100;
    kutuTop=(screenSize.height() /2-kutuHeight*0.53);
    copyState=false;
    wsolVisible=false;
}
   gizleGoster=true;
   screenDesktop=true;

    if(myZeminType==0) zeminSeffafButtonClick();
    if(myZeminType==1) zeminSiyahButtonClick();
    if(myZeminType==2) zeminBeyazButtonClick();
    if(myZeminType==3) zeminCustomColorInitButtonClick();
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setAttribute(Qt::WA_NoSystemBackground, false);
    //this->setAttribute(Qt::WA_NoBackground,true);
    this->repaint();



     sceneSayfaActiveNumber=0;
    sceneSayfaNumber=0;

     //qDebug() <<"Başlangıç Ayarları Yapıldı..";
}

void MainWindow::currentScreenModeSlot()
{
    //iconButton();
    //buttonColorClear();

    if(screenDesktop==false) ekranButtonClick();

    if(screenClickDrm) screenClickButtonClick();

    if(gizleGoster==false&&screenDesktop)
    {
        timerGizle->stop();
      //  qDebug()<<"dur"<<gizleGoster<<screenDesktop;
    }
        else
    {
        timerGizle->start(15000);
      //  qDebug()<<"çalış"<<gizleGoster<<screenDesktop;
    }


    palette->setColor(QPalette::Button, QColor(212,0,0,255));
    penWriteStatus=false;
    view->setEnabled(true);
    view->show();
    QPalette palet;
    palet.setBrush(QPalette::Background,QColor(0,0,0,0));
    this->setPalette(palet);


    if(currentScreenMode==Scene::Mode::DrawRectangle)
    {
        sekilButton->setPalette(*palette);
        sekilButton->setAutoFillBackground(true);
        sekilPopButton->setPalette(*palette);
        sekilPopButton->setAutoFillBackground(true);
    }
    if(currentScreenMode==Scene::Mode::EraseMode)
    {
        silButton->setPalette(*palette);
        silButton->setAutoFillBackground(true);
        silPopButton->setPalette(*palette);
        silPopButton->setAutoFillBackground(true);

      /*  QPixmap ppp(":/icons/erase.png");
        QPixmap pppResult;
        pppResult = ppp.transformed(QTransform());
        setCursor(pppResult.scaled(myEraseSize*5,myEraseSize*5,Qt::KeepAspectRatio));
*/
    }
    if(currentScreenMode==Scene::Mode::SelectObject)
    {
        secButton->setPalette(*palette);
        secButton->setAutoFillBackground(true);

    }
    if(currentScreenMode==Scene::Mode::DrawPen)
    {
        kalemButton->setPalette(*palette);
        kalemButton->setAutoFillBackground(true);
        kalemMenuButton->setPalette(*palette);
        kalemMenuButton->setAutoFillBackground(true);
        kalemPopButton->setPalette(*palette);
        kalemPopButton->setAutoFillBackground(true);

        if(!scene->mySekilTanimlamaStatus)//akıllı kalem için kontrol yapılıyor
        {
            QPixmap pixMap = view->grab(view->sceneRect().toRect());
            QPalette palet;
            palet.setBrush(QPalette::Background,pixMap);
            this->setPalette(palet);
            penWriteStatus=true;
            view->setEnabled(false);
            view->hide();

        }


/*
        QPixmap ppp(":/icons/pen.png");
        QPixmap pppResult;
        pppResult = ppp.transformed(QTransform());
        setCursor(pppResult.scaled(myPenSize*5,myPenSize*5,Qt::KeepAspectRatio));
*/

    }
    if(currentScreenMode==Scene::Mode::CopyMode)
    {
       // kalemButton->setPalette(*palette);
       // kalemButton->setAutoFillBackground(true);

    }
    if(currentScreenMode==Scene::Mode::SelectObject)
    {
        secButton->setPalette(*palette);
        secButton->setAutoFillBackground(true);
    }
    if(currentScreenMode==Scene::Mode::GeriAlMode)
    {
        //if(Scene::graphicsListHistoryBack.count()==0)geriAlButton->setEnabled(false);
    }
    if(currentScreenMode==Scene::Mode::IleriAlMode)
    {

    }

     //   ekranButton->setIcon(QIcon(":icons/screenpen.png"));
       //   ekranButton->setPalette(*palette);
        //ekranButton->setAutoFillBackground(true);
    scene->setMode(currentScreenMode,mySekilType);

}

void MainWindow::setZeminColor(const QColor &newColor)
{
    myZeminColor = QColor(newColor.red(),newColor.green(),newColor.blue(),myPenAlpha);
    palette->setColor(QPalette::Button, myZeminColor);
}

void MainWindow::setPenColor(const QColor &newColor){
    myPenColor = QColor(newColor.red(),newColor.green(),newColor.blue(),myPenAlpha);
    palette->setColor(QPalette::Button, myPenColor);
    mySekilKalemColor=myPenColor;
     scene->setSekilKalemColor(mySekilKalemColor);
//    colorButton->setPalette(*palette);
  //  colorButton->update();
    kalemRenkButton->setPalette(*palette);
    kalemRenkButton->update();

    scene->setPenColor(myPenColor);
}
void MainWindow::setPenAlpha(int size)
{   myPenAlpha=size;
    scene->setPenAlpha(myPenAlpha);
}

void MainWindow::setPenStyle(const Qt::PenStyle &styl){
    myPenStyle=styl;
    scene->setPenStyle(myPenStyle);
}

void MainWindow::setSekilType(const DiagramItem::DiagramType &typ){
    mySekilType=typ;
   // scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType(typ));
    sekilButtonClick();

  }
void MainWindow::setPenSize(int size)
{
  //  int t = size * 2 - 1;
    this->myPenSize = size*2-1;
 //   this->myPenSize = t;-
    kalemSizePopLabel->setText("Kalem Boyutu: "+QString::number(myPenSize)+"\t\t");
    scene->setPenSize(this->myPenSize);
    kalemButtonClick();
}

void MainWindow::setSekilPenSize(int size)
{
    int t = size * 2 - 1;
    this->mySekilPenSize = t;
    sekilKalemSizePopLabel->setText("Şekil Kalem Boyutu: "+QString::number(mySekilPenSize)+"\t\t");
    scene->setSekilPenSize(mySekilPenSize);
    sekilButtonClick();
}
void MainWindow::setSekilPenStyle(const Qt::PenStyle &styl)
{
    mySekilPenStyle=styl;
    scene->setSekilPenStyle(mySekilPenStyle);
}
void MainWindow::setGridSize(int size)
{
    int t = size * 2 - 1;
    this->myGridSize = t;
     gridSizePopLabel->setText("Grid Boyutu: "+QString::number(myGridSize)+"\t\t");
    /// qDebug()<<"size:"<<myGridSize;
     if(scene->sceneGridYatay) gridYatayButtonClick(scene->sceneGridYatay);
     if(scene->sceneGridDikey) gridDikeyButtonClick(scene->sceneGridDikey);
     if(scene->sceneGuzelYazi) zeminGuzelYaziButtonClick(scene->sceneGuzelYazi);

}
void MainWindow::setEraseSize(int size)
{
        int t = size;
        this->myEraseSize = t;
        eraseSizePopLabel->setText("Silgi Boyutu: "+QString::number(myEraseSize)+"\t\t");
        scene->setEraseSize(myEraseSize);
        silButtonClick();
}
void MainWindow::zamanlama()
{
   /// loading();
    QTime time1 = QTime::currentTime();
    if(clock)
    {
        QFont ff( "Arial", 8, QFont::Bold);
        clockButton->setFont(ff);

    QString text = time1.toString("hh:mm");
    clockButton->setText(text);
    }else
    {
        QFont ff( "Arial", 7, QFont::Bold);
        clockButton->setFont(ff);
        clockButton->setText("E-Tahta");
    }
    if(depo::historyBackCount>0)
    {
       if(geriAlButton)
        geriAlButton->setEnabled(true);
    }
    else
    {
        if(geriAlButton)
         geriAlButton->setEnabled(false);
    }
    if(depo::historyNextCount>0)
    {
       if(ileriAlButton)
        ileriAlButton->setEnabled(true);
    }
    else
    {
        if(ileriAlButton)
         ileriAlButton->setEnabled(false);
    }

    /******************************************/

    /******************************************/


    if ((time1.second() % 5) == 0){
       /// qDebug()<<"ekran işlemm";


if(zamanlamastart!=0)
{
     /* QSize sSize = qApp->screens()[0]->size();
      QGraphicsTextItem *text = new QGraphicsTextItem(".");
      scene->addItem(text);
      text->setPos(0, 0);
      QGraphicsTextItem *text1 = new QGraphicsTextItem(".");
      scene->addItem(text1);
      text1->setPos(sSize.width()-2, sSize.height()-2);
     //}

      QPixmap pixmap(sSize.width(),sSize.height());
      pixmap.fill(Qt::transparent);     // Start all pixels transparent
      ///pixmap.fill(Qt::white);     // Start all pixels transparent
      QPainter painter(&pixmap);
      painter.setRenderHint(QPainter::Antialiasing);
      scene->render(&painter); //scene.render
      painter.setRenderHint(QPainter::Antialiasing, false);
      painter.end();*/
    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    pageList[sceneSayfaActiveNumber]->setIcon(QIcon(pixMap));////önemli
}
zamanlamastart=1;
}


    //if(depo::historyNextCount>0) ileriAlButton->setEnabled(true);else ileriAlButton->setEnabled(false);


   // qDebug() <<"zamanlama";
  /*  int acikDosyaSayisi;
    acikDosyaSayisi=0;

    QStringList arguments;
    arguments << "-c" << "ps -aux|grep '.odp\\|.otp\\|.pps\\|.ppsx\\|.ppt\\|.pptx\\|.pdf\\|vlc\\|wine'|wc -l";
    QProcess process;
    process.start("/bin/bash",arguments);
    process.waitForFinished(-1); // will wait forever until finished
    QString stdout = process.readAllStandardOutput();
    // QString stderr = process.readAllStandardError();
    // qDebug()<<stdout;
    acikDosyaSayisi+=stdout.toInt();
    if(screenDesktop==false) acikDosyaSayisi=5;
       if(acikDosyaSayisi>2)
       {
           this->activateWindow();

    }*/

}

void MainWindow::timerCopySlot()
{
    //qDebug()<<"copy timer";
    FileCrud *fc=new FileCrud();
    fc->dosya="E-Tahta.copy.ini";
   if((fc->fileexists()))
    {
        QString strmyPenAlpha=fc->fileSearch("copy");strmyPenAlpha.chop(1);
        QStringRef _strmyPenAlpha=strmyPenAlpha.rightRef(strmyPenAlpha.length()-5);
   //qDebug()<<_strmyPenAlpha;
        if(_strmyPenAlpha=="0")
        {
         // qDebug()<<"kopya başladı";
        }
        if(_strmyPenAlpha=="1")
        {
            /************************************/
            Qt::WindowFlags flags = 0;
            flags |= Qt::Dialog;
            flags |= Qt::X11BypassWindowManagerHint;

            QMessageBox messageBox(this);
            messageBox.setWindowFlags(flags);
            messageBox.setText("Uyarı\t\t\t");
            messageBox.setInformativeText("Yeni Beyaz Sayfada Açılsın mı?");
            QAbstractButton *evetButton =messageBox.addButton(tr("Evet"), QMessageBox::ActionRole);
            QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
            messageBox.setIcon(QMessageBox::Question);
                    messageBox.exec();

            if(copyState==true)
            {
                zeminBeyazButtonClick();
            }else
            {
           /// int ret = msgBox.exec();
            ///if(ret==16384) zeminBeyazButtonClick();
            if (messageBox.clickedButton() == evetButton)

            {
                VERectangle* tempCopyModeItemToRectDraw=scene->tempCopyModeItemToRectDraw;
                ekleSayfaButtonClick(sceneSayfaActiveNumber,false,-1);///yeni scene eklendi değişim yapılacak
                scene->addItem(tempCopyModeItemToRectDraw);
                scene->graphicsList.append(tempCopyModeItemToRectDraw);
                scene->graphicsListTemp.append(tempCopyModeItemToRectDraw);
                scene->historyBack.append(tempCopyModeItemToRectDraw);
                scene->historyBackAction.append("added");
                depo::historyBackCount=scene->historyBack.count();
                depo::historyNextCount=scene->historyNext.count();

                zeminBeyazButtonClick();
            }
            if (messageBox.clickedButton() == hayirButton)
            {
                VERectangle* tempCopyModeItemToRectDraw=scene->tempCopyModeItemToRectDraw;
                scene->addItem(tempCopyModeItemToRectDraw);
                scene->graphicsList.append(tempCopyModeItemToRectDraw);
                scene->graphicsListTemp.append(tempCopyModeItemToRectDraw);
                scene->historyBack.append(tempCopyModeItemToRectDraw);
                scene->historyBackAction.append("added");
                depo::historyBackCount=scene->historyBack.count();
                depo::historyNextCount=scene->historyNext.count();


            }
            }
            FileCrud *fc=new FileCrud();
            fc->dosya="E-Tahta.copy.ini";
            if(fc->fileexists()) fc->fileremove();
            fc->fileWrite("copy=0");
            timerCopy->stop();
        }
   }
}
void MainWindow::saatslot(){
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    //sayac->display(text);
    saniye+=1;
    qDebug()<<saniye;
    int hour=saniye/3600;
     int minute=saniye/60;
     int second=saniye%60;
     int sr=sure->value()*60;

    sayac->setText(QString::number(sure->value()-1-minute)+":"+QString::number(60-second));
bar->setValue(saniye);
//if(minute>(sr*0.3))
//sayac->setStyleSheet("QLabel{size:170px;}");
QFont f( "Arial", 120, QFont::Bold);
sayac->setFont(f);
sayac->setAlignment(Qt::AlignCenter);

sayac->setStyleSheet("QLabel{color: rgb(0, 255, 0);}");
if(saniye>sr*0.33)sayac->setStyleSheet("QLabel{color: rgb(255, 255, 0);}");
if(saniye>0.66*sr)sayac->setStyleSheet("QLabel{color: rgb(255, 0, 0);}");
if(saniye>sr){
    sayac->setText("-00-");
    sayac->setStyleSheet("QLabel{color: rgb(0, 0, 0);}");
}



}

void MainWindow::kalemEgitim()
{

    QMessageBox msgBox;
    /**************** ilk Karşılama Metni ****************/
    msgBox.setText("PardusKalem yazılımı açıldığında bu ekranı görüyorsanız muhtemelen"
                   "ilk defa açıyorusunuzdur. Bu mesajlar bir kaç adımda yazılımın nasıl"
                   "kullanılacağını anlatmaktadır. Eğer bu ekranı tekrar görmek isterseniz info seçeneğinden ulaşabilirsiniz."
                   "<img src=':icons/yazi-info.png' width='512' height='512'/>"
                                "");
    msgBox.setStandardButtons(QMessageBox::Ok);msgBox.exec();

    /**************** Kalemle ilgili Açıklama ****************/
    msgBox.setText("Kalem istenilen renk ve boyuta ayarlanıp kullanılabilmektedir."
                   "Fosforlu kalem ise önemli yerleri göstermek için kullanılan bir seçenektir."
                   "<img src=':icons/yazi-info1.png' width='512' height='512'/>"
                               "");
    msgBox.setStandardButtons(QMessageBox::Ok);msgBox.exec();
    /**************** Zemin Renkleriyle ilgili Açıklama ****************/
    msgBox.setText("Zemin şeffaf, beyaz, siyah veya istenilen herhangi bir renk zeminde kullanılabilir."
                   "Yatay ve dikey çizgiler ekleyebilir ve silinebilir."
                   "Yatay ve dikey çizgi aralığı yazı boyutuna göre ölçülenmektedir."
                   "Müzik dersi ve Güzel Yazı Yazma dersleri için desenleride seçebilir."
                   "<img src=':icons/desen-info.png' width='512' height='512'/>"
                                  "");
    msgBox.setStandardButtons(QMessageBox::Ok);msgBox.exec();
    /**************** Seçimle İlgili Açıklama  ****************/
    msgBox.setText("Yazılar veya nesleler isteğe göre seçilerek taşınabilir veya silinebilir."
                   "Şekiller ise seçilerek büyültme-küçültme, döndürme, taşıma ve silme işlemi yapılabilir."
                   "<img src=':icons/sekil-info.png' width='512' height='512'/>"
                                  "");
    msgBox.setStandardButtons(QMessageBox::Ok);msgBox.exec();

    /**************** Şekillerle İlgili Açıklamalar ****************/
    msgBox.setText("Matematik ve algoritma için kullanılabilen şekiller bulunmaktadır."
                   "Şekiller seçme tuşuyla taşıma, silme, döndürme ve boyutlandırma yapılabilir."
                   "<img src=':icons/sekil-info1.png' width='512' height='512'/>"
                                 "");
    msgBox.setStandardButtons(QMessageBox::Ok);msgBox.exec();

}


QPixmap MainWindow::image(const QPolygonF &myPolygon,int w,int h) const
{
    QPixmap pixmap(w, h);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
  // painter.translate(en, boy);
    painter.drawPolyline(myPolygon);
    return pixmap;
}

QImage MainWindow::zImage(int w, int h, QColor color) const
{
    QImage img(w, h,QImage::Format_ARGB32_Premultiplied);
    img.fill(color);
    QPainter painter(&img);
   // painter.setPen(QPen(color, pensize));
  // painter.translate(en, boy);
   // painter.drawPolyline(myPolygon);
    return img;
}

QPixmap MainWindow::zeminImage(const QPolygonF &myPolygon, int w, int h, QColor color,int pensize) const
{
    QPixmap pixmap(w, h);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(color, pensize));
  // painter.translate(en, boy);
    painter.drawPolyline(myPolygon);
    return pixmap;
}
QPixmap MainWindow::lineImage(const QPolygonF &myPolygon,const Qt::PenStyle &stl,int w,int h) const
{
    QPixmap pixmap(w, h);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8,stl));
  // painter.translate(en, boy);
    painter.drawPolyline(myPolygon);
    return pixmap;
}

QPixmap MainWindow::imageEllipse(const QPolygonF &myPolygon,int w,int h) const
{
    QRectF rectangle(myPolygon[0],myPolygon[1]);
   // QPainter painter(this);
   // painter.drawEllipse(rectangle);
    QPixmap pixmap(w, h);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
  // painter.translate(en, boy);
    painter.drawEllipse(rectangle);
    return pixmap;
}

void MainWindow::sayfaListeIcon()
{
int ss= sayfaListeView->count();
int sr=0;
while(sr<=ss)
{
       //sayfaListeView->removeItemWidget(sayfaListeView->item(sayfaListeView->currentRow()));
    sayfaListeView->clear();
    sr++;
}

//sayfaListeView->clear();
    qDebug()<<"sayfa izle";
    QSize screenSize = qApp->screens()[0]->size();

    /*******************scene fotosunu çekiyor fakat transparan********************/
      //  setGeometry(mainScreenSize);
    QImage img(screenSize.width(),screenSize.height(),QImage::Format_ARGB32_Premultiplied);
    QPainter p(&img);
    //scene->update();
    scene->render(&p);
    p.end();
    sayfaListeView->addItem(new QListWidgetItem(QIcon(QPixmap::fromImage(img)), ""));

   // sayfaListeView->addItem(new QListWidgetItem(QIcon(":/icons/goster.png"),""));
 //   sayfaListeView->addItem(new QListWidgetItem(QIcon(":/icons/gizle.png"),""));
 //sayfaListeView->update();
    }
void MainWindow::pageButtonClick(int index)
{
    sceneSayfaActiveNumber=index;;
    clearImage();
    scene=sceneSayfa[sceneSayfaActiveNumber];
    view->setScene(scene);
//
  ///  qDebug()<<"ekle button click"<<sceneSayfaNumber<<sceneSayfaActiveNumber<<scene->pdfObjectAdded<<scene->pdfObjectShow<<scene->pdfPageNumber;

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

    for(int i=0;i<pageList.length();i++)
    {
        palette->setColor(QPalette::Button, QColor(225,225,225,100));
        pageList[i]->setPalette(*palette);
        pageList[i]->setAutoFillBackground(true);

    }
    palette->setColor(QPalette::Button, QColor(255,0,0,100));
    pageList[index]->setPalette(*palette);
    pageList[index]->setAutoFillBackground(true);
    if(scene->pdfObjectAdded&&scene->pdfObjectShow==false&&scene->pdfPageNumber<=pdfPageCount-1) pdfLoaderPage(scene->pdfPageNumber);///pdf page loader
    currentScreenModeSlot();


}

void MainWindow::pdfLoaderPage(int pageIndex)
{
   // qDebug()<<"pdf loader function"<<pageIndex;
     zeminBeyazButtonClick();///burada zemin beyaz yapılıyor

     //  QImage image = doc->page(pageIndex)->renderToImage(125.0,125.0,-1,-1,-1,-1);
     QImage image = doc->page(pageIndex)->renderToImage(150.0,150.0,doc->page(pageIndex)->pageSize().width(),doc->page(pageIndex)->pageSize().height());

    ///  view->setSceneRect(0,0,image.width(),image.height());
     VERectangle*  itemToRectDraw = new VERectangle(scene);
    itemToRectDraw->sekilTur(DiagramItem::DiagramType::Pdf);
    itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
     itemToRectDraw->setPos(QPoint(this->width()/8,0));

     itemToRectDraw->setBrush(mySekilZeminColor);
     QPixmap tmp(image.width(),image.height());
     tmp.fill(QColor(mySekilZeminColor));
     QPainter painter(&tmp);
     painter.drawImage(QPoint{}, image, image.rect());
     painter.end();

     itemToRectDraw->setImage(tmp);

    scene->addItem(itemToRectDraw);

    scene->graphicsList.append(itemToRectDraw);
    scene->graphicsListTemp.append(itemToRectDraw);
    scene->historyBack.append(itemToRectDraw);
    scene->historyBackAction.append("added");

    depo::historyBackCount=scene->historyBack.count();
    depo::historyNextCount=scene->historyNext.count();

    itemToRectDraw->setRect(0,0,this->width()/4*3,this->height());

    itemToRectDraw->fareState(false);
    itemToRectDraw->setZValue(-200);
    scene->makeItemsControllable(false);
    scene->pdfObjectShow=true;
    //itemToRectDraw->fareState(true);
    itemToRectDraw = 0;
    //secButtonClick();
scene->update();
 currentScreenModeSlot();

}

#endif // FUNCTION_H
