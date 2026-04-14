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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "scene.h"
#include <QAction>
#include <QGraphicsPolygonItem>
#include<gridlines.h>
#include<QPushButton>
#include <QDebug>
#include<filecrud.h>
#include<depo.h>
#include<poppler/qt5/poppler-qt5.h>
#include <QMovie>
#include <QThread>
#include<diagramtextitem.h>

class QButtonGroup;
class QAbstractButton;
class QToolBox;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QPalette;
class QPixmap;
class QLabel;
class QToolButton;
class QAction;
class QListWidget;
class QListWidgetItem;
class QSpinBox;
class QTimer;
class QProgressBar;


class name
{
public:
    name() {}
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow();
      ~MainWindow();
    int en;
    int boy;
    QPixmap image(const QPolygonF &myPolygon, int w, int h) const;
    QPixmap zeminImage(const QPolygonF &myPolygon, int w, int h, QColor color, int pensize) const;

    QPixmap lineImage(const QPolygonF &myPolygon,const Qt::PenStyle &stl,int w,int h) const;
    QPixmap imageEllipse(const QPolygonF &myPolygon, int w, int h) const;
    QPolygonF polygon() const { return myPolygon; }
    QPixmap PixItem(QGraphicsItem *item);
    QImage zImage(int w, int h, QColor color) const;

public slots:

private slots:
    void promterCloseSignalSlot(QString text);
    void pageButtonClick(int index);
     QMenu* colorMenu(QString colorType);
    void pdfLoaderPage(int pageIndex);
     void zamanlama();
    void timerCopySlot();
    void saatslot();
    void timerGizleSlot();
    void currentScreenModeSlot();
    //void clockSlot();
    void siyahButtonClick();
    void kirmiziButtonClick();
    void kalemRenkButtonClick();
    void maviButtonClick();
  //  void penColorButtonClick();
    void kalemButtonClick();
    void kalemPopButtonClick();
    void kalemMenuButtonClick();
    void fosforluKalemButtonClick();
    void silButtonClick();
    void silPopButtonClick();
    void silMenuButtonClick();
    void temizleButtonClick();
    void temizleMenuButtonClick();
    void ekranButtonClick();
    void kalemKapatButtonClick();
    void sekilButtonClick();
    void sekilPopButtonClick();
    void zoomfitSayfaButtonClick();
    void zoompozitifSayfaButtonClick();

    void zoomnegatifSayfaButtonClick();

    void zeminButtonClick();
    void zeminPopButtonClick();
    void geriAlButtonClick();
    void sayfaListeIcon();
    void ileriSayfaButtonClick();
    void geriSayfaButtonClick();
    void silSayfaButtonClick();
    void ekleSayfaButtonClick(int inserIndex, bool pdfObjectAdded, int pdfPageIndex);
    void screenClickButtonClick();
    void pagePopButtonClick();
    void sekilZeminRenkButtonClick();
    void sekilKalemRenkButtonClick();
    void zeminSeffafButtonClick();
    void zeminBeyazButtonClick();
    void zeminSiyahButtonClick();
    void zeminCustomColorButtonClick();
    void zeminCustomColorInitButtonClick();
    void gridDisableButtonClick();
    void gridYatayButtonClick(bool toggle);
    void gridDikeyButtonClick(bool toggle);
    void gizleGosterButtonClick();
    void secButtonClick();
    void tasiButtonClick();
    void setPenSize(int size);
    void setGridSize(int size);
    void setSekilPenSize(int size);
    void buttonColorClear();
    void setEraseSize(int size);
    void setPenAlpha(int size);
    void setPenStyle(const Qt::PenStyle &styl);
    void setSekilPenStyle(const Qt::PenStyle &styl);
    void setSekilType(const DiagramItem::DiagramType &typ);
    void infoButtonClick();
    void klavyeButtonClick();
    void saveButtonClick();
    void openButtonClick();
    void kalemEgitim();

    void zeminMuzikButtonClick();
    void zeminGuzelYaziButtonClick(bool toggle);
    //void ileriGeriSayfa();
    void sekilButtonIconSlot();
    void initPen();
    void kalemLayout();
    void resizeSlot();
protected:
     void loading();
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void moveEvent(QMoveEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void clearImage();
    QImage copyImage(const QImage & input, const QRect & path);
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);


private:

    int pdfPageList=0;
    int ekliSayfa=1;
    bool ileriButonClickState=false;
    Poppler::Document *doc;
    int pdfPageCount=0;
    int pdfFirstPageNumber=0;
    int pdfLastPageNumber=0;

