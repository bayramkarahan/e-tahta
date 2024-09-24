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


#ifndef POPMENU_H
#define POPMENU_H
#include <QPdfWriter>
#include <QPainter>
#include<poppler/qt5/poppler-qt5.h>
#include <QThread>
#include<QWidget>

QMenu *MainWindow::ayarMenu()
{   QMenu *menu = new QMenu(this);
    int e=(en*0.8)/4*9;
      int b=(boy*0.6)/4*5;

   infoButton->setFixedSize(e,b);
   infoButton->setIconSize(QSize(e,b));
   tasiButton->setFixedSize(e, b);
   tasiButton->setIconSize(QSize(e,b));
   klavyeButton->setFixedSize(e, b);
   klavyeButton->setIconSize(QSize(e,b));
   kalemKapatButton->setFixedSize(e, b);
   kalemKapatButton->setIconSize(QSize(e,b));
   connect(tasiButton, &QPushButton::clicked, [=]() {     menu->close();   });
   connect(klavyeButton, &QPushButton::clicked, [=]() {     menu->close();   });

   QPushButton *saveProfileButton= new QPushButton;
   saveProfileButton->setFixedSize(e, b);
   saveProfileButton->setIconSize(QSize(e,b));
   saveProfileButton->setFlat(true);
   saveProfileButton->setIcon(QIcon(":icons/saveprofile.png"));

   connect(saveProfileButton, &QPushButton::clicked, [=]() {
       FileCrud *fc=new FileCrud();
       fc->dosya="e-tahta.ini";

       if(fc->fileexists()) fc->fileremove();
       fc->fileWrite("myPenAlpha="+QString::number(myPenAlpha));
       fc->fileWrite("myPenColor="+myPenColor.name());
       fc->fileWrite("myPenSize="+QString::number(myPenSize));
       fc->fileWrite("myGridSize="+QString::number(myGridSize));
       fc->fileWrite("myEraseSize="+QString::number(myEraseSize));
       fc->fileWrite("myPenStyle="+QString::number(myPenStyle));
       fc->fileWrite("mySekilPenStyle="+QString::number(mySekilPenStyle));
       fc->fileWrite("mySekilZeminColor="+mySekilZeminColor.name());
       fc->fileWrite("mySekilKalemColor="+mySekilKalemColor.name());
       fc->fileWrite("myGridColor="+myGridColor.name());
       fc->fileWrite("myZeminColor="+myZeminColor.name());
       fc->fileWrite("mySekilPenSize="+QString::number(mySekilPenSize));
       fc->fileWrite("myZeminType="+QString::number(myZeminType));
       fc->fileWrite("gridYatay="+QString::number(scene->sceneGridYatay));
       fc->fileWrite("gridDikey="+QString::number(scene->sceneGridDikey));
       fc->fileWrite("clock="+QString::number(clock));
       fc->fileWrite("kutuLeft="+QString::number(kutuLeft));
       fc->fileWrite("kutuTop="+QString::number(kutuTop));
       fc->fileWrite("copyState="+QString::number(copyState));
       fc->fileWrite("wsolVisible="+QString::number(wsolVisible));

});
   QPushButton *loadDefaultProfileButton= new QPushButton;
   loadDefaultProfileButton->setFixedSize(e, b);
   loadDefaultProfileButton->setIconSize(QSize(e,b));
   loadDefaultProfileButton->setFlat(true);
   loadDefaultProfileButton->setIcon(QIcon(":icons/loadprofile.png"));

   connect(loadDefaultProfileButton, &QPushButton::clicked, [=]() {

       myPenAlpha=255;
       myPenColor=QColor(0,0,0,255);
       myPenSize=4;
       myGridSize=4;
       myEraseSize=4;
       myPenStyle=Qt::SolidLine;
       mySekilPenStyle=Qt::SolidLine;
       mySekilZeminColor=QColor(0,0,0,0);
       mySekilKalemColor=QColor(0,0,0,255);
       myGridColor=QColor(128,128,128,128);
       mySekilPenSize=4;
       myZeminColor=QColor(0,0,0,0);
       scene->sceneGridYatay=false;
       scene->sceneGridDikey=false;
       gizleGoster=true;
       screenDesktop=true;
       myZeminType=0;
       clock=true;
       kutuLeft=this->width()-kutuWidth-this->width()/100;
       kutuTop=(this->height() /2-kutuHeight/2);
       copyState=false;
       wsolVisible=false;

});

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
  //  layout->setContentsMargins(20, 20, 20,20);
   // layout->setVerticalSpacing(0);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(klavyeButton, 2,1,1,1,Qt::AlignHCenter);
    layout->addWidget(tasiButton, 2, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(infoButton, 2, 3,1,1,Qt::AlignHCenter);

    layout->addWidget(saveProfileButton,5,1 ,1,1,Qt::AlignHCenter);
    layout->addWidget(loadDefaultProfileButton, 5,2 ,1,1,Qt::AlignHCenter);
  ///  layout->addWidget(saatButton, 5, 3,1,1,Qt::AlignHCenter);
  //  layout->addWidget(kalemKapatButton, 7,1,1,1);
    layout->addWidget(new QLabel("<font size=1>Klavye</font>"),3,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Taşı</font>"),3,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Bilgi</font>"),3,3,1,1,Qt::AlignHCenter);

    layout->addWidget(new QLabel("<font size=1>Ayarları Kaydet</font>"),6,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Öntanımlı Ayarlar</font>"),6,2,1,1,Qt::AlignHCenter);

 ///   layout->addWidget(new QLabel("<font size=1>Sayaç</font>"),6,3,1,1,Qt::AlignHCenter);
    QCheckBox *checkbox = new QCheckBox("Kopyalama Yeni Sayfada Açılsın", menu);
    QFont ff( "Arial", 8, QFont::Normal);
    checkbox->setFont(ff);
    checkbox->setChecked(copyState);
    //qDebug()<<copyState;
    connect(checkbox, &QCheckBox::clicked, [=]() {
        copyState=checkbox->checkState();
       // qDebug()<<copyState;
});
    layout->addWidget(checkbox,7,1,1,3,Qt::AlignLeft);

    /**************************************************************/
    QCheckBox *checkboxwsolVisible = new QCheckBox("Sol E-TAHTA Paneli Gizle", menu);
  //  QFont ff( "Arial", 8, QFont::Normal);
    checkboxwsolVisible->setFont(ff);
    checkboxwsolVisible->setChecked(wsolVisible);
    //qDebug()<<copyState;
    connect(checkboxwsolVisible, &QCheckBox::clicked, [=]() {
        wsolVisible=checkboxwsolVisible->checkState();
        if(!wsolVisible) wsol->show();
        else wsol->hide();

       // qDebug()<<copyState;
});
    layout->addWidget(checkboxwsolVisible,8,1,1,3,Qt::AlignLeft);
    /****************************************************************/
   // layout->addWidget(new QLabel("<font size=1>Sayaç</font>"),6,3,1,1,Qt::AlignHCenter);

  //  layout->addWidget(new QLabel("<font size=1>Kapat</font>"),8,1,1,1,Qt::AlignHCenter);


  //  layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

   //  menu->setStyleSheet("QMenu { width: auto; height: auto; }");
   return menu;
}

QMenu* MainWindow::colorMenu(QString colorType)
{   QMenu *menu = new QMenu(this);
   // qDebug()<<"renk invoke"<<colorType;
    int e=(en*0.8)/4*9;
      int b=(boy*0.6)/4*5;
      e=e/2;
      b=b*0.8;

   palette->setColor(QPalette::Button,QColor(255,0,0,255));

   QPushButton *color1Button= new QPushButton;
   color1Button->setFixedSize(e, b);
   color1Button->setIconSize(QSize(e,b));
   color1Button->setFlat(true);
   color1Button->setAutoFillBackground(true);
   color1Button->setPalette(*palette);
   color1Button->update();

   connect(color1Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(255,0,0,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
   });


 palette->setColor(QPalette::Button,QColor(0,255,0,255));
   QPushButton *color2Button= new QPushButton;
   color2Button->setFixedSize(e, b);
   color2Button->setIconSize(QSize(e,b));
   color2Button->setFlat(true);
   color2Button->setAutoFillBackground(true);
   color2Button->setPalette(*palette);
   color2Button->update();

   connect(color2Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(0,255,0,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});

   palette->setColor(QPalette::Button,QColor(0,0,255,255));

   QPushButton *color3Button= new QPushButton;
   color3Button->setFixedSize(e, b);
   color3Button->setIconSize(QSize(e,b));
   color3Button->setFlat(true);
   color3Button->setAutoFillBackground(true);
   color3Button->setPalette(*palette);
   color3Button->update();

   connect(color3Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(0,0,255,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});

   palette->setColor(QPalette::Button,QColor(255,255,0,255));

   QPushButton *color4Button= new QPushButton;
   color4Button->setFixedSize(e, b);
   color4Button->setIconSize(QSize(e,b));
   color4Button->setFlat(true);
   color4Button->setAutoFillBackground(true);
   color4Button->setPalette(*palette);
   color4Button->update();

   connect(color4Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(255,255,0,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});

   palette->setColor(QPalette::Button,QColor(0,255,255,255));

   QPushButton *color5Button= new QPushButton;
   color5Button->setFixedSize(e, b);
   color5Button->setIconSize(QSize(e,b));
   color5Button->setFlat(true);
   color5Button->setAutoFillBackground(true);
   color5Button->setPalette(*palette);
   color5Button->update();

   connect(color5Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(0,255,255,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});

   palette->setColor(QPalette::Button,QColor(255,0,255,255));

   QPushButton *color6Button= new QPushButton;
   color6Button->setFixedSize(e, b);
   color6Button->setIconSize(QSize(e,b));
   color6Button->setFlat(true);
   color6Button->setAutoFillBackground(true);
   color6Button->setPalette(*palette);
   color6Button->update();

   connect(color6Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(255,0,255,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});

   palette->setColor(QPalette::Button,QColor(255,255,255,255));

   QPushButton *color7Button= new QPushButton;
   color7Button->setFixedSize(e, b);
   color7Button->setIconSize(QSize(e,b));
   color7Button->setFlat(true);
   color7Button->setAutoFillBackground(true);
   color7Button->setPalette(*palette);
   color7Button->update();

   connect(color7Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(255,255,255,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});

   palette->setColor(QPalette::Button,QColor(0,0,0,255));

   QPushButton *color8Button= new QPushButton;
   color8Button->setFixedSize(e, b);
   color8Button->setIconSize(QSize(e,b));
   color8Button->setFlat(true);
   color8Button->setAutoFillBackground(true);
   color8Button->setPalette(*palette);
   color8Button->update();

   connect(color8Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(0,0,0,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});

   palette->setColor(QPalette::Button,QColor(127,127,127,255));

   QPushButton *color9Button= new QPushButton;
   color9Button->setFixedSize(e, b);
   color9Button->setIconSize(QSize(e,b));
   color9Button->setFlat(true);
   color9Button->setAutoFillBackground(true);
   color9Button->setPalette(*palette);
   color9Button->update();

   connect(color9Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(127,127,127,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});
   palette->setColor(QPalette::Button,QColor(127,255,127,255));

   QPushButton *color10Button= new QPushButton;
   color10Button->setFixedSize(e, b);
   color10Button->setIconSize(QSize(e,b));
   color10Button->setFlat(true);
   color10Button->setAutoFillBackground(true);
   color10Button->setPalette(*palette);
   color10Button->update();

   connect(color10Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(127,255,127,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});

   palette->setColor(QPalette::Button,QColor(255,120,0,255));

   QPushButton *color11Button= new QPushButton;
   color11Button->setFixedSize(e, b);
   color11Button->setIconSize(QSize(e,b));
   color11Button->setFlat(true);
   color11Button->setAutoFillBackground(true);
   color11Button->setPalette(*palette);
   color11Button->update();

   connect(color11Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(255,120,0,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});


   palette->setColor(QPalette::Button,QColor(102,0,153,255));

   QPushButton *color12Button= new QPushButton;
   color12Button->setFixedSize(e, b);
   color12Button->setIconSize(QSize(e,b));
   color12Button->setFlat(true);
   color12Button->setAutoFillBackground(true);
   color12Button->setPalette(*palette);
   color12Button->update();

   connect(color12Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(102,0,153,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});
   palette->setColor(QPalette::Button,QColor(150,75,0,255));

   QPushButton *color13Button= new QPushButton;
   color13Button->setFixedSize(e, b);
   color13Button->setIconSize(QSize(e,b));
   color13Button->setFlat(true);
   color13Button->setAutoFillBackground(true);
   color13Button->setPalette(*palette);
   color13Button->update();

    connect(color13Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(150,75,0,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});

    palette->setColor(QPalette::Button,QColor(150,170,255,255));

   QPushButton *color14Button= new QPushButton;
   color14Button->setFixedSize(e, b);
   color14Button->setIconSize(QSize(e,b));
   color14Button->setFlat(true);
   color14Button->setAutoFillBackground(true);
   color14Button->setPalette(*palette);
   color14Button->update();

   connect(color14Button, &QPushButton::clicked, [=]() {
       QColor renk=QColor(150,170,255,255);
       if(colorType=="pencolor") setPenColor(renk);
       if(colorType=="mySekilKalemColor")  mySekilKalemColor=renk;
       if(colorType=="mySekilZeminColor")  mySekilZeminColor=renk;
       if(colorType=="myZeminColor")  myZeminColor=renk;
       if(colorType=="myGridColor")  myGridColor=renk;
       menu->close();
});
    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    layout->setContentsMargins(5, 5, 5,5);
    layout->setVerticalSpacing(2);
  //  layout->setColumnMinimumWidth(0, 37);
    layout->addWidget(color1Button, 1,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color2Button, 2,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color3Button, 3,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color4Button, 4,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color5Button, 5,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color6Button, 6,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color7Button, 7,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color8Button, 8,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color9Button, 9,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color10Button, 10,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color11Button, 11,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color12Button, 12,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color13Button, 13,1,1,1,Qt::AlignHCenter);
    layout->addWidget(color14Button, 14,1,1,1,Qt::AlignHCenter);

    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

     menu->setStyleSheet("QMenu {background-color:#acacac; }");
   return menu;
}

QMenu *MainWindow::eraseMenu()
{   int e=(en*0.8)/4*9;
    int b=(boy*0.6)/4*5;
    QMenu *menu = new QMenu(this);
    eraseSizePopLabel= new QLabel();
    eraseSizePopLabel->setText("Silgi Boyutu: "+QString::number(myPenSize));
  //  eraseSizePopLabel->resize(e,b);
    QFont ff( "Arial", 8, QFont::Normal);
    eraseSizePopLabel->setFont(ff);

    QSlider *eraseSize= new QSlider(Qt::Horizontal,menu);
    //eraseSize->setMinimum(2);
    //eraseSize->setMaximum(1);
    eraseSize->setRange(1,15);
    eraseSize->setSliderPosition(4);
    connect(eraseSize,SIGNAL(valueChanged(int)),this,SLOT(setEraseSize(int)));
    silMenuButton->setFixedSize(e, b);
    silMenuButton->setIconSize(QSize(e,b));
    temizleMenuButton->setFixedSize(e, b);
    temizleMenuButton->setIconSize(QSize(e,b));

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
   // layout->setContentsMargins(0, 0, 0, 3);
   // layout->setColumnMinimumWidth(0, 37);


    layout->addWidget(eraseSizePopLabel, 1, 1,1,2);
    layout->addWidget(silMenuButton, 2, 1,1,1,Qt::AlignHCenter);
    layout->addWidget(temizleMenuButton, 2, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Sil</font>"),3,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Tahta Temizle</font>"),3,2,1,1,Qt::AlignHCenter);

    layout->addWidget(eraseSize,4,1,1,2);
  //  layout->setColumnStretch(6, 255);
    connect(silMenuButton, &QPushButton::clicked, [=]() {
        scene->setPopMenuStatus(false);
        menu->close();
        //kalemButtonClick();
    });
    connect(temizleMenuButton, &QPushButton::clicked, [=]() {
        scene->setPopMenuStatus(false);
        menu->close();
        //kalemButtonClick();
    });
    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);
    eraseSize->setStyleSheet(".QSlider::groove:Horizontal {"
                                   "background: rgba(0, 0, 50, 200);"
                                   "width:"+QString::number(e*3)+"px;"
                                    "height:"+QString::number(b/2)+"px;"
                                   "}"

                                   ".QSlider::handle:Horizontal {"
                                   "background: rgba(242, 242, 242, 95);"
                                   "border: 2px solid rgb(0,0,0);"
                                   "background: rgba(0, 0, 50, 255);"
                                   "width: "+QString::number(e/2)+"px;"
                                   "height: "+QString::number(b)+"px;"
                                    "margin:-"+QString::number(e/8*3)+"px   0   -"+QString::number(b/8*3)+"px   0;"
                                   "}");

    eraseSize->setFixedSize(QSize(e*3,b));
   // menu->setStyleSheet("QMenu { width: 290 px; height: 180 px; }");
   return menu;
}

