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

#ifndef KALEMLAYOUT_H
#define KALEMLAYOUT_H
//#include<mainwindow.h>
#include<diagramitem.h>
#include<QPushButton>
#include<QDateTime>
#include<toolpromter.h>


void MainWindow::kalemLayout()
{

auto layout = new QGridLayout();
layout->setContentsMargins(1,0, 0,0);
layout->setSpacing(1);
float c=1;
float cc=0.7;
float b=0.7;
clockButton=new QPushButton(this);
clockButton->setFixedSize(en*c, boy/2);
clockButton->setFlat(true);
clockButton->setStyleSheet("QPushButton{color: rgb(62, 140, 183);}");
 zamanlama();
connect(clockButton, &QPushButton::clicked, [=]() {

    clock=!clock;
    zamanlama();
   });

layout->addWidget(clockButton, 0, 0,1,2);
//colorButton->setFixedSize(en*c, boy*0.5);
//colorButton->setIconSize(QSize(en*cc,boy*0.5));
//layout->addWidget(colorButton, 1, 0,1,2);

ekranButton->setFixedSize(en*c, boy*b);
ekranButton->setIconSize(QSize(en*cc,boy*b));

layout->addWidget(ekranButton, 3, 0,1,2);
secButton->setFixedSize(en*c, boy*b);
secButton->setIconSize(QSize(en*cc,boy*b));

layout->addWidget(secButton, 4, 0,1,2);
/***************************************************************/


copyButton = new QPushButton(this);
copyButton->setIcon(QIcon(":icons/copy.png"));
copyButton->setFixedSize(en*c, boy*b);
copyButton->setIconSize(QSize(en*cc,boy*b));
copyButton->setFlat(true);
//copyButton->hide();
//copyButton->move(this->width()/2-en,this->height()-boy-10);
connect(copyButton, &QPushButton::clicked, [=]()
{ ///qDebug()<<"kopy kalem çalıştı"<<screenDesktop;
//if (!screenDesktop)kalemButtonClick();
 scene->makeItemsControllable(false);
    scene->setMode(Scene::Mode::CopyMode, DiagramItem::DiagramType::Copy);
    currentScreenMode=Scene::Mode::CopyMode;
    iconButton();
    buttonColorClear();
    scene->setSekilTanimlamaStatus(false);
     palette->setColor(QPalette::Button, QColor(212,0,0,255));
     secButton->setPalette(*palette);
     secButton->setAutoFillBackground(true);
             QSize screenSize = qApp->screens()[0]->size();
     QPixmap desk = qApp->screens().at(0)->grabWindow(
     QDesktopWidget().winId(),
    0,
    0,
     screenSize.width(),
     screenSize.height());
     scene->setImage(desk);
     timerCopy->start(1000);
     /*****************************/
     FileCrud *fc=new FileCrud();
     fc->dosya="E-Tahta.copy.ini";
     if(fc->fileexists()) fc->fileremove();
     fc->fileWrite("copy=0");
currentScreenModeSlot();
     /**********************************/
});
layout->addWidget(copyButton, 5, 0,1,2);
/***************************************************************/
temizleButton->setFixedSize(en*c, boy*b);
temizleButton->setIconSize(QSize(en*cc,boy*b));

layout->addWidget(temizleButton, 7,0,1,2);
//layout->addWidget(geriAlButton, 7, 0,1,1);
siyahButton->setFixedSize(en*c, boy*0.5);
//siyahButton->setIconSize(QSize(en*0.75,boy*0.5));

layout->addWidget(siyahButton, 8, 0,1,2);
kirmiziButton->setFixedSize(en*c, boy*0.5);
//kirmiziButton->setIconSize(QSize(en*0.75,boy*0.5));

layout->addWidget(kirmiziButton, 9, 0,1,2);
//kalemRenkButton->setFixedSize(en*c, boy*0.5);
kalemRenkButton->setFixedSize(en*c, boy*b);
kalemRenkButton->setIconSize(QSize(en*c,boy*b));

//yesilButton->setIconSize(QSize(en*0.75,boy*0.5));

layout->addWidget(maviButton, 10, 0,1,2);
maviButton->setFixedSize(en*c, boy*0.5);
//maviButton->setIconSize(QSize(en*0.75,boy*0.5));

layout->addWidget(kalemRenkButton, 11, 0,1,2);
/******************************************************/

ileriAlButton->setIcon(QIcon(":icons/redo.png"));
ileriAlButton->setFixedSize(en*c/2, boy*b);
ileriAlButton->setIconSize(QSize(en*cc*0.6,boy*b));
ileriAlButton->setFlat(true);
connect(ileriAlButton, &QPushButton::clicked, [=]()
{currentScreenModeSlot();
    Scene::Mode tempMode=currentScreenMode;
 scene->setMode(Scene::Mode::IleriAlMode, DiagramItem::DiagramType::NoType);
     scene->setMode(tempMode,mySekilType);

});
/*************************************************************/
//layout->addWidget(kalemSizePopLabel, 0, 1,1,3);
geriAlButton->setFixedSize(en*c/2, boy*b);
geriAlButton->setIconSize(QSize(en*cc*0.6,boy*b));
layout->addWidget(geriAlButton,12,0,1,1);
layout->addWidget(ileriAlButton,12,1,1,1);

kalemButton->setFixedSize(en*c/2, boy*b);
kalemButton->setIconSize(QSize(en*cc*0.7,boy*b));
kalemPopButton->setFixedSize(en*c/2, boy*b);
kalemPopButton->setIconSize(QSize(en*cc*0.7,boy*b));

layout->addWidget(kalemButton, 14, 0,1,1);
layout->addWidget(kalemPopButton,14,1,1,1);
QMenu *kalemMenus=penMenu();
kalemMenus->show();kalemMenus->hide();

//kalemPopButton->setMenu(penMenu(SLOT(kalemPopButton()), DiagramItem::DiagramType::Cizgi));
connect(kalemPopButton, &QPushButton::clicked, [=]() {//en*6+en/10
    currentScreenModeSlot();
    scene->setPopMenuStatus(true);
    kalemMenus->exec(mapToGlobal(kalemPopButton->pos() + QPoint(kutuLeft-kalemMenus->width()-kutuWidth/2,kutuTop+boy/2)));
    scene->setPopMenuStatus(false);
});
  gizleGosterButton->setIcon(QIcon(":icons/gizle.png"));
silButton->setFixedSize(en*c/2, boy*b);
silButton->setIconSize(QSize(en*cc*0.7,boy*b));

silPopButton->setFixedSize(en*c/2, boy*b);
silPopButton->setIconSize(QSize(en*cc*0.7,boy*b));

layout->addWidget(silButton, 18,0,1,1);
layout->addWidget(silPopButton, 18,1,1,1);
QMenu *silMenus=eraseMenu();
silMenus->show();silMenus->hide();

//silPopButton->setMenu(eraseMenu(SLOT(silPopButton()), DiagramItem::DiagramType::Cizgi));
connect(silPopButton, &QPushButton::clicked, [=]() {
       currentScreenModeSlot();
       scene->setPopMenuStatus(true);
      silMenus->exec(mapToGlobal(silPopButton->pos() + QPoint(kutuLeft-silMenus->width()-kutuWidth/2,kutuTop+boy/2)));
      scene->setPopMenuStatus(false);

});

zeminButton->setFixedSize(en*c/2, boy*b);
zeminButton->setIconSize(QSize(en*cc*0.7,boy*b));
zeminPopButton->setFixedSize(en*c/2, boy*b);
zeminPopButton->setIconSize(QSize(en*cc*0.7,boy*b));

layout->addWidget(zeminButton, 25,0,1,1);
layout->addWidget(zeminPopButton, 25,1,1,1);
zeminMenus=zeminMenu();
zeminMenus->show();zeminMenus->hide();
//zeminPopButton->setMenu(zeminMenu(SLOT(zeminPopButton()), DiagramItem::DiagramType::Cizgi));
connect(zeminPopButton, &QPushButton::clicked, [=]() {
    //qDebug()<<"zeminpop click";
    currentScreenModeSlot();
   scene->setPopMenuStatus(true);
    zeminMenus->exec(mapToGlobal(zeminPopButton->pos() + QPoint(kutuLeft-zeminMenus->width()-kutuWidth/2,kutuTop+boy/2)));
    scene->setPopMenuStatus(false);


});

sekilButton->setFixedSize(en*c/2, boy*b);
sekilButton->setIconSize(QSize(en*cc*0.7,boy*b));

sekilPopButton->setFixedSize(en*c/2, boy*b);
sekilPopButton->setIconSize(QSize(en*cc*0.7,boy*b));

layout->addWidget(sekilButton, 35,0,1,1);
layout->addWidget(sekilPopButton, 35,1,1,1);
sekilMenus=sekilMenu();
sekilMenus->show();sekilMenus->hide();
//sekilPopButton->setMenu(sekilMenu(SLOT(sekilPopButton()), DiagramItem::DiagramType::Cizgi));
connect(sekilPopButton, &QPushButton::clicked, [=]() {
   // scene->setPopMenuStatus(true);
     currentScreenModeSlot();
     //qDebug()<<"sssss";
    sekilMenus->exec(mapToGlobal(sekilPopButton->pos() + QPoint(kutuLeft-sekilMenus->width()-kutuWidth/2,kutuTop+boy/2)));
    scene->setPopMenuStatus(false);

});

QPushButton *textButton = new QPushButton(this);
textButton->setIcon(QIcon(":/icons/text.png"));
textButton->setFixedSize(en*c, boy*b);
textButton->setIconSize(QSize(en*c,boy*b*0.75));
textButton->setFlat(true);
//connect(textButton,SIGNAL(clicked()),this,SLOT(screenClickButtonClick()));

layout->addWidget(textButton, 15,0,1,2);
connect(textButton, &QPushButton::clicked, [=]() {

    // View boyutu
    QSize viewSize = view->viewport()->size();
    toolPromter *promter=new toolPromter(viewSize.width()*0.90,viewSize.height());
    connect(promter, SIGNAL(promterCloseSignal(QString)),
            this, SLOT(promterCloseSignalSlot(QString)));

    promter->move(viewSize.width()/2-promter->width()/2,viewSize.width()/4-promter->height()/2);
    Qt::WindowFlags flags = 0;
    flags |= Qt::FramelessWindowHint;
    //flags |= Qt::X11BypassWindowManagerHint;
    promter->setWindowFlags(flags);
    promter->show();
    this->hide();
   // return;

});
/**********************************/
screenClickButton = new QPushButton(this);
screenClickButton->setIcon(QIcon(":/icons/screenClick.png"));
screenClickButton->setFixedSize(en*c, boy*b);
screenClickButton->setIconSize(QSize(en*c,boy*b));
screenClickButton->setFlat(true);
connect(screenClickButton,SIGNAL(clicked()),this,SLOT(screenClickButtonClick()));

layout->addWidget(screenClickButton, 36,0,1,2);
/*connect(screenClickButton, &QPushButton::clicked, [=]() {
    screenClickDrm=!screenClickDrm;
    if(screenClickDrm)
    {
    tempcurrentScreenMode=currentScreenMode;
    scene->setMode(Scene::Mode::NoMode, DiagramItem::DiagramType::NoType);
     }else
    {
        currentScreenMode=tempcurrentScreenMode;
        scene->setMode(currentScreenMode, DiagramItem::DiagramType::NoType);

    }
     currentScreenModeSlot();
});*/
/*******************************************/
QPushButton *saatButton= new QPushButton;
saatButton->setFixedSize(en*c, boy*b);
saatButton->setIconSize(QSize(en*c,boy*b));
saatButton->setFlat(true);
saatButton->setIcon(QIcon(":icons/sayac.png"));

connect(saatButton, &QPushButton::clicked, [=]() {
    if(!sayacShow)
    {
        sayacShow=true;//Sayac Açılıyor...
    if(!screenDesktop)ekranButtonClick();
     zeminBeyazButtonClick();///burada zemin beyaz yapılıyor

 sayacStartButton= new QPushButton(this);
 sayacStartButton->hide();
 sayacCloseButton= new QPushButton(this);
 sayacCloseButton->hide();

        sayac=new QLabel(this);
        // kalemKalinlik();
        sayac->hide();
        sure=new QSpinBox(this);
        sure->setStyleSheet(
                     "QSpinBox { border: 3px solid gray; border-radius: 5px; min-height: 150px; min-width: 150px; }"
                     "QSpinBox::up-arrow { border-left: 17px solid none;"
                     "border-right: 17px solid none; border-bottom: 17px solid black; width: 0px; height: 0px; }"
                     "QSpinBox::up-arrow:hover { border-left: 17px solid none; "
                     "border-right: 17px solid none; border-bottom: 17px solid black; width: 0px; height: 0px; }"
                     "QSpinBox::up-button { min-width: 80px; min-height: 77px; background-color: gray; }"
                     "QSpinBox::up-button:hover { min-width: 80px; min-height: 77px; background-color: gray; }"
                     "QSpinBox::down-arrow { border-left: 17px solid none;"
                     "border-right: 17px solid none; border-top: 17px solid black; width: 0px; height: 0px; }"


                     "QSpinBox::down-arrow:hover { border-left: 17px solid none;"
                     "border-right: 17px solid none; border-top: 17px solid black; width: 0px; height: 0px; }"
                     "QSpinBox::down-button { min-width: 80px; min-height: 77px; background-color: gray; }"
                     "QSpinBox::down-button:hover { min-width: 80px; min-height: 77px; background-color: gray; }"

                     );
         sure->hide();
         bar=new QProgressBar(this);
         bar->hide();


     sayac->move(this->width()/2-400,this->height()/2-250);
     sayac->resize(800, 500);
     sayac->show();
     bar->show();
     //sure->hide();

     sure->move(this->width()/2-250,this->height()/2+170);
     sure->resize(200, 50);
     sure->setValue(30);
     sure->show();
      sayacStartButton->setFixedSize(en*2, boy*3);
     sayacStartButton->setIconSize(QSize(en*2,boy*3));
     sayacStartButton->setFlat(true);
     sayacStartButton->setIcon(QIcon(":icons/sayacplay.png"));
     sayacStartButton->move(this->width()/2-50,this->height()/2+200);
     sayacStartButton->show();
     bar->move(this->width()/2-250,this->height()/2-250);
     bar->resize(500, 50);
     connect(sayacStartButton, &QPushButton::clicked, [=]() {
         saniye=0;
         saat->start(1000);
         //delete sure;
         sure->hide();
         sayacStartButton->hide();
        // bar->hide();
        // sayacCloseButton->hide();
         bar->setMaximum(sure->value()*60);




 });
        sayacCloseButton->setFixedSize(en*2, boy*3);
     sayacCloseButton->setIconSize(QSize(en*2,boy*3));
     sayacCloseButton->setFlat(true);
     sayacCloseButton->setIcon(QIcon(":icons/sayacstop.png"));
     sayacCloseButton->move(this->width()/2+100,this->height()/2+200);
     sayacCloseButton->show();
     connect(sayacCloseButton, &QPushButton::clicked, [=]() {
         sayacShow=false;//Sayac Kapatılıyor..
        saat->stop();
               sayac->hide();
         sure->hide();
           bar->hide();
         sayacStartButton->hide();
         sayacCloseButton->hide();
         zeminSeffafButtonClick();///burada zemin beyaz yapılıyor

 });
}
});
layout->addWidget(saatButton, 37,0,1,2);
/**************************************/

addShapeButton = new QPushButton(this);
addShapeButton->setIcon(QIcon(":/icons/addimage.png"));
addShapeButton->setFixedSize(en*c, boy*b);
addShapeButton->setIconSize(QSize(en*cc,boy*b));
addShapeButton->setFlat(true);
connect(addShapeButton, &QPushButton::clicked, [=]()
{
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
                QPixmap image = QPixmap(abc.selectedFiles()[0]);
                scene->setImage(image);
                secButtonClick();
                scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Resim);
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
                QPixmap image = QPixmap(abc.selectedFiles()[0]);
                scene->setImage(image);
                  secButtonClick();
                scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Resim);

            }
        }

    }

    flags |= Qt::Window;
    flags |= Qt::X11BypassWindowManagerHint;
    flags |= Qt::WindowStaysOnTopHint;
    this->setWindowFlags(flags);
    show();
});layout->addWidget(addShapeButton, 38, 0,1,2);
/***************************************************************/
/**************************************/
/*pageSaveButton = new QPushButton(this);
pageSaveButton->setIcon(QIcon(":/icons/save.png"));
*/