    float msx,msy,mex,mey;
    int pdfobjectnumber=0;
    QPen pen;
    int rad=0;
    QImage img;
    QPoint lastPoint;
    QPointF startPoint;

    bool drawingMain=false;

    bool penWriteStatus=false;
    bool sayacShow=false;
     qint64 saniye;
    bool gizleGoster;
    bool screenDesktop;
   /// bool gridYatay;
   /// bool gridDikey;
   /// bool guzelYazi;
    bool clock;
    int myZeminType;//0=seffaf 1=siyah 2=beyaz 3=custom
    void setPenColor(const QColor &newColor);
    void setZeminColor(const QColor &newColor);
    QLabel *sayac;

    GridLines * gridLines; ///< this is my custom QGraphicsItem
    int myPenSize;
    int mySekilPenSize;
    int myGridSize;
    int myEraseSize;
    QColor myPenColor;
    QColor myGridColor;
    QColor myZeminColor;
    QColor mySekilZeminColor;
    QColor mySekilKalemColor;
    //QColor myGridColor;

    Qt::PenStyle myPenStyle;
    Qt::PenStyle mySekilPenStyle;
    DiagramItem::DiagramType mySekilType;
    Scene::Mode currentScreenMode;
    Scene::Mode tempcurrentScreenMode;
    int myPenAlpha;
    bool tasi;
    bool sekilZeminRenkDrm;
    bool sekilKalemRenkDrm;
    bool kalemRenkDrm;
    bool screenClickDrm;

    QPolygonF myPolygon;
    int kutuHeight;
    int kutuWidth;
    int kutuLeft;
    int kutuTop;
    bool copyState;

       QVBoxLayout *kokLayot;
       QVBoxLayout *verticalLayout;
       QHBoxLayout *horzinalLayout;
       QHBoxLayout *analayot;
       QWidget *buyukKutu;
       QWidget *pageListwg;
       QHBoxLayout *screenlayout;

    void createToolBox();
    void createToolbars();

    QMenu *penMenu();
    QMenu *eraseMenu();
    QMenu *sekilMenu();
    QMenu *zeminMenu();
    QMenu *pageMenu();

    QMenu *ayarMenu();
    QMenu *colorMenu();

    QMenu *sekilMenus;
    QMenu *zeminMenus;

    QGraphicsView* view;
    Scene* scene;
    Scene* _scene;
    //QList<QGraphicsScene> sceneSayfa;
    QList<Scene*> sceneSayfa;
    int sceneSayfaNumber;
    int sceneSayfaActiveNumber;
    QListWidget* sayfaListeView;





    QPalette *palette;
   /// QRect mainScreenSize;
 ///   QRect currentGeometry;
  QPushButton *zoomfitSayfaButton;
    QPushButton *zoompozitifSayfaButton;
      QPushButton *zoomnegatifSayfaButton;
  //  QPushButton *colorButton;
    QPushButton *siyahButton;
    QPushButton *kirmiziButton;
    QPushButton *kalemRenkButton;
    QPushButton *maviButton;
    QPushButton *kalemButton;
    QPushButton *kalemPopButton;
    QPushButton *kalemMenuButton;
    QPushButton *silButton;
    QPushButton *silPopButton;
    QPushButton *silMenuButton;
    QPushButton *sekilButton;
    QPushButton *sekilPopButton;

    QPushButton *zeminButton;
    QPushButton *zeminPopButton;
    QPushButton *temizleMenuButton;
    QPushButton *temizleButton;
    QPushButton *ekranButton;
    QPushButton *fosforluKalemButton;
    QPushButton *kalemKapatButton;
    QPushButton *sekilZeminRenkButton;
    QPushButton *sekilKalemRenkButton;
   // QPushButton *ileriSayfaButton;
    //QPushButton *geriSayfaButton;
    //QPushButton *silSayfaButton;
    //QPushButton *ekleSayfaButton;
   // QPushButton *pageButton;
  //  QPushButton *pagePopButton;

    QPushButton *ayarButton;
    QPushButton *screenClickButton;

    QPushButton *zeminSeffafButton;
    QPushButton *zeminBeyazButton;
    QPushButton *zeminSiyahButton;
    QPushButton *zeminCustomColorButton;
    QPushButton *gridDisableButton;
    QPushButton *gridYatayButton;
    QPushButton *gridDikeyButton;
    QPushButton *gizleGosterButton;
    QPushButton *tasiButton;
    QPushButton *secButton;

    QPushButton *infoButton;
    QPushButton *klavyeButton;
    QPushButton *saveButton;
    QPushButton *openButton;
    QPushButton *printButton;
    QPushButton *zeminMuzikButton;
    QPushButton *zeminGuzelYaziButton;
    QPushButton *backSayfaButton;
    QPushButton *nextSayfaButton;
    QPushButton *delSayfaButton;
    QPushButton *addSayfaButton;