QMenu *MainWindow::sekilMenu()
{
    int ken=300;
    //ken=300;
    int e=(en*0.8)/4*9;
    int b=(boy*0.6)/4*5;
    e=e/2;
    QMenu *menu = new QMenu(this);
   // QLabel *sekilLabel= new QLabel();
   // sekilLabel->setText("Geometrik Şekiller");
    sekilKalemSizePopLabel= new QLabel();
    sekilKalemSizePopLabel->setText("Kalem Boyutu: "+QString::number(mySekilPenSize));
    QFont ff( "Arial", 8, QFont::Normal);
    sekilKalemSizePopLabel->setFont(ff);

    QSlider *sekilPenSize= new QSlider(Qt::Horizontal,menu);
    sekilPenSize->setMinimum(2);
    sekilPenSize->setMaximum(8);
    sekilPenSize->setSliderPosition(4);
    connect(sekilPenSize,SIGNAL(valueChanged(int)),this,SLOT(setSekilPenSize(int)));
    /*************************************************************************/
    DiagramItem *ditem=new DiagramItem();

    QPushButton *penStyleSolidLine = new QPushButton;
    penStyleSolidLine->setFixedSize(e, b);
    penStyleSolidLine->setIconSize(QSize(e,b));
    //penStyleSolidLine->setFlat(true);
    penStyleSolidLine->setIcon(lineImage(ditem->sekilStore(DiagramItem::DiagramType::Kalem,QRectF(QPointF(0,0),QPointF(ken,ken))),Qt::SolidLine,ken,ken));
    connect(penStyleSolidLine, &QPushButton::clicked, [=]() {setSekilPenStyle(Qt::SolidLine);});

    QPushButton *penStyleDashLine = new QPushButton;
    penStyleDashLine->setIcon(lineImage(ditem->sekilStore(DiagramItem::DiagramType::Kalem,QRectF(QPointF(0,0),QPointF(ken,ken))),Qt::DashLine,ken,ken));
    penStyleDashLine->setFixedSize(e, b);
    penStyleDashLine->setIconSize(QSize(e,b));
    //penStyleDashLine->setFlat(true);
    connect(penStyleDashLine, &QPushButton::clicked, [=]() {setSekilPenStyle(Qt::DashLine);});

    QPushButton *penStyleDotLine = new QPushButton;
    penStyleDotLine->setIcon(lineImage(ditem->sekilStore(DiagramItem::DiagramType::Kalem,QRectF(QPointF(0,0),QPointF(ken,ken))),Qt::DotLine,ken,ken));
    penStyleDotLine->setFixedSize(e, b);
    penStyleDotLine->setIconSize(QSize(e,b));
   // penStyleDotLine->setFlat(true);
    connect(penStyleDotLine, &QPushButton::clicked, [=]() {setSekilPenStyle(Qt::DotLine);});
/********************************************************************/


    /***********************pergel cetvel gönye iletki***************/


    QPushButton *pergel = new QPushButton;
    pergel->setFixedSize(e, b);
    pergel->setIconSize(QSize(e,b));
    //penStyleSolidLine->setFlat(true);
    pergel->setIcon(QIcon(":icons/pergel.png"));
    connect(pergel, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::Pergel);
    //QPixmap pm=QPixmap(":icons/pergel.png").scaled(200,50,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        scene->setImage(QPixmap(":icons/pergel.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Pergel);
      scene->donSlot();
        menu->close();
    });

    QPushButton *cetvel = new QPushButton;
    cetvel->setIcon(QIcon(":icons/cetvel.png"));
    cetvel->setFixedSize(e, b);
    cetvel->setIconSize(QSize(e,b));
    //penStyleDashLine->setFlat(true);
    connect(cetvel, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::Cetvel);
        scene->setImage(QPixmap(":icons/cetvel.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Cetvel);
         scene->donSlot();
        menu->close();

    });

    QPushButton *gonye = new QPushButton;
    gonye->setIcon(QIcon(":icons/gonye.png"));
    gonye->setFixedSize(e, b);
    gonye->setIconSize(QSize(e,b));
    // penStyleDotLine->setFlat(true);
    connect(gonye, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::Gonye);
        scene->setImage(QPixmap(":icons/gonye.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Gonye);
          scene->donSlot();
        menu->close();

    });

    QPushButton *iletki = new QPushButton;
    iletki->setIcon(QIcon(":icons/iletki.png"));
    iletki->setFixedSize(e, b);
    iletki->setIconSize(QSize(e,b));
    // penStyleDotLine->setFlat(true);
    connect(iletki, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::Iletki);
        scene->setImage(QPixmap(":icons/iletki.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Iletki);
         scene->donSlot();
        menu->close();

    });
    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(pergel);
    layout1->addWidget(cetvel);
    layout1->addWidget(gonye);
    layout1->addWidget(iletki);

    /***********************noktalı izometrik kareli çizgili***************/


    QPushButton *noktaliKagit = new QPushButton;
    noktaliKagit->setFixedSize(e, b);
    noktaliKagit->setIconSize(QSize(e,b));
    //penStyleSolidLine->setFlat(true);
    noktaliKagit->setIcon(QIcon(":icons/noktalikagit.png"));
    connect(noktaliKagit, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::NoktaliKagit);
        VERectangle*  itemToRectDraw = new VERectangle(scene);
        itemToRectDraw->sekilTur(DiagramItem::DiagramType::Copy);
        itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
        itemToRectDraw->setPos(QPoint(this->width()/2-250,this->height()/2-250));
         itemToRectDraw->setBrush(mySekilZeminColor);
        QPixmap pg(":icons/noktalikagit.png");
         QPixmap tmp(pg.width(),pg.height());
         tmp.fill(QColor(mySekilZeminColor));
         QPainter painter(&tmp);
          painter.drawPixmap(QPoint{}, pg, pg.rect());
         painter.end();

         itemToRectDraw->setImage(tmp);

        scene->addItem(itemToRectDraw);
        /***************************************/

        scene->graphicsList.append(itemToRectDraw);
        scene->graphicsListTemp.append(itemToRectDraw);
        scene->historyBack.append(itemToRectDraw);
        scene->historyBackAction.append("added");
        depo::historyBackCount=scene->historyBack.count();
        depo::historyNextCount=scene->historyNext.count();


        /*******************************************/
        itemToRectDraw->setRect(0,0,500,500);

        itemToRectDraw->fareState(false);
        scene->makeItemsControllable(false);
        itemToRectDraw->fareState(true);
        itemToRectDraw = 0;
        secButtonClick();

       //scene->donSlot();
        menu->close();
    });

    QPushButton *izometrikKagit = new QPushButton;
    izometrikKagit->setIcon(QIcon(":icons/izometrikkagit.png"));
    izometrikKagit->setFixedSize(e, b);
    izometrikKagit->setIconSize(QSize(e,b));
    //penStyleDashLine->setFlat(true);
    connect(izometrikKagit, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::IzometrikKagit);


        VERectangle*  itemToRectDraw = new VERectangle(scene);
        itemToRectDraw->sekilTur(DiagramItem::DiagramType::Copy);
        itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
        itemToRectDraw->setPos(QPoint(this->width()/2-250,this->height()/2-250));
         itemToRectDraw->setBrush(mySekilZeminColor);
        QPixmap pg(":icons/izometrikkagit.png");
         QPixmap tmp(pg.width(),pg.height());
         tmp.fill(QColor(mySekilZeminColor));
         QPainter painter(&tmp);
          painter.drawPixmap(QPoint{}, pg, pg.rect());
         painter.end();

         itemToRectDraw->setImage(tmp);

        scene->addItem(itemToRectDraw);
        /***************************************/

        scene->graphicsList.append(itemToRectDraw);
        scene->graphicsListTemp.append(itemToRectDraw);
        scene->historyBack.append(itemToRectDraw);
        scene->historyBackAction.append("added");
        depo::historyBackCount=scene->historyBack.count();
        depo::historyNextCount=scene->historyNext.count();


        /*******************************************/
        itemToRectDraw->setRect(0,0,500,500);
        itemToRectDraw->fareState(false);
        scene->makeItemsControllable(false);
        itemToRectDraw->fareState(true);


        itemToRectDraw = 0;