saveButton->setFixedSize(en*c, boy*0.8);
saveButton->setIconSize(QSize(en*cc,boy*0.8));
saveButton->setFlat(true);
layout->addWidget(saveButton, 40, 0,1,2);
/************************************************************/
//QPushButton *
yazdirButton= new QPushButton;
yazdirButton->setFixedSize(en*c, boy*0.8);
yazdirButton->setIconSize(QSize(en*cc,boy*0.7));
yazdirButton->setFlat(true);
yazdirButton->setIcon(QIcon(":icons/print.png"));

connect(yazdirButton, &QPushButton::clicked, [=]() {
    //QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",QString(), "*.pdf");
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    //printer.setOrientation(Qt::Horizontal);
    printer.setOrientation(QPrinter::Landscape);
    //printer.setOutputFormat(QPrinter::PdfFormat);
    //printer.setOutputFileName(fileName);
    int filenumber=20;
    QSize screenSize = qApp->screens()[0]->size();
    QPixmap pixMap = view->grab(view->sceneRect().toRect());
    QPainter p;
    p.begin(&printer);
    p.setWindow(QRect(0, 0, screenSize.width(),screenSize.height()));
    p.drawPixmap (0, 0, pixMap);
    p.end();
});
layout->addWidget(yazdirButton, 41,0,1,2);