    QPushButton *copyButton;
    //QPushButton *saveButton;
    QPushButton *addShapeButton;
    QPushButton *cButton;
    QPushButton *sayacStartButton;
    QPushButton *sayacCloseButton;
    QSpinBox *sure;
    QTimer *saat;
    QTimer *timerCopy;
    QTimer *timerGizle;
    QProgressBar *bar;

    QPushButton *ileriAlButton;
    QPushButton *geriAlButton;
    QLabel *kalemSizePopLabel;
    QLabel *eraseSizePopLabel;
    QLabel *pageNumberPopLabel;

    QLabel *gridSizePopLabel;
    QLabel *sekilKalemSizePopLabel;
    QLabel *ileriGeriSayfaLabel;
    QPushButton *clockButton;
    QPushButton *yazdirButton;
    QPushButton *loadPdfButton;
    QPushButton *savePdfButton;
    QToolButton *screenbtn ;
    QList<QToolButton*> pageList;
    int zamanlamastart=0;
     QWidget *wust;
      QWidget *wsol;
        QVector<QPointF> wpoints;
  double factorial(double n)
        {
            if (n == 0)
               return 1;
            return n * factorial(n - 1);
        }
  float distance(const QPointF& pt1, const QPointF& pt2)
      {
          float hd = (pt1.x() - pt2.x()) * (pt1.x() - pt2.x());
          float vd = (pt1.y() - pt2.y()) * (pt1.y() - pt2.y());
          return std::sqrt(hd + vd);
      }

      QPointF getLineStart(const QPointF& pt1, const QPointF& pt2)
      {
          QPointF pt;
          float rat = 10.0 / distance(pt1, pt2);
          if (rat > 0.5) {
              rat = 0.5;
          }
          pt.setX((1.0 - rat) * pt1.x() + rat * pt2.x());
          pt.setY((1.0 - rat) * pt1.y() + rat * pt2.y());
          return pt;
      }

      QPointF getLineEnd(const QPointF& pt1, const QPointF& pt2)
      {
          QPointF pt;
          float rat = 10.0 / distance(pt1, pt2);
          if (rat > 0.5) {
              rat = 0.5;
          }
          pt.setX(rat * pt1.x() + (1.0 - rat)*pt2.x());
          pt.setY(rat * pt1.y() + (1.0 - rat)*pt2.y());
          return pt;
      }