secButtonClick();
       // scene->setImage(QPixmap(":icons/izometrikkagit.png"));
      //  scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::IzometrikKagit);
       //  scene->donSlot();
        menu->close();

    });

    QPushButton *kareliKagit = new QPushButton;
    kareliKagit->setIcon(QIcon(":icons/karelikagit.png"));
    kareliKagit->setFixedSize(e, b);
    kareliKagit->setIconSize(QSize(e,b));
    // penStyleDotLine->setFlat(true);
    connect(kareliKagit, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::KareliKagit);


        VERectangle*  itemToRectDraw = new VERectangle(scene);
        itemToRectDraw->sekilTur(DiagramItem::DiagramType::Copy);
        itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
        itemToRectDraw->setPos(QPoint(this->width()/2-250,this->height()/2-250));
         itemToRectDraw->setBrush(mySekilZeminColor);
        QPixmap pg(":icons/karelikagit.png");
         QPixmap tmp(pg.width(),pg.height());
         tmp.fill(QColor(mySekilZeminColor));
         QPainter painter(&tmp);
          painter.drawPixmap(QPoint{}, pg, pg.rect());
         painter.end();

         itemToRectDraw->setImage(tmp);

        scene->addItem(itemToRectDraw);
        /***************************************/

        scene->graphicsList.append(itemToRectDraw);
        scene->graphicsListTemp.append(itemToRectDraw);
        scene->historyBack.append(itemToRectDraw);
        scene->historyBackAction.append("added");
        depo::historyBackCount=scene->historyBack.count();
        depo::historyNextCount=scene->historyNext.count();


        /*******************************************/
        itemToRectDraw->setRect(0,0,500,500);

        itemToRectDraw->fareState(false);
        scene->makeItemsControllable(false);
        itemToRectDraw->fareState(true);


        itemToRectDraw = 0;