loadPdfButton= new QPushButton;
loadPdfButton->setFixedSize(en*c, boy*0.8);
loadPdfButton->setIconSize(QSize(en*cc,boy*1.3));
loadPdfButton->setFlat(true);
loadPdfButton->setIcon(QIcon(":icons/loadpdf.png"));

connect(loadPdfButton, &QPushButton::clicked, [=]() {


    bool fileSelected=false;
    Qt::WindowFlags flags = 0;
   //if(screenDesktop==true) ekranButtonClick();

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
        abc.setWindowTitle("Pdf Dosyası Aç");
        abc.setDirectory(QDir::homePath()+"/Masaüstü");
        abc.setNameFilter(tr("PDF file (*.pdf)"));
        abc.setWindowModality( Qt::WindowModal );
        abc.setFileMode( QFileDialog::AnyFile );
        abc.setModal(true);
           abc.setWindowModality(Qt::ApplicationModal);

        if(abc.exec()) {
            if(abc.selectedFiles()[0].contains(".pdf", Qt::CaseInsensitive)) fileSelected=true;

           //..

        }
       // int i =
             //   abc.show();
         //   qDebug() << "Dialog result: " << i;

//if(screenDesktop==false) ekranButtonClick();
    }
    else
    {
        //qDebug()<<"windows fileopen";
        abc.setWindowTitle("Pdf Dosya Aç");
        abc.setDirectory(QDir::homePath()+"/desktop");
        abc.setNameFilter(tr("PDF file (*.pdf)"));
        abc.setWindowModality( Qt::WindowModal );
        abc.setFileMode( QFileDialog::AnyFile );
        int i = abc.exec();
            qDebug() << "Dialog result: " << i;

        if(abc.exec()) {
            if(abc.selectedFiles()[0].contains(".pdf", Qt::CaseInsensitive)) fileSelected=true;

            if(screenDesktop==false) ekranButtonClick();

        }
        //qDebug()<<"selam";


    }

    flags |= Qt::Window;
    flags |= Qt::X11BypassWindowManagerHint;
    flags |= Qt::WindowStaysOnTopHint;
    this->setWindowFlags(flags);
    show();


    if(fileSelected==false) return;
    fileSelected=false;
   // Poppler::Document *doc
    doc = Poppler::Document::load(abc.selectedFiles()[0]);
    doc->setRenderHint(Poppler::Document::TextAntialiasing,true);
    doc->setRenderHint(Poppler::Document::Antialiasing,true);
    doc->setRenderHint(Poppler::Document::TextHinting,true);
    doc->setRenderHint(Poppler::Document::TextSlightHinting,true);
    doc->setRenderHint(Poppler::Document::ThinLineSolid,true);
    doc->setRenderBackend(Poppler::Document::ArthurBackend);
    pdfPageCount=doc->numPages();
    pdfFirstPageNumber=0;
    pdfLastPageNumber=0;
    //******************Load Pdf File************************************
    if(pdfPageCount>0)
    {


        pdfobjectnumber=1;
       // pdfPageList=1;
        ileriSayfaButtonClick();

        //sceneSayfaActiveNumber=0;
       // scene=sceneSayfa[sceneSayfaActiveNumber];
       // view->setScene(scene);
       // if(scene->pdfObjectAdded&&scene->pdfObjectShow==false) pdfLoaderPage(sceneSayfaActiveNumber);///pdf page loader
        //currentScreenModeSlot();
    }

});
layout->addWidget(loadPdfButton, 43, 0,1,2);