    //butonlar ayarlanıyor
    void iconButton()
    {
        kalemButton->setIcon(QIcon(":icons/pen.png"));
        kalemMenuButton->setIcon(QIcon(":icons/pen.png"));
        kalemPopButton->setIcon(QIcon(":icons/pop.png"));
        fosforluKalemButton->setIcon(QIcon(":icons/fosforlupen.png"));
        silButton->setIcon(QIcon(":icons/erase.png"));
        silMenuButton->setIcon(QIcon(":icons/erase.png"));
        silPopButton->setIcon(QIcon(":icons/pop.png"));
        DiagramItem *ditem=new DiagramItem();
        int ken=300;
        mySekilType=DiagramItem::DiagramType::Cizgi;
        QPixmap pixmap(image(ditem->sekilStore(mySekilType,QRectF(QPointF(20,50),QPointF(ken-70,ken-70))),ken,ken));
         sekilButton->setIcon(pixmap);
        sekilPopButton->setIcon(QIcon(":icons/pop.png"));
        zeminButton->setIcon(QIcon(":icons/zemin.png"));
        zeminPopButton->setIcon(QIcon(":icons/pop.png"));
        ayarButton->setIcon(QIcon(":icons/settings.png"));
        temizleMenuButton->setIcon(QIcon(":icons/clear.png"));
        temizleButton->setIcon(QIcon(":icons/clear.png"));
        ekranButton->setIcon(QIcon(":icons/screendesktop.png"));
        kalemKapatButton->setIcon(QIcon(":icons/close.png"));
        secButton->setIcon(QIcon(":icons/pointer.png"));
        tasiButton->setIcon(QIcon(":icons/tasi.png"));
        klavyeButton->setIcon(QIcon(":icons/klavye.png"));
        infoButton->setIcon(QIcon(":icons/about.png"));
        saveButton->setIcon(QIcon(":icons/save.png"));
        openButton->setIcon(QIcon(":icons/open.png"));
        //ileriSayfaButton->setIcon(QIcon(":icons/next.png"));
       // geriSayfaButton->setIcon(QIcon(":icons/back.png"));
       // silSayfaButton->setIcon(QIcon(":icons/deletepage.png"));
       // ekleSayfaButton->setIcon(QIcon(":icons/insertpage.png"));

        geriAlButton->setIcon(QIcon(":icons/undo.png"));
     //   ->setIcon(QIcon(":icons/page.png"));
      //  pagePopButton->setIcon(QIcon(":icons/pop.png"));
        zeminSeffafButton->setIcon(QIcon(":icons/transparanboard.png"));
        zeminBeyazButton->setIcon(QIcon(":icons/whiteboard.png"));
        zeminSiyahButton->setIcon(QIcon(":icons/blackboard.png"));
        zeminCustomColorButton->setIcon(QIcon(":icons/zeminCustomColor.png"));
        gridDisableButton->setIcon(QIcon(":icons/gridonoff.png"));
        gridYatayButton->setIcon(QIcon(":icons/gridyatay.png"));
        gridDikeyButton->setIcon(QIcon(":icons/griddikey.png"));

        zeminMuzikButton->setIcon(QIcon(":icons/iconmuzik.png"));
        zeminGuzelYaziButton->setIcon(QIcon(":icons/iconguzelyazi.png"));
    }
    void createButton()
    {


      /*  sayacStartButton= new QPushButton(this);
        sayacStartButton->hide();
        sayacCloseButton= new QPushButton(this);
        sayacCloseButton->hide();*/
        ileriAlButton = new QPushButton(this);

      //  colorButton = new QPushButton(this);
        siyahButton = new QPushButton(this);
        kirmiziButton = new QPushButton(this);
        kalemRenkButton = new QPushButton(this);
        maviButton = new QPushButton(this);
        kalemButton = new QPushButton(this);
        kalemPopButton = new QPushButton(this);
        kalemMenuButton = new QPushButton(this);
        fosforluKalemButton = new QPushButton(this);
        silButton = new QPushButton(this);
        silPopButton = new QPushButton(this);
        silMenuButton = new QPushButton(this);
        sekilButton = new QPushButton(this);
        sekilPopButton = new QPushButton(this);
        ayarButton = new QPushButton(this);
       // ayarPopButton = new QPushButton(this);

        zeminButton = new QPushButton(this);
        zeminPopButton = new QPushButton(this);
        temizleMenuButton = new QPushButton(this);

        temizleButton = new QPushButton(this);
        ekranButton = new QPushButton(this);
        kalemKapatButton = new QPushButton(this);
        sekilZeminRenkButton = new QPushButton(this);
        sekilKalemRenkButton = new QPushButton(this);
        //ileriSayfaButton = new QPushButton(this);

        //geriSayfaButton = new QPushButton(this);
        //silSayfaButton = new QPushButton(this);
        //ekleSayfaButton = new QPushButton(this);
        //ileriAlButton = new QPushButton(this);
        geriAlButton = new QPushButton(this);
      //   = new QPushButton(this);
       // pagePopButton = new QPushButton(this);

         zeminSeffafButton= new QPushButton(this);
         zeminBeyazButton= new QPushButton(this);
         zeminSiyahButton= new QPushButton(this);
         zeminCustomColorButton= new QPushButton(this);
         gridDisableButton= new QPushButton(this);
         gridYatayButton= new QPushButton(this);
         gridDikeyButton= new QPushButton(this);
         gizleGosterButton= new QPushButton(this);
         secButton=new QPushButton(this);
         tasiButton=new QPushButton(this);
         infoButton=new QPushButton(this);
         klavyeButton=new QPushButton(this);
         saveButton=new QPushButton(this);
         openButton=new QPushButton(this);
           zeminGuzelYaziButton=new QPushButton(this);
         zeminMuzikButton=new QPushButton(this);


     //   colorButton->setFlat(true);
        siyahButton->setFlat(true);
        kirmiziButton->setFlat(true);
        kalemRenkButton->setFlat(true);
        maviButton->setFlat(true);
        kalemButton->setFlat(true);
        kalemPopButton->setFlat(true);
        kalemMenuButton->setFlat(true);
        fosforluKalemButton->setFlat(true);
        silButton->setFlat(true);
        silPopButton->setFlat(true);
        silMenuButton->setFlat(true);
        sekilButton->setFlat(true);
        sekilPopButton->setFlat(true);
        ayarButton->setFlat(true);
       // ayarPopButton->setFlat(true);

        zeminButton->setFlat(true);
        zeminPopButton->setFlat(true);
        temizleMenuButton->setFlat(true);
        temizleButton->setFlat(true);
        ekranButton->setFlat(true);
        kalemKapatButton->setFlat(true);
        sekilZeminRenkButton->setFlat(true);
        sekilKalemRenkButton->setFlat(true);
        //ileriSayfaButton->setFlat(true);
       // geriSayfaButton->setFlat(true);
       // silSayfaButton->setFlat(true);
        //ekleSayfaButton->setFlat(true);
        //ileriAlButton->setFlat(true);
        geriAlButton->setFlat(true);
       // ->setFlat(true);
       // pagePopButton->setFlat(true);


        zeminSeffafButton->setFlat(true);
        zeminBeyazButton->setFlat(true);
        zeminSiyahButton->setFlat(true);
        zeminCustomColorButton->setFlat(true);
        gridDisableButton->setFlat(true);
        gridYatayButton->setFlat(true);
        gridDikeyButton->setFlat(true);
        gizleGosterButton->setFlat(true);
        secButton->setFlat(true);
        tasiButton->setFlat(true);
        klavyeButton->setFlat(true);
        infoButton->setFlat(true);
        saveButton->setFlat(true);
        openButton->setFlat(true);
       zeminGuzelYaziButton->setFlat(true);
        zeminMuzikButton->setFlat(true);
        float cp=1.5;
        float pcp=0.5;
      //  colorButton->setFixedSize(QSize(en*cp,boy/2));
        siyahButton->setFixedSize(QSize(en*cp,boy/2));
        kirmiziButton->setFixedSize(QSize(en*cp,boy/2));
        kalemRenkButton->setFixedSize(QSize(en*cp,boy/2));
        maviButton->setFixedSize(QSize(en*cp,boy/2));
        kalemButton->setFixedSize(QSize(en*cp,boy));
        kalemMenuButton->setFixedSize(QSize(en,boy));
        kalemPopButton->setFixedSize(QSize(en*pcp,boy));
        fosforluKalemButton->setFixedSize(QSize(en,boy));
        silButton->setFixedSize(QSize(en*cp,boy));
        silPopButton->setFixedSize(QSize(en*pcp,boy));
        silMenuButton->setFixedSize(QSize(en,boy));
        sekilButton->setFixedSize(QSize(en*cp,boy));
        sekilPopButton->setFixedSize(QSize(en*pcp,boy));
        ayarButton->setFixedSize(QSize(en*cp,boy));
        //ayarPopButton->setFixedSize(QSize(en/2,boy));

        zeminButton->setFixedSize(QSize(en*cp,boy));
        zeminPopButton->setFixedSize(QSize(en*pcp,boy));

        temizleButton->setFixedSize(QSize(en*cp,boy));
        ekranButton->setFixedSize(QSize(en*cp,boy));
        kalemKapatButton->setFixedSize(QSize(en*cp,boy));
        sekilZeminRenkButton->setFixedSize(QSize(en,boy));
        sekilKalemRenkButton->setFixedSize(QSize(en,boy));
        //ileriSayfaButton->setFixedSize(QSize(en,boy));
       // geriSayfaButton->setFixedSize(QSize(en,boy));
       // silSayfaButton->setFixedSize(QSize(en,boy));
       // ekleSayfaButton->setFixedSize(QSize(en,boy));
        //ileriAlButton->setFixedSize(QSize(en,boy));
        geriAlButton->setFixedSize(QSize(en,boy));
       // ->setFixedSize(QSize(en*cp,boy));

        //pagePopButton->setFixedSize(QSize(en*pcp,boy)//);


        zeminSeffafButton->setFixedSize(QSize(en,boy));
        zeminBeyazButton->setFixedSize(QSize(en,boy));
        zeminSiyahButton->setFixedSize(QSize(en,boy));
        zeminCustomColorButton->setFixedSize(QSize(en,boy));
        gridDisableButton->setFixedSize(QSize(en,boy));
        gridYatayButton->setFixedSize(QSize(en,boy));
        gridDikeyButton->setFixedSize(QSize(en,boy));
        gizleGosterButton->setFixedSize(QSize(en*cp,boy));
        secButton->setFixedSize(QSize(en*cp,boy));
        tasiButton->setFixedSize(QSize(en,boy));
        klavyeButton->setFixedSize(QSize(en,boy));
        infoButton->setFixedSize(QSize(en,boy));
      //  saveButton->setFixedSize(QSize(en,boy));
        openButton->setFixedSize(QSize(en,boy));
        zeminGuzelYaziButton->setFixedSize(QSize(en,boy));
        zeminMuzikButton->setFixedSize(QSize(en,boy));

    //    colorButton->setIconSize(QSize(en,boy/2));
        siyahButton->setIconSize(QSize(en,boy/2));
        kirmiziButton->setIconSize(QSize(en,boy/2));
        kalemRenkButton->setIconSize(QSize(en,boy/2));
        maviButton->setIconSize(QSize(en,boy/2));
        kalemButton->setIconSize(QSize(en*0.7,boy));
        kalemMenuButton->setIconSize(QSize(en,boy));
        kalemPopButton->setIconSize(QSize(en,boy));
        fosforluKalemButton->setIconSize(QSize(en,boy));
        silButton->setIconSize(QSize(en*0.7,boy));
        silPopButton->setIconSize(QSize(en,boy));
        silMenuButton->setIconSize(QSize(en,boy));
        sekilButton->setIconSize(QSize(en*0.7,boy));
        sekilPopButton->setIconSize(QSize(en,boy));

        zeminButton->setIconSize(QSize(en*0.7,boy));
        zeminPopButton->setIconSize(QSize(en,boy));
        ayarButton->setIconSize(QSize(en*cp,boy));
      //  ayarPopButton->setIconSize(QSize(en,boy));

        temizleButton->setIconSize(QSize(en,boy));
        ekranButton->setIconSize(QSize(en,boy));
        kalemKapatButton->setIconSize(QSize(en,boy));
        sekilZeminRenkButton->setIconSize(QSize(en,boy));
        sekilKalemRenkButton->setIconSize(QSize(en,boy));
        //ileriSayfaButton->setIconSize(QSize(en,boy));
        //geriSayfaButton->setIconSize(QSize(en,boy));
        //ekleSayfaButton->setIconSize(QSize(en,boy));
        //silSayfaButton->setIconSize(QSize(en,boy));
        //ileriAlButton->setIconSize(QSize(en,boy));
        geriAlButton->setIconSize(QSize(en*0.6,boy));
     //   ->setIconSize(QSize(en*0.7,boy));
       // pagePopButton->setIconSize(QSize(en,boy));

        zeminSeffafButton->setIconSize(QSize(en,boy));
        zeminBeyazButton->setIconSize(QSize(en,boy));
        zeminSiyahButton->setIconSize(QSize(en,boy));
        zeminCustomColorButton->setIconSize(QSize(en,boy));
        gridDisableButton->setIconSize(QSize(en,boy));
        gridYatayButton->setIconSize(QSize(en,boy));
        gridDikeyButton->setIconSize(QSize(en,boy));
      //  gizleGosterButton->setIconSize(QSize(en+en+10,boy));
        secButton->setIconSize(QSize(en,boy));
        tasiButton->setIconSize(QSize(en,boy));
        klavyeButton->setIconSize(QSize(en,boy));
        infoButton->setIconSize(QSize(en,boy));
        //saveButton->setIconSize(QSize(en,boy));
        openButton->setIconSize(QSize(en,boy));
        zeminMuzikButton->setIconSize(QSize(en,boy));
        zeminGuzelYaziButton->setIconSize(QSize(en,boy));



        palette = new QPalette();
        palette->setColor(QPalette::Button, myPenColor);
       // colorButton->setPalette(*palette);
        //colorButton->setAutoFillBackground(true);

        palette->setColor(QPalette::Button, QColor(0,0,0,255));
        siyahButton->setPalette(*palette);
        siyahButton->setAutoFillBackground(true);

        palette->setColor(QPalette::Button, QColor(255,0,0,255));
        kirmiziButton->setPalette(*palette);
        kirmiziButton->setAutoFillBackground(true);

       /* palette->setColor(QPalette::Button, QColor(0,198,0,255));
        yesilButton->setPalette(*palette);
        yesilButton->setAutoFillBackground(true);
*/
        palette->setColor(QPalette::Button, QColor(0,0,255,255));
        maviButton->setPalette(*palette);
        maviButton->setAutoFillBackground(true);

        palette->setColor(QPalette::Button, QColor(0,0,0,0));
        zeminCustomColorButton->setPalette(*palette);
        zeminCustomColorButton->setAutoFillBackground(true);
        if(!kalemRenkDrm)
        {
           kalemRenkButton->setIcon(QIcon(":icons/kalemRenk.png"));
            // palette = new QPalette();
           kalemRenkButton->setAutoFillBackground(true);

            palette->setColor(QPalette::Button, myPenColor);
            kalemRenkButton->setPalette(*palette);
            kalemRenkButton->update();
          //  scene->setBrush(QColor(0,0,0,0));
        }
        else
        {
            kalemRenkButton->setIcon(QIcon(":icons/kalemRenk.png"));
            // palette = new QPalette();
             kalemRenkButton->setAutoFillBackground(true);
            palette->setColor(QPalette::Button, QColor(0,0,0,0));
            kalemRenkButton->setPalette(*palette);
            kalemRenkButton->update();
           // scene->setBrush(QColor(0,0,0,0));
        }

        if(!sekilZeminRenkDrm)
        {
           sekilZeminRenkButton->setIcon(QIcon(":icons/sekilZeminRenk.png"));
            // palette = new QPalette();
            palette->setColor(QPalette::Button, mySekilZeminColor);
            sekilZeminRenkButton->setPalette(*palette);
            sekilZeminRenkButton->update();
          //  scene->setBrush(QColor(0,0,0,0));
        }
        else
        {
            sekilZeminRenkButton->setIcon(QIcon(":icons/sekilZeminRenk.png"));
            // palette = new QPalette();
            palette->setColor(QPalette::Button, QColor(0,0,0,0));
            sekilZeminRenkButton->setPalette(*palette);
            sekilZeminRenkButton->update();
           // scene->setBrush(QColor(0,0,0,0));
        }
        if(sekilKalemRenkDrm)
        {
            sekilKalemRenkButton->setIcon(QIcon(":icons/sekilKalemRenk.png"));
            // palette = new QPalette();
            palette->setColor(QPalette::Button, mySekilKalemColor);
            sekilKalemRenkButton->setPalette(*palette);
            sekilKalemRenkButton->update();
          //  scene->setBrush(QColor(0,0,0,0));
        }
        else
        {
            sekilKalemRenkButton->setIcon(QIcon(":icons/sekilKalemRenk.png"));
            // palette = new QPalette();
            palette->setColor(QPalette::Button, QColor(0,0,0,0));
            sekilKalemRenkButton->setPalette(*palette);
            sekilKalemRenkButton->update();
           // scene->setBrush(QColor(0,0,0,0));
        }
        //iconButton();
        connect(siyahButton,SIGNAL(clicked()),this,SLOT(siyahButtonClick()));
        connect(kirmiziButton,SIGNAL(clicked()),this,SLOT(kirmiziButtonClick()));
        connect(kalemRenkButton,SIGNAL(clicked()),this,SLOT(kalemRenkButtonClick()));
        connect(maviButton,SIGNAL(clicked()),this,SLOT(maviButtonClick()));
       // connect(colorButton,SIGNAL(clicked()),this,SLOT(penColorButtonClick()));
        connect(kalemButton,SIGNAL(clicked()),this,SLOT(kalemButtonClick()));
        connect(kalemMenuButton,SIGNAL(clicked()),this,SLOT(kalemButtonClick()));
        //kalemPopButton->setPopupMode(QPushButton::MenuButtonPopup);
        //connect(kalemPopButton,SIGNAL(clicked()),this,SLOT(kalemButtonClick()));
        connect(fosforluKalemButton,SIGNAL(clicked()),this,SLOT(fosforluKalemButtonClick()));
        connect(silButton,SIGNAL(clicked()),this,SLOT(silButtonClick()));
        connect(silMenuButton,SIGNAL(clicked()),this,SLOT(silButtonClick()));

        connect(sekilButton,SIGNAL(clicked()),this,SLOT(sekilButtonClick()));
        connect(zeminButton,SIGNAL(clicked()),this,SLOT(zeminButtonClick()));

        connect(temizleMenuButton,SIGNAL(clicked()),this,SLOT(temizleButtonClick()));
        connect(temizleButton,SIGNAL(clicked()),this,SLOT(temizleButtonClick()));
        connect(ekranButton,SIGNAL(clicked()),this,SLOT(ekranButtonClick()));
        connect(kalemKapatButton,SIGNAL(clicked()),this,SLOT(kalemKapatButtonClick()));
        connect(sekilZeminRenkButton,SIGNAL(clicked()),this,SLOT(sekilZeminRenkButtonClick()));
        connect(sekilKalemRenkButton,SIGNAL(clicked()),this,SLOT(sekilKalemRenkButtonClick()));

        //connect(ileriSayfaButton,SIGNAL(clicked()),this,SLOT(ileriSayfaButtonClick()));
        //connect(geriSayfaButton,SIGNAL(clicked()),this,SLOT(geriSayfaButtonClick()));
        //connect(silSayfaButton,SIGNAL(clicked()),this,SLOT(silSayfaButtonClick()));
        //connect(ekleSayfaButton,SIGNAL(clicked()),this,SLOT(ekleSayfaButtonClick()));
     //   connect(pageButton,SIGNAL(clicked()),this,SLOT(ekleSayfaButtonClick()));

        connect(zeminButton,SIGNAL(clicked()),this,SLOT(zeminSeffafButtonClick()));
        connect(geriAlButton,SIGNAL(clicked()),this,SLOT(geriAlButtonClick()));
        connect(zeminSeffafButton,SIGNAL(clicked()),this,SLOT(zeminSeffafButtonClick()));
        connect(zeminSiyahButton,SIGNAL(clicked()),this,SLOT(zeminSiyahButtonClick()));
        connect(zeminBeyazButton,SIGNAL(clicked()),this,SLOT(zeminBeyazButtonClick()));
        connect(zeminCustomColorButton,SIGNAL(clicked()),this,SLOT(zeminCustomColorButtonClick()));
        connect(gridDisableButton,SIGNAL(clicked()),this,SLOT(gridDisableButtonClick()));
        connect(gridYatayButton,SIGNAL(clicked(bool)),this,SLOT(gridYatayButtonClick(bool)));
        connect(gridDikeyButton,SIGNAL(clicked(bool)),this,SLOT(gridDikeyButtonClick(bool)));
        connect(gizleGosterButton,SIGNAL(clicked()),this,SLOT(gizleGosterButtonClick()));

        connect(secButton,SIGNAL(clicked()),this,SLOT(secButtonClick()));
        connect(tasiButton,SIGNAL(clicked()),this,SLOT(tasiButtonClick()));
        connect(klavyeButton,SIGNAL(clicked()),this,SLOT(klavyeButtonClick()));
        connect(infoButton,SIGNAL(clicked()),this,SLOT(infoButtonClick()));
        connect(saveButton,SIGNAL(clicked()),this,SLOT(saveButtonClick()));
        connect(openButton,SIGNAL(clicked()),this,SLOT(openButtonClick()));

         connect(zeminMuzikButton,SIGNAL(clicked()),this,SLOT(zeminMuzikButtonClick()));
         connect(zeminGuzelYaziButton,SIGNAL(clicked(bool)),this,SLOT(zeminGuzelYaziButtonClick(bool)));

//qDebug() <<"Butonlar Oluşturuldu..";
    }
    void showPenButton()
    {
        siyahButton->show();
        kirmiziButton->show();
        maviButton->show();
        kalemRenkButton->show();
        kalemButton->show();
        kalemPopButton->show();
        fosforluKalemButton->show();
        silButton->show();
        silMenuButton->show();
        silPopButton->show();
        sekilButton->show();
        sekilPopButton->show();
        kalemMenuButton->show();
        zeminButton->show();
        zeminPopButton->show();
        ayarButton->show();
        temizleButton->show();


    }
    void showZeminButton()
    {
        zeminSeffafButton->show();
        zeminBeyazButton->show();
        zeminSiyahButton->show();
        zeminCustomColorButton->show();
        gridDisableButton->show();
        gridYatayButton->show();
        gridDikeyButton->show();
        gridDikeyButton->show();
        zeminMuzikButton->show();
        zeminGuzelYaziButton->show();
        //zeminColorButton->show();
        //ileriSayfaButton->show();
       // geriSayfaButton->show();
        //silSayfaButton->show();
        //ekleSayfaButton->show();
        ileriAlButton->show();
        geriAlButton->show();
       // pageButton->show();
       // pagePopButton->show();
        copyButton->show();
        klavyeButton->show();
        infoButton->show();


    }