secButtonClick();
       // scene->setImage(QPixmap(":icons/karelikagit.png"));
       // scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::KareliKagit);
       //   scene->donSlot();
        menu->close();

    });

    QPushButton *cizgiliKagit = new QPushButton;
    cizgiliKagit->setIcon(QIcon(":icons/gridyatay.png"));
    cizgiliKagit->setFixedSize(e, b);
    cizgiliKagit->setIconSize(QSize(e,b));
    // penStyleDotLine->setFlat(true);
    connect(cizgiliKagit, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::CizgiliKagit);
        gridLines = new GridLines (this->width(), this->height(),myGridSize*20,true,false,false,mySekilZeminColor, myPenColor);
        QSize screenSize = qApp->screens()[0]->size();
        QPixmap bkgnd=gridLines->PixItem(gridLines,this->width(), this->height());
        //scene->setForegroundBrush(bkgnd);

        VERectangle*  itemToRectDraw = new VERectangle(scene);
        itemToRectDraw->sekilTur(DiagramItem::DiagramType::Copy);
        itemToRectDraw->setPen(QPen(mySekilKalemColor, mySekilPenSize, mySekilPenStyle));
        itemToRectDraw->setPos(QPoint(this->width()/2-250,this->height()/2-250));
         itemToRectDraw->setBrush(mySekilZeminColor);
        QPixmap pg(bkgnd);
         QPixmap tmp(pg.width(),pg.height());
         tmp.fill(QColor(mySekilZeminColor));
         QPainter painter(&tmp);
          painter.drawPixmap(QPoint{}, pg, pg.rect());
         painter.end();

         itemToRectDraw->setImage(tmp);

        scene->addItem(itemToRectDraw);
        /***************************************/

        scene->graphicsList.append(itemToRectDraw);
        scene->graphicsListTemp.append(itemToRectDraw);
        scene->historyBack.append(itemToRectDraw);
        scene->historyBackAction.append("added");
        depo::historyBackCount=scene->historyBack.count();
        depo::historyNextCount=scene->historyNext.count();


        /*******************************************/
        itemToRectDraw->setRect(0,0,500,500);

        itemToRectDraw->fareState(false);
        scene->makeItemsControllable(false);
        itemToRectDraw->fareState(true);