savePdfButton= new QPushButton;
savePdfButton->setFixedSize(en*c, boy*0.8);
savePdfButton->setIconSize(QSize(en,boy*0.7));
savePdfButton->setFlat(true);
savePdfButton->setIcon(QIcon(":icons/savepdf.png"));



// movie->start();
connect(savePdfButton, &QPushButton::clicked, [=]() {
    Qt::WindowFlags flags = 0;
    flags |= Qt::Dialog;
    flags |= Qt::X11BypassWindowManagerHint;

    QMessageBox messageBox(this);
    messageBox.setWindowFlags(flags);
    messageBox.setText("Bilgi\t\t\t\t\t\t");
    messageBox.setInformativeText("Pdf Dosyası Masaüstünüze Kaydedilecek\n"
                                  "Bu İşlem Kaydedeceğiniz Sayfa Sayısına Göre Zaman Alacaktır\n"
                                  "İşlemler Tamamlanana Kadar Lütfen Bekleyiniz... ");
    QAbstractButton *evetButton =messageBox.addButton(tr("Tamam"), QMessageBox::ActionRole);
    messageBox.setIcon(QMessageBox::Information);
            messageBox.exec();
//qDebug()<<"ileri Start"<<QDateTime::currentDateTime();
    for(int i=1;i<=(pdfPageCount+ekliSayfa)/15;i++)
    {
        ileriSayfaButtonClick();
    }
 //   qDebug()<<"ileri end"<<QDateTime::currentDateTime();
    QString fileName;
    QString os="";
    #ifdef WIN32
    // Windows code here
        os="windows";
    #else
    // UNIX code here
        os="linux";
    #endif

        if(os=="linux"){
        fileName=QDir::homePath()+"/Masaüstü/E-Tahta.pdf";
        }
    else{//windows
        fileName=QDir::homePath()+"/desktop/E-Tahta.pdf";
       }


        QFile f(fileName);
           f.open(QIODevice::WriteOnly);
           QPdfWriter* pdfWriter = new QPdfWriter(&f);

        //QPdfWriter *pdfWriter(&f);
//pdfWriter.setPageSize(QPageSize(100,100));
pdfWriter->setPageSizeMM(QSizeF(view->sceneRect().toRect().width(), view->sceneRect().toRect().height()));
QPainter painter(pdfWriter);
//qDebug()<<"Sayfacreate Start"<<QDateTime::currentDateTime();
for(int i=0;i<pageList.length();i++) {

        // if(sceneSayfa[i]->pdfObjectShow==false&&sceneSayfa[i]->pdfObjectAdded)
             pageButtonClick(i);///sayfalar sırayla pdf yapılıyor
             scene->makeItemsControllable(false);
             painter.setWindow(QRect(0, 0, view->sceneRect().toRect().width(), view->sceneRect().toRect().height()));
             QPixmap pixMap = view->grab(view->sceneRect().toRect());
             painter.drawPixmap(0,0,pixMap);

    if(i!=pageList.length()-1)pdfWriter->newPage();
    /*if(i!=sceneSayfaNumber)
    {
        pdfWriter.newPage();
        ileriSayfaButtonClick();
    }*/
}
//qDebug()<<"Sayfacreate End"<<QDateTime::currentDateTime();
painter.end();
delete pdfWriter;
f.close();

QString st;
st.append(QDir::homePath()+"/Masaüstü/E-Tahta.pdf");
st.append("\n\nDosyası Masaüstünüze Kaydedildi. ");


 Qt::WindowFlags flagss = 0;
 flagss |= Qt::Dialog;
 flagss |= Qt::X11BypassWindowManagerHint;

 QMessageBox messageBox1(this);
 messageBox1.setWindowFlags(flagss);
 messageBox1.setText("Bilgi\t\t\t");
 messageBox1.setInformativeText(st);
 QAbstractButton *evetButton1 =messageBox1.addButton(tr("Tamam"), QMessageBox::ActionRole);
// QAbstractButton *hayirButton =messageBox.addButton(tr("Hayır"), QMessageBox::ActionRole);
 messageBox1.setIcon(QMessageBox::Information);
         messageBox1.exec();


});
layout->addWidget(savePdfButton, 44,0,1,2);
/*******************************/