    void showPcButton()
    {
       // openButton->show();
        saveButton->show();
        yazdirButton->show();
        savePdfButton->show();
        loadPdfButton->show();
        addShapeButton->show();

    }
    void hideButton()
    {
        ileriAlButton->hide();
        siyahButton->hide();
        kirmiziButton->hide();
        maviButton->hide();
        kalemRenkButton->hide();
        ayarButton->hide();
        kalemButton->hide();
        kalemPopButton->hide();
        kalemMenuButton->hide();
        fosforluKalemButton->hide();
        silButton->hide();
        silMenuButton->hide();
        silPopButton->hide();
        sekilButton->hide();
        sekilPopButton->hide();
        temizleButton->hide();
        zeminPopButton->hide();
        zeminButton->hide();

        klavyeButton->hide();
        infoButton->hide();
        saveButton->hide();
       // openButton->hide();

        zeminSeffafButton->hide();
        zeminBeyazButton->hide();
        zeminSiyahButton->hide();
        zeminCustomColorButton->hide();
        gridDisableButton->hide();
        gridYatayButton->hide();
        gridDikeyButton->hide();
        zeminMuzikButton->hide();
        zeminGuzelYaziButton->hide();
        geriAlButton->hide();
        copyButton->hide();

    }


};



#endif // MAINWINDOW_H