secButtonClick();
        itemToRectDraw = 0;

       // scene->setImage(QPixmap(":icons/gridyatay.png"));
       // scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::CizgiliKagit);
       //  scene->donSlot();
        menu->close();

    });
    QHBoxLayout *layout0 = new QHBoxLayout;
    layout0->addWidget(noktaliKagit);
    layout0->addWidget(izometrikKagit);
    layout0->addWidget(kareliKagit);
    layout0->addWidget(cizgiliKagit);
    QHBoxLayout *layout00 = new QHBoxLayout;
    layout00->addWidget(new QLabel("<font size=1>Noktalı  </font>"));
    layout00->addWidget(new QLabel("<font size=1>İzometrik</font>"));
    layout00->addWidget(new QLabel("<font size=1>Kareli   </font>"));
    layout00->addWidget(new QLabel("<font size=1>Çizgili  </font>"));


    /***********************ndogru nnkoordinat  hnkoordinat nkoordinat***************/


    QPushButton *ndogru = new QPushButton;
    ndogru->setFixedSize(e, b);
    ndogru->setIconSize(QSize(e,b));
    //penStyleSolidLine->setFlat(true);
    ndogru->setIcon(QIcon(":icons/ndogru.png"));
    connect(ndogru, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::NDogru);

        scene->setImage(QPixmap(":icons/ndogru.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::NDogru);
 scene->donSlot();
         menu->close();
    });

    QPushButton *nnkoordinat = new QPushButton;
    nnkoordinat->setIcon(QIcon(":icons/nnkoordinat.png"));
    nnkoordinat->setFixedSize(e, b);
    nnkoordinat->setIconSize(QSize(e,b));
    //penStyleDashLine->setFlat(true);
    connect(nnkoordinat, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::NNKoordinat);
        scene->setImage(QPixmap(":icons/nnkoordinat.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::NNKoordinat);
         scene->donSlot();
        menu->close();

    });

    QPushButton *hnkoordinat = new QPushButton;
    hnkoordinat->setIcon(QIcon(":icons/hnkoordinat.png"));
    hnkoordinat->setFixedSize(e, b);
    hnkoordinat->setIconSize(QSize(e,b));
    // penStyleDotLine->setFlat(true);
    connect(hnkoordinat, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::HNKoordinat);
        scene->setImage(QPixmap(":icons/hnkoordinat.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::HNKoordinat);
        scene->donSlot();
        menu->close();

    });

    QPushButton *nkoordinat = new QPushButton;
    nkoordinat->setIcon(QIcon(":icons/nkoordinat.png"));
    nkoordinat->setFixedSize(e, b);
    nkoordinat->setIconSize(QSize(e,b));
    // penStyleDotLine->setFlat(true);
    connect(nkoordinat, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::NKoordinat);
        scene->setImage(QPixmap(":icons/nkoordinat.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::NKoordinat);
         scene->donSlot();
        menu->close();

    });
    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3->addWidget(nkoordinat);
    layout3->addWidget(hnkoordinat);
    layout3->addWidget(ndogru);
    layout3->addWidget(nnkoordinat);
    /***********************küp silindir küre pramid***************/


    QPushButton *kup = new QPushButton;
    kup->setFixedSize(e, b);
    kup->setIconSize(QSize(e,b));
    //penStyleSolidLine->setFlat(true);
    kup->setIcon(QIcon(":icons/kup.png"));
    connect(kup, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::Kup);

        scene->setImage(QPixmap(":icons/kup.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Kup);

         menu->close();
    });

    QPushButton *silindir = new QPushButton;
    silindir->setIcon(QIcon(":icons/silindir.png"));
    silindir->setFixedSize(e, b);
    silindir->setIconSize(QSize(e,b));
    //penStyleDashLine->setFlat(true);
    connect(silindir, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::Silindir);
        scene->setImage(QPixmap(":icons/silindir.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Silindir);
         menu->close();

    });

    QPushButton *pramit = new QPushButton;
    pramit->setIcon(QIcon(":icons/pramit.png"));
    pramit->setFixedSize(e, b);
    pramit->setIconSize(QSize(e,b));
    // penStyleDotLine->setFlat(true);
    connect(pramit, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::Pramit);
        scene->setImage(QPixmap(":icons/pramit.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Pramit);
        menu->close();

    });

    QPushButton *kure = new QPushButton;
    kure->setIcon(QIcon(":icons/kure.png"));
    kure->setFixedSize(e, b);
    kure->setIconSize(QSize(e,b));
    // penStyleDotLine->setFlat(true);
    connect(kure, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::Kure);
        scene->setImage(QPixmap(":icons/kure.png"));
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Kure);
        menu->close();

    });
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(kup);
    layout2->addWidget(silindir);
    layout2->addWidget(pramit);
    layout2->addWidget(kure);

    /***********************************************************/

    QPushButton *cizgi= new QPushButton;
    cizgi->setFixedSize(e, b);
    cizgi->setIconSize(QSize(e,b));
   // cizgi->setFlat(true);
    cizgi->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::Cizgi,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(cizgi, &QPushButton::clicked, [=]() {
    //    setPenStyle(Qt::SolidLine);
          setSekilType(DiagramItem::DiagramType::Cizgi);
          scene->setMode(Scene::Mode::DrawLine, DiagramItem::DiagramType::Cizgi);

           menu->close();
    });

    QPushButton *ok= new QPushButton;
    ok->setFixedSize(e, b);
    ok->setIconSize(QSize(e,b));
    //ok->setFlat(true);
    ok->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::Ok,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(ok, &QPushButton::clicked, [=]() {
   setSekilType(DiagramItem::DiagramType::Ok);
   scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Ok);

    menu->close();
    });

    QPushButton *ciftok= new QPushButton;
    ciftok->setFixedSize(e, b);
    ciftok->setIconSize(QSize(e,b));
    //ciftok->setFlat(true);
    ciftok->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::CiftOk,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(ciftok, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::CiftOk);
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::CiftOk);

         menu->close();
    });

    QPushButton *ucgen= new QPushButton;
    ucgen->setFixedSize(e, b);
    ucgen->setIconSize(QSize(e,b));
   // ucgen->setFlat(true);
    ucgen->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::Ucgen,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(ucgen, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::Ucgen);
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Ucgen);

         menu->close();
    });

    QPushButton *dortgen= new QPushButton;
    dortgen->setFixedSize(e, b);
    dortgen->setIconSize(QSize(e,b));
    //dortgen->setFlat(true);
    dortgen->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::Dortgen,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(dortgen, &QPushButton::clicked, [=]() {
       setSekilType(DiagramItem::DiagramType::Dortgen);
       scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Dortgen);

        menu->close();
    });

    QPushButton *cember= new QPushButton;
    cember->setFixedSize(e, b);
    cember->setIconSize(QSize(e,b));
   // cember->setFlat(true);
    cember->setIcon(imageEllipse(ditem->sekilStore(DiagramItem::DiagramType::Cember,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(cember, &QPushButton::clicked, [=]() {
      setSekilType(DiagramItem::DiagramType::Cember);
      scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Cember);

       menu->close();
    });

    QPushButton *baklava= new QPushButton;
    baklava->setFixedSize(e, b);
    baklava->setIconSize(QSize(e,b));
    //baklava->setFlat(true);
    baklava->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::Baklava,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(baklava, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::Baklava);
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Baklava);

         menu->close();
    });

    QPushButton *yamuk= new QPushButton;
    yamuk->setFixedSize(e, b);
    yamuk->setIconSize(QSize(e,b));
    //yamuk->setFlat(true);
    yamuk->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::Yamuk,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(yamuk, &QPushButton::clicked, [=]() {
         setSekilType(DiagramItem::DiagramType::Yamuk);
         scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Yamuk);

          menu->close();
    });

    QPushButton *besgen= new QPushButton;
    besgen->setFixedSize(e, b);
    besgen->setIconSize(QSize(e,b));
    //esgen->setFlat(true);
    besgen->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::Besgen,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(besgen, &QPushButton::clicked, [=]() {
 setSekilType(DiagramItem::DiagramType::Besgen);
 scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Besgen);

 menu->close();
 //delete menu;
 //qDebug()<<"sss";
    });

    QPushButton *altigen= new QPushButton;
    altigen->setFixedSize(e, b);
    altigen->setIconSize(QSize(e,b));
    //altigen->setFlat(true);
    altigen->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::Altigen,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(altigen, &QPushButton::clicked, [=]() {
     setSekilType(DiagramItem::DiagramType::Altigen);
     scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Altigen);

      menu->close();
    });

    QPushButton *sekizgen= new QPushButton;
    sekizgen->setFixedSize(e, b);
    sekizgen->setIconSize(QSize(e,b));
    //sekizgen->setFlat(true);
    sekizgen->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::Sekizgen,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(sekizgen, &QPushButton::clicked, [=]() {
         setSekilType(DiagramItem::DiagramType::Sekizgen);
         scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Sekizgen);

          menu->close();
    });

    QPushButton *dikucgen= new QPushButton;
    dikucgen->setFixedSize(e, b);
    dikucgen->setIconSize(QSize(e,b));
    //dikucgen->setFlat(true);
    dikucgen->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::DikUcgen,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(dikucgen, &QPushButton::clicked, [=]() {
        setSekilType(DiagramItem::DiagramType::DikUcgen);
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::DikUcgen);

     menu->close();
    });

    QPushButton *guzelyazi= new QPushButton;
    guzelyazi->setFixedSize(e, b);
    guzelyazi->setIconSize(QSize(e,b));
    //guzelyazi->setFlat(true);
    guzelyazi->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::GuzelYazi,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(guzelyazi, &QPushButton::clicked, [=]() {
         setSekilType(DiagramItem::DiagramType::GuzelYazi);
         scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::GuzelYazi);

     menu->close();
    });

    QPushButton *muzik= new QPushButton;
    muzik->setFixedSize(e, b);
    muzik->setIconSize(QSize(e,b));
    //muzik->setFlat(true);
    muzik->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::Muzik,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(muzik, &QPushButton::clicked, [=]() {
         setSekilType(DiagramItem::DiagramType::Muzik);
         scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::Muzik);

          menu->close();
    });

    QPushButton *cizgilisayfa= new QPushButton;
    cizgilisayfa->setFixedSize(e, b);
    cizgilisayfa->setIconSize(QSize(e,b));
   // cizgilisayfa->setFlat(true);
    cizgilisayfa->setIcon(image(ditem->sekilStore(DiagramItem::DiagramType::CizgiliSayfa,QRectF(QPointF(b,b),QPointF(ken-b,ken-b))),ken,ken));
    connect(cizgilisayfa, &QPushButton::clicked, [=]() {
    //    setPenStyle(Qt::SolidLine);
        setSekilType(DiagramItem::DiagramType::CizgiliSayfa);
        scene->setMode(Scene::Mode::DrawRectangle, DiagramItem::DiagramType::CizgiliSayfa);

         menu->close();
    });
    QPushButton *resimEkle= new QPushButton;
    resimEkle->setFixedSize(e, b);
    resimEkle->setIconSize(QSize(e,b));
    resimEkle->setFlat(true);
    resimEkle->setIcon(QIcon(":/icons/addimage.png"));
    connect(resimEkle, &QPushButton::clicked, [=]() {
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
         menu->close();
    });
    resimEkle->setFixedSize(e,b);
    resimEkle->setIconSize(QSize(e,b));

    sekilKalemRenkButton->setFixedSize(e,b);
    sekilKalemRenkButton->setIconSize(QSize(e,b));
    sekilZeminRenkButton->setFixedSize(e,b);
    sekilZeminRenkButton->setIconSize(QSize(e,b));

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
   // layout->setContentsMargins(20, 0, 0, 0);
    //layout->setColumnMinimumWidth(0, 37);
    //layout->addWidget(sekilLabel, 0, 1,1,3);
    layout->addWidget(sekilKalemSizePopLabel, 1, 1,1,3);
    layout->addWidget(sekilPenSize, 2, 1,1,3);

    layout->addWidget(penStyleSolidLine, 3, 1,1,1,Qt::AlignHCenter);
    layout->addWidget(penStyleDashLine, 3, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(penStyleDotLine, 3, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Çizgi</font>"),4,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Kesik Çizgi</font>"),4,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Noktalı Çizgi</font>"),4,3,1,1,Qt::AlignHCenter);

    layout->addLayout(layout1, 5, 1,1,3,Qt::AlignHCenter);
   layout->addLayout(layout3, 6, 1,1,3,Qt::AlignHCenter);
   layout->addLayout(layout2, 7, 1,1,3,Qt::AlignHCenter);
   layout->addLayout(layout0, 8, 1,1,3,Qt::AlignHCenter);
   layout->addLayout(layout00, 9, 1,1,3,Qt::AlignHCenter);

   // layout->addWidget(pergel, 5, 1,1,1,Qt::AlignHCenter);
   // layout->addWidget(cetvel, 5, 2,1,1,Qt::AlignHCenter);
   // layout->addWidget(gonye, 5, 3,1,1,Qt::AlignHCenter);
   // layout->addWidget(new QLabel("<font size=1>Pergel</font>"),6,1,1,1,Qt::AlignHCenter);
   // layout->addWidget(new QLabel("<font size=1>Cetvel</font>"),6,2,1,1,Qt::AlignHCenter);
    //layout->addWidget(new QLabel("<font size=1>Gönye</font>"),6,3,1,1,Qt::AlignHCenter);


    layout->addWidget(sekilKalemRenkButton, 10, 1,1,1,Qt::AlignHCenter);
    layout->addWidget(resimEkle, 10, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(sekilZeminRenkButton, 10, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Kenar R.</font>"),11,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Resim Ekle</font>"),11,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Zemin Rengi</font>"),11,3,1,1,Qt::AlignHCenter);

    layout->addWidget(cizgi, 13, 1,1,1,Qt::AlignHCenter);
    layout->addWidget(ok, 13, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(ciftok, 13, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Çizgi</font>"),14,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Ok</font>"),14,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Çift Ok</font>"),14,3,1,1,Qt::AlignHCenter);

    layout->addWidget(ucgen, 15, 1,1,1,Qt::AlignHCenter);
    layout->addWidget(dortgen, 15, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(cember, 15, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Üçgen</font>"),16,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Dörtgen</font>"),16,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Çember</font>"),16,3,1,1,Qt::AlignHCenter);

    layout->addWidget(baklava, 20, 1,1,1,Qt::AlignHCenter);
    layout->addWidget(yamuk, 20, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(besgen, 20, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Baklava</font>"),21,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Yamuk</font>"),21,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Beşgen</font>"),21,3,1,1,Qt::AlignHCenter);

    layout->addWidget(altigen, 25, 1,1,1,Qt::AlignHCenter);
    layout->addWidget(sekizgen, 25, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(dikucgen, 25, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Altıgen</font>"),26,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Sekizgen</font>"),26,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Dik Üçgen</font>"),26,3,1,1,Qt::AlignHCenter);

    layout->addWidget(guzelyazi, 29, 1,1,1,Qt::AlignHCenter);
    layout->addWidget(muzik, 29, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(cizgilisayfa, 29, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>G.Yazı</font>"),30,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Müzik</font>"),30,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Çizgili Sayfa</font>"),30,3,1,1,Qt::AlignHCenter);

 //   layout->setColumnStretch(10, 255);
    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);
    sekilPenSize->setStyleSheet(".QSlider::groove:Horizontal {"
                                   "background: rgba(0, 0, 0, 200);"
                                   "width:"+ QString::number(e*3.5)+"px;"
                                    "height:"+ QString::number(b/2)+"px;"
                                   "}"

                                   ".QSlider::handle:Horizontal {"
                                   "background: rgba(242, 242, 242, 95);"
                                   "border: 2px solid rgb(0,0,0);"
                                   "background: rgba(0, 0, 0, 255);"
                                   "width: "+ QString::number(e/2)+"px;"
                                   "height:"+ QString::number(b/2)+"px;"
                                    "margin:-"+ QString::number(b/4*3)+"px   0   -"+ QString::number(b/4*3)+"px   0;"
                                   "}");

    sekilPenSize->setFixedSize(QSize(e*3.5,b));
   // menu->setStyleSheet("QMenu { width: 180 px; height: 200 px;/*background: rgba(220, 220, 220, 200);*/ }");
    return menu;
}

QMenu *MainWindow::penMenu()
{
    int ken=300;
    int e=(en*0.8)/4*9;
    int b=(boy*0.6)/4*5;

    QMenu *menu = new QMenu(this);
    kalemSizePopLabel= new QLabel();
    kalemSizePopLabel->setText("Kalem Boyutu: "+QString::number(myPenSize));
    QFont ff( "Arial", 8, QFont::Normal);
    kalemSizePopLabel->setFont(ff);

   /* QSlider *penSize= new QSlider(Qt::Horizontal,menu);
    penSize->setMinimum(2);
    penSize->setMaximum(8);
    penSize->setSliderPosition(4);
    connect(penSize,SIGNAL(valueChanged(int)),this,SLOT(setPenSize(int)));
*/
    DiagramItem *ditem=new DiagramItem();

    QPushButton *penStyleSolidLine = new QPushButton;
    penStyleSolidLine->setFixedSize(e, b);
    penStyleSolidLine->setIconSize(QSize(e,b));
    //penStyleSolidLine->setFlat(true);
    penStyleSolidLine->setIcon(lineImage(ditem->sekilStore(DiagramItem::DiagramType::Kalem,QRectF(QPointF(0,0),QPointF(ken,ken))),Qt::SolidLine,ken,ken));
    connect(penStyleSolidLine, &QPushButton::clicked, [=]() {setPenStyle(Qt::SolidLine);});

    QPushButton *penStyleDashLine = new QPushButton;
    penStyleDashLine->setIcon(lineImage(ditem->sekilStore(DiagramItem::DiagramType::Kalem,QRectF(QPointF(0,0),QPointF(ken,ken))),Qt::DashLine,ken,ken));
    penStyleDashLine->setFixedSize(e, b);
    penStyleDashLine->setIconSize(QSize(e,b));
    //penStyleDashLine->setFlat(true);
    connect(penStyleDashLine, &QPushButton::clicked, [=]() {setPenStyle(Qt::DashLine);});

    QPushButton *penStyleDotLine = new QPushButton;
    penStyleDotLine->setIcon(lineImage(ditem->sekilStore(DiagramItem::DiagramType::Kalem,QRectF(QPointF(0,0),QPointF(ken,ken))),Qt::DotLine,ken,ken));
    penStyleDotLine->setFixedSize(e, b);
    penStyleDotLine->setIconSize(QSize(e,b));
   // penStyleDotLine->setFlat(true);
    connect(penStyleDotLine, &QPushButton::clicked, [=]() {setPenStyle(Qt::DotLine);});

    QPushButton *kalemSekilTanimlama= new QPushButton;
    kalemSekilTanimlama->setIcon(QIcon(":icons/smartpen.png"));
    kalemSekilTanimlama->setFixedSize(e, b);
    kalemSekilTanimlama->setIconSize(QSize(e,b));
    kalemSekilTanimlama->setFlat(true);



    kalemMenuButton->setFixedSize(e, b);
    kalemMenuButton->setIconSize(QSize(e,b));

    //connect(penBtn, &QPushButton::clicked, [=]() {/*setPenStyle(Qt::DotLine);*/
   // penBtn->setIcon(QIcon(":icons/selectpen.png"));
    //});
    QPushButton *nokta2 = new QPushButton;
    nokta2->setIcon(QIcon(":icons/nokta.png"));
    nokta2->setFixedSize(e*0.4, b);
    nokta2->setIconSize(QSize(e*0.2,b*0.2));
    nokta2->setFlat(true);
    connect(nokta2, &QPushButton::clicked, [=]() {setPenSize(1);});

    QPushButton *nokta4 = new QPushButton;
    nokta4->setIcon(QIcon(":icons/nokta.png"));
    nokta4->setFixedSize(e*0.4, b);
    nokta4->setIconSize(QSize(e*0.4,b*0.4));
    nokta4->setFlat(true);
    connect(nokta4, &QPushButton::clicked, [=]() {setPenSize(2);});

    QPushButton *nokta6 = new QPushButton;
    nokta6->setIcon(QIcon(":icons/nokta.png"));
    nokta6->setFixedSize(e*0.4, b);
    nokta6->setIconSize(QSize(e*0.6,b*0.6));
    nokta6->setFlat(true);
    connect(nokta6, &QPushButton::clicked, [=]() {setPenSize(3);});

    QPushButton *nokta8 = new QPushButton;
    nokta8->setIcon(QIcon(":icons/nokta.png"));
    nokta8->setFixedSize(e*0.4, b);
    nokta8->setIconSize(QSize(e*0.8,b*0.8));
    nokta8->setFlat(true);
    connect(nokta8, &QPushButton::clicked, [=]() {setPenSize(4);});

    QPushButton *nokta10 = new QPushButton;
    nokta10->setIcon(QIcon(":icons/nokta.png"));
    nokta10->setFixedSize(e*0.4, b);
    nokta10->setIconSize(QSize(e*1,b*1));
    nokta10->setFlat(true);
    connect(nokta10, &QPushButton::clicked, [=]() {setPenSize(5);});

    QPushButton *nokta12 = new QPushButton;
    nokta12->setIcon(QIcon(":icons/nokta.png"));
    nokta12->setFixedSize(e*0.4, b);
    nokta12->setIconSize(QSize(e*1.2,b*1.2));
    nokta12->setFlat(true);
    connect(nokta12, &QPushButton::clicked, [=]() {setPenSize(6);});

    QPushButton *nokta14 = new QPushButton;
    nokta14->setIcon(QIcon(":icons/nokta.png"));
    nokta14->setFixedSize(e*0.4, b);
    nokta14->setIconSize(QSize(e*1.4,b*1.4));
    nokta14->setFlat(true);
    connect(nokta14, &QPushButton::clicked, [=]() {setPenSize(7);});

    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
   // layout->setContentsMargins(0, 0, 0, 3);
   // layout->setColumnMinimumWidth(0, 37);

    fosforluKalemButton->setFixedSize(e, b);
    fosforluKalemButton->setIconSize(QSize(e,b));
   // geriAlButton->setFixedSize(70, 50);
    //geriAlButton->setIconSize(QSize(70,50));

    connect(kalemMenuButton, &QPushButton::clicked, [=]() {

        scene->setPopMenuStatus(false);
        menu->close();
        scene->setSekilTanimlamaStatus(false);

    });
    connect(kalemButton, &QPushButton::clicked, [=]() {

       // scene->setPopMenuStatus(false);
        //menu->close();
        scene->setSekilTanimlamaStatus(false);


    });
    connect(fosforluKalemButton, &QPushButton::clicked, [=]() {

        scene->setPopMenuStatus(false);
        menu->close();
        //kalemButtonClick();
        scene->setSekilTanimlamaStatus(false);

    });
    connect(kalemSekilTanimlama, &QPushButton::clicked, [=]()
    {
        scene->setPopMenuStatus(false);
        menu->close();
        kalemButtonClick();
        scene->setSekilTanimlamaStatus(true);
        buttonColorClear();
        palette->setColor(QPalette::Button, QColor(212,0,0,255));
       // kalemSekilTanimlama->setPalette(*palette);
        //kalemSekilTanimlama->setAutoFillBackground(true);
        kalemButton->setPalette(*palette);
        kalemButton->setAutoFillBackground(true);
        kalemButton->setIcon(QIcon(":icons/smartpen.png"));
//kalemButton->setIconSize(QSize(20,20));
         currentScreenModeSlot();
    });

    layout->addWidget(kalemSizePopLabel, 0, 1,1,3);
 //   layout->addWidget(geriAlButton,1,2,1,1);
//    layout->addWidget(new QLabel("<font size=1>Geri Al</font>"),2,2,1,1,Qt::AlignHCenter);

    layout->addWidget(kalemMenuButton,3,1,1,1,Qt::AlignHCenter);
    layout->addWidget(fosforluKalemButton,3,2,1,1,Qt::AlignHCenter);
    layout->addWidget(kalemSekilTanimlama,3,3,1,2,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Kalem</font>"),4,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Fosforlu Kalem</font>"),4,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Akıllı Kalem</font>"),4,3,1,1,Qt::AlignHCenter);

   // layout->addWidget(penSize,5,1,1,3,Qt::AlignHCenter);

    QHBoxLayout *layout1 = new QHBoxLayout;
         layout1->addWidget(nokta2);
         layout1->addWidget(nokta4);
         layout1->addWidget(nokta6);
         layout1->addWidget(nokta8);
         layout1->addWidget(nokta10);
         layout1->addWidget(nokta12);
         layout1->addWidget(nokta14);


    layout->addLayout(layout1, 6, 1,1,3,Qt::AlignHCenter);
    //layout->addWidget(nokta4, 6, 2,1,1,Qt::AlignHCenter);
    //layout->addWidget(nokta8, 6, 3,1,1,Qt::AlignHCenter);
    //layout->addWidget(nokta12, 6, 4,1,1,Qt::AlignHCenter);

    layout->addWidget(penStyleSolidLine, 7, 1,1,1,Qt::AlignHCenter);
    layout->addWidget(penStyleDashLine, 7, 2,1,1,Qt::AlignHCenter);
    layout->addWidget(penStyleDotLine, 7, 3,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Düz</font>"),8,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Kesik</font>"),8,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Noktalı</font>"),8,3,1,1,Qt::AlignHCenter);


  //  layout->setColumnStretch(6, 255);

    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
  //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);
   /* penSize->setStyleSheet(".QSlider::groove:Horizontal {"
                                   "background: rgba(0, 0, 0, 200);"
                                   "width:"+QString::number(e*4)+"px;"
                                    "height: "+QString::number(b/2)+"px;"
                                   "}"

                                   ".QSlider::handle:Horizontal {"
                                   "background: rgba(242, 242, 242, 95);"
                                   "border: 2px solid rgb(0,0,0);"
                                   "background: rgba(0, 0, 0, 255);"
                                   "width: "+QString::number(e/2)+"px;"
                                   "height: "+QString::number(b)+"px;"
                                    "margin:-"+QString::number(e/8*3)+"px   0   -"+QString::number(b/8*3)+"px   0;"
                                   "}");
*/
   // penSize->setFixedSize(QSize(e*4,b));
    //menu->setStyleSheet("QMenu { width: 290 px; height: 250 px; }");
return menu;
}

QMenu *MainWindow::zeminMenu()
{  //int e=en;
   // int b=boy;
    int e=(en*0.8)/4*9;
    int b=(boy*0.6)/4*5;

    QMenu *menu = new QMenu(this);
    QLabel  *zeminLabel= new QLabel();
    zeminLabel->setText("Arkaplan Seçenekleri");
    QFont ff( "Arial", 8, QFont::Normal);
    zeminLabel->setFont(ff);

    gridSizePopLabel= new QLabel();
    gridSizePopLabel->setText("Grid Boyutu: "+QString::number(myGridSize));
    gridSizePopLabel->setFont(ff);

    QSlider *penSize= new QSlider(Qt::Horizontal,menu);
    penSize->setMinimum(2);
    penSize->setMaximum(8);
    penSize->setSliderPosition(4);
    connect(penSize,SIGNAL(valueChanged(int)),this,SLOT(setGridSize(int)));


    auto widget = new QWidget;
    auto layout = new QGridLayout(widget);
    //layout->setContentsMargins(0, 0, 0, 3);
    //layout->setColumnMinimumWidth(0, 37);
    zeminSeffafButton->setFixedSize(e, b);zeminSeffafButton->setIconSize(QSize(e,b));
    zeminSiyahButton->setFixedSize(e, b);zeminSiyahButton->setIconSize(QSize(e,b));
    zeminBeyazButton->setFixedSize(e, b);zeminBeyazButton->setIconSize(QSize(e,b));
    gridYatayButton->setFixedSize(e, b);gridYatayButton->setIconSize(QSize(e,b));
    gridDikeyButton->setFixedSize(e, b);gridDikeyButton->setIconSize(QSize(e,b));
    gridDisableButton->setFixedSize(e, b);gridDisableButton->setIconSize(QSize(e,b));
    zeminCustomColorButton->setFixedSize(e, b);zeminCustomColorButton->setIconSize(QSize(e,b));
    zeminMuzikButton->setFixedSize(e, b);zeminMuzikButton->setIconSize(QSize(e,b));
    zeminGuzelYaziButton->setFixedSize(e, b);zeminGuzelYaziButton->setIconSize(QSize(e,b));
    openButton->setFixedSize(e, b);openButton->setIconSize(QSize(e,b));

    DiagramItem *ditem=new DiagramItem();
    int ken=300;
    QPushButton *zeminCizgiliSayfaButton = new QPushButton;
    zeminCizgiliSayfaButton->setIcon(QIcon(":icons/cizgiliSayfa.png"));
    zeminCizgiliSayfaButton->setFixedSize(e, b);
    zeminCizgiliSayfaButton->setIconSize(QSize(e,b));
    zeminCizgiliSayfaButton->setFlat(true);
    connect(zeminCizgiliSayfaButton, &QPushButton::clicked, [=]()
    {
          myZeminColor=QColor(0,0,0,0);
        gridDisableButtonClick();
        DiagramItem *ditem=new DiagramItem();
        mySekilType=DiagramItem::DiagramType::CizgiliSayfa;
        QPixmap pim(zeminImage(ditem->sekilStore(mySekilType,QRectF(QPointF(0,0),QPointF(this->width(),this->height()))),this->width(),this->height(),myGridColor,2));
        scene->setForegroundBrush(pim);

        QPixmap pixMap = view->grab(view->sceneRect().toRect());
        QPalette palet;
        palet.setBrush(QPalette::Background,pixMap);
        this->setPalette(palet);

        //setSekilPenStyle(Qt::DashLine);
    });
/*    QPushButton *zeminTemizleButton = new QPushButton;
    zeminTemizleButton->setIcon(QIcon(":icons/zeminTemizle.png"));
    zeminTemizleButton->setFixedSize(e, b);
    zeminTemizleButton->setIconSize(QSize(e,b));
    zeminTemizleButton->setFlat(true);
    connect(zeminTemizleButton, &QPushButton::clicked, [=]()
    {
       scene->setForegroundBrush(QColor(0,0,0,0));
        scene->setPopMenuStatus(false);
      //  menu->close();
      //  gridOnOffButtonClick();

    });*/

    QPushButton *gridRenkButton = new QPushButton;
    gridRenkButton->setIcon(QIcon(":icons/gridRenk.png"));
    gridRenkButton->setFixedSize(e, b);
    gridRenkButton->setIconSize(QSize(e,b));
    gridRenkButton->setFlat(true);
    palette->setColor(QPalette::Button, myGridColor);
    gridRenkButton->setPalette(*palette);
    gridRenkButton->update();

    connect(gridRenkButton, &QPushButton::clicked, [=]()
    {
      /*  scene->setPopMenuStatus(false);

        Qt::WindowFlags flags = 0;
        flags |= Qt::Dialog;
        flags |= Qt::X11BypassWindowManagerHint;
        QColorDialog abc(this);
        abc.setWindowFlags(flags);
        abc.setCurrentColor(myGridColor);
        abc.exec();

        QColor newColor = abc.selectedColor();
         if (newColor.isValid())
          {
            /// qDebug()<<"renk seçildi"<<scene->sceneGridYatay<<scene->sceneGridDikey<<scene->sceneGuzelYazi;
            myGridColor = QColor(newColor.red(),newColor.green(),newColor.blue(),128);
            palette->setColor(QPalette::Button, myGridColor);
            gridRenkButton->setPalette(*palette);
            gridRenkButton->setAutoFillBackground(true);
            gridRenkButton->update();
            if(scene->sceneGridYatay) gridYatayButtonClick(scene->sceneGridYatay);
            if(scene->sceneGridDikey) gridDikeyButtonClick(scene->sceneGridDikey);
            if(scene->sceneGuzelYazi) zeminGuzelYaziButtonClick(scene->sceneGuzelYazi);

               }**/
        auto *colorMenus=colorMenu("myGridColor");
        colorMenus->show();
        colorMenus->hide();
        currentScreenModeSlot();
        scene->setPopMenuStatus(true);
        colorMenus->exec(mapToGlobal(zeminMenus->pos()-QPoint(colorMenus->width(),0)));
        scene->setPopMenuStatus(false);

        palette->setColor(QPalette::Button, myGridColor);
        gridRenkButton->setPalette(*palette);
        gridRenkButton->setAutoFillBackground(true);
        gridRenkButton->update();
        if(scene->sceneGridYatay) gridYatayButtonClick(scene->sceneGridYatay);
        if(scene->sceneGridDikey) gridDikeyButtonClick(scene->sceneGridDikey);
        if(scene->sceneGuzelYazi) zeminGuzelYaziButtonClick(scene->sceneGuzelYazi);

       /* palette->setColor(QPalette::Button,mySekilZeminColor);
        sekilZeminRenkButton->setIcon(QIcon(":icons/sekilZeminRenk.png"));
        sekilZeminRenkButton->setAutoFillBackground(true);
        sekilZeminRenkButton->setPalette(*palette);
        sekilZeminRenkButton->update();
        scene->setSekilZeminColor(mySekilZeminColor);*/


    });

    connect(zeminSeffafButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});
    connect(zeminSiyahButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});
    connect(zeminBeyazButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});
    connect(zeminCustomColorButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});
    connect(zeminCizgiliSayfaButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});
    connect(zeminMuzikButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});
    connect(zeminGuzelYaziButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});
  ///  connect(zeminTemizleButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});
    connect(gridRenkButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});
    connect(gridYatayButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});
    connect(gridDikeyButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});
    connect(gridDisableButton, &QPushButton::clicked, [=](){scene->setPopMenuStatus(false);/* menu->close();*/});

    layout->addWidget(zeminLabel, 0, 1,1,3);
    layout->addWidget(gridSizePopLabel, 1, 1,1,3);
    layout->addWidget(zeminSeffafButton,2,1,1,1,Qt::AlignHCenter);
    layout->addWidget(zeminSiyahButton,2,2,1,1,Qt::AlignHCenter);
    layout->addWidget(zeminBeyazButton,2,3,1,1,Qt::AlignHCenter);
    layout->addWidget(zeminCustomColorButton,2,4,1,1,Qt::AlignHCenter);


    layout->addWidget(new QLabel("<font size=1>Şeffaf Tahta</font>"),3,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Siyah Tahta</font>"),3,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Beyaz Tahta</font>"),3,3,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Zemin Rengi Seç</font>"),3,4,1,1,Qt::AlignHCenter);


    layout->addWidget(zeminCizgiliSayfaButton,5,1,1,1,Qt::AlignHCenter);
    layout->addWidget(zeminMuzikButton,5,2,1,1,Qt::AlignHCenter);
    layout->addWidget(zeminGuzelYaziButton,5,3,1,1,Qt::AlignHCenter);
    layout->addWidget(openButton,5,4,1,1,Qt::AlignHCenter);

    layout->addWidget(new QLabel("<font size=1>Çizgi Deseni</font>"),6,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Müzik Deseni</font>"),6,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Güzelyazı</font>"),6,3,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Desen Resim Ekle</font>"),6,4,1,1,Qt::AlignHCenter);

    layout->addWidget(penSize,10,1,1,4,Qt::AlignHCenter);

    layout->addWidget(gridRenkButton,15,1,1,1,Qt::AlignHCenter);
    layout->addWidget(gridYatayButton,15,2,1,1,Qt::AlignHCenter);
    layout->addWidget(gridDikeyButton,15,3,1,1,Qt::AlignHCenter);
    layout->addWidget(gridDisableButton,15,4,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Çizgi Rengi Seç</font>"),16,1,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Yatay Çizgi</font>"),16,2,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Dikey Çizgi</font>"),16,3,1,1,Qt::AlignHCenter);
    layout->addWidget(new QLabel("<font size=1>Çizgi Temizle</font>"),16,4,1,1,Qt::AlignHCenter);

    //openButton->show();
    //openButton->resize(e,b);
   // layout->addWidget( openButton,17,2,1,1,Qt::AlignHCenter);
   // layout->addWidget(new QLabel("<font size=1>Resim Ekle</font>"),18,2,1,1,Qt::AlignHCenter);

    //layout->setColumnStretch(6, 255);
    // add a widget action to the context menu
    auto wa = new QWidgetAction(this);
    //  wa->setIcon(QIcon(":/icon1"));
    wa->setDefaultWidget(widget);
    menu->addAction(wa);

    penSize->setStyleSheet(".QSlider::groove:Horizontal {"
                                   "background: rgba(0, 0, 0, 200);"
                                   "width:"+QString::number(e*4.5)+"px;"
                                    "height: "+QString::number(b/2)+"px;"
                                   "}"

                                   ".QSlider::handle:Horizontal {"
                                   "background: rgba(242, 242, 242, 95);"
                                   "border: 2px solid rgb(0,0,0);"
                                   "background: rgba(0, 0, 0, 255);"
                                   "width: "+QString::number(e/2)+"px;"
                                   "height: "+QString::number(b)+"px;"
                                    "margin:-"+QString::number(e/8*3)+"px   0   -"+QString::number(b/8*3)+"px   0;"
                                   "}");

    penSize->setFixedSize(QSize(e*4.5,b));

   // menu->setStyleSheet("QMenu { width: 340 px; height: 410 px; }");
return menu;
}




#endif // POPMENU_H