//layout->addWidget(pageButton, 50, 0,1,1);
//layout->addWidget(pagePopButton,50,1,1,1);

//layout->addWidget(sayfaLabel,5,0,1,2);
//pagePopButton->setMenu(pageMenu(SLOT(pagePopButton()), DiagramItem::DiagramType::Cizgi));
/*QMenu *pageMenus=pageMenu();
connect(pagePopButton, &QPushButton::clicked, [=]() {
    scene->setPopMenuStatus(true);
    pageMenus->exec(mapToGlobal(pagePopButton->pos() + QPoint(kutuLeft-315,kutuTop+boy/2)));
    scene->setPopMenuStatus(false);
});*/
/*ileriGeriSayfaLabel=new QLabel(this);
//ileriGeriSayfaLabel->setText("( "+QString::number(sceneSayfaNumber+1)+"/"+QString::number(sceneSayfaActiveNumber+1)+" )");
ileriGeriSayfaLabel->setText("  "+QString::number(sceneSayfaNumber+1)+"/"+QString::number(sceneSayfaActiveNumber+1));
ileriGeriSayfaLabel->setStyleSheet("QLabel { color:#3e8cb7;}");
ileriGeriSayfaLabel->move(this->width()/2-en/10,this->height()-boy-boy/10);
ileriGeriSayfaLabel->hide();
*/
/***************************************************************/
zoomfitSayfaButton = new QPushButton(this);
zoomfitSayfaButton->setIcon(QIcon(":icons/fitwindow.png"));
zoomfitSayfaButton->setFixedSize(en, boy);
zoomfitSayfaButton->setIconSize(QSize(en*0.8,boy*0.8));
zoomfitSayfaButton->setFlat(true);
zoomfitSayfaButton->hide();
zoomfitSayfaButton->move(this->width()/4*3+boy*4,this->height()-boy-boy);

connect(zoomfitSayfaButton, &QPushButton::clicked, [=]()
{
   zoomfitSayfaButtonClick();
   });
/***************************************************************/
zoompozitifSayfaButton = new QPushButton(this);
zoompozitifSayfaButton->setIcon(QIcon(":icons/zoompozitif.png"));
zoompozitifSayfaButton->setFixedSize(en, boy);
zoompozitifSayfaButton->setIconSize(QSize(en*0.8,boy*0.8));
zoompozitifSayfaButton->setFlat(true);
zoompozitifSayfaButton->hide();
zoompozitifSayfaButton->move(this->width()/4*3+boy*2,this->height()-boy-boy);

connect(zoompozitifSayfaButton, &QPushButton::clicked, [=]()
{
   zoompozitifSayfaButtonClick();
   });
/***************************************************************/
zoomnegatifSayfaButton = new QPushButton(this);
zoomnegatifSayfaButton->setIcon(QIcon(":icons/zoomnegatif.png"));
zoomnegatifSayfaButton->setFixedSize(en, boy);
zoomnegatifSayfaButton->setIconSize(QSize(en*0.8,boy*0.8));
zoomnegatifSayfaButton->setFlat(true);
zoomnegatifSayfaButton->hide();
zoomnegatifSayfaButton->move(this->width()/4*3+boy*3,this->height()-boy-boy);

connect(zoomnegatifSayfaButton, &QPushButton::clicked, [=]()
{
   zoomnegatifSayfaButtonClick();
   });
/***************************************************************/
nextSayfaButton = new QPushButton(this);
nextSayfaButton->setIcon(QIcon(":icons/nextpage.png"));
nextSayfaButton->setFixedSize(en, boy);
nextSayfaButton->setIconSize(QSize(en*0.8,boy*0.8));
nextSayfaButton->setFlat(true);
nextSayfaButton->hide();
nextSayfaButton->move(this->width()/4*3+boy,this->height()-boy-boy);

connect(nextSayfaButton, &QPushButton::clicked, [=]()
{
    ileriSayfaButtonClick();
   });
/***************************************************************/
backSayfaButton = new QPushButton(this);
backSayfaButton->setIcon(QIcon(":icons/backpage.png"));
backSayfaButton->setFixedSize(en, boy);
backSayfaButton->setIconSize(QSize(en*0.8,boy*0.8));
backSayfaButton->setFlat(true);
backSayfaButton->hide();
backSayfaButton->move(this->width()/4-boy-boy,this->height()-boy-boy);
connect(backSayfaButton, &QPushButton::clicked, [=]()
{
geriSayfaButtonClick();
});
/***************************************************************/
/***************************************************************/
delSayfaButton = new QPushButton(this);
delSayfaButton->setIcon(QIcon(":icons/delpage.png"));
delSayfaButton->setFixedSize(en, boy);
delSayfaButton->setIconSize(QSize(en*0.8,boy*0.8));
delSayfaButton->setFlat(true);
///delSayfaButton->hide();
delSayfaButton->setEnabled(false);
delSayfaButton->move(this->width()/4*3,this->height()-boy-boy);
connect(delSayfaButton, &QPushButton::clicked, [=]()
{
    ekliSayfa--;
silSayfaButtonClick();
});
/***************************************************************/
/***************************************************************/
addSayfaButton = new QPushButton(this);
addSayfaButton->setIcon(QIcon(":icons/addpage.png"));
addSayfaButton->setFixedSize(en*c, boy);
addSayfaButton->setIconSize(QSize(en*0.8,boy*0.8));
addSayfaButton->setFlat(true);
//addSayfaButton->hide();
addSayfaButton->move(this->width()/4-boy,this->height()-boy-boy);
connect(addSayfaButton, &QPushButton::clicked, [=]()
{
ekliSayfa++;
ekleSayfaButtonClick(sceneSayfaActiveNumber,false,-1);
});
/*************************/
ayarButton->setFixedSize(en*c, boy*0.8);
ayarButton->setIconSize(QSize(en,boy*0.7));
layout->addWidget(ayarButton, 50, 0,1,2);
//pagePopButton->setMenu(pageMenu(SLOT(pagePopButton()), DiagramItem::DiagramType::Cizgi));
QMenu *ayarMenus=ayarMenu();
ayarMenus->show();ayarMenus->hide();

connect(ayarButton, &QPushButton::clicked, [=]() {
   scene->setPopMenuStatus(true);
   ayarMenus->exec(mapToGlobal(ayarButton->pos() + QPoint(kutuLeft-ayarMenus->width(),kutuTop/2)));
   scene->setPopMenuStatus(false);
});
/***************************************************************/

//layout->addWidget(backSayfaButton, 50,0,1,2);
//layout->addWidget(nextSayfaButton, 50,1,1,2);
gizleGosterButton->setFixedSize(en*c, boy*0.8);
gizleGosterButton->setIconSize(QSize(en*0.7,boy*0.7));
layout->addWidget(gizleGosterButton, 55,0,1,2);

kalemKapatButton->setFixedSize(en*c, boy*0.8);
kalemKapatButton->setIconSize(QSize(en*1.2,boy*0.7));

layout->addWidget(kalemKapatButton,60,0,1,2);
//layout->setColumnStretch(3, 25);
kokLayot->addLayout(layout);
//buyukKutu->setLayout(layout);

/***********************kalem Move button******************************/
auto MoveLeft= new QPushButton(this);
MoveLeft->setIcon(QIcon(":icons/kalemmove.png"));
MoveLeft->setFixedSize(en*c, boy);
MoveLeft->setIconSize(QSize(en*0.8,boy*0.8));
MoveLeft->setFlat(true);
//addSayfaButton->hide();
MoveLeft->move(boy*1.5,this->height()-boy-boy);
connect(MoveLeft, &QPushButton::clicked, [=]()
{
    if(kutuLeft!=10)
    {
    buyukKutu->setGeometry(QRect(10,kutuTop,kutuWidth,kutuHeight));
    kutuLeft=10;
   /// kutuTop=50;
    gizleGosterButtonClick();
    gizleGosterButtonClick();
    }else{
        buyukKutu->setGeometry(QRect(this->width()-kutuWidth-10,kutuTop,kutuWidth,kutuHeight));
        kutuLeft=this->width()-kutuWidth-10;
       /// kutuTop=50;
        gizleGosterButtonClick();
        gizleGosterButtonClick();
    }
});
auto MoveRight= new QPushButton(this);
MoveRight->setIcon(QIcon(":icons/kalemmove.png"));
MoveRight->setFixedSize(en*c, boy);
MoveRight->setIconSize(QSize(en*0.8,boy*0.8));
MoveRight->setFlat(true);
//addSayfaButton->hide();
MoveRight->move(this->width()-boy*1.5,this->height()-boy-boy);
connect(MoveRight, &QPushButton::clicked, [=]()
{
    if(kutuLeft!=this->width()-kutuWidth-10)
    {
    buyukKutu->setGeometry(QRect(this->width()-kutuWidth-10,kutuTop,kutuWidth,kutuHeight));
    kutuLeft=this->width()-kutuWidth-10;
   /// kutuTop=50;
    gizleGosterButtonClick();
    gizleGosterButtonClick();
    }else{
        buyukKutu->setGeometry(QRect(10,kutuTop,kutuWidth,kutuHeight));
        kutuLeft=10;
       /// kutuTop=50;
        gizleGosterButtonClick();
        gizleGosterButtonClick();

    }
});
/******************************************************/

}

#endif // KALEMLAYOUT_H
