#ifndef MYSCENE_H
#define MYSCENE_H

#include <QtGui>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QMenu>
#include <QGroupBox>
#include <QMenuBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QPixmap>
#include <QSize>
#include <QLabel>
#include <QBrush>
#include <QPainter>
#include <QRectF>
#include <QGraphicsItem>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMouseEvent>


class MyScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MyScene();
    ~MyScene();
    void drawBackground(QPainter *painter, const QRectF &rect);
    void changementBackground(QString filename);
    void changementBallon(QString filename);
    void changementPersonnage(QString filename);



public slots:
    void update();
    void changementVitesse(int);
    void changementTailleBallon(int);


signals:
    void setLabelActuel(QString);
    void setLabelDernier(QString);
    void setLabelRecord(QString);


protected:
       void keyPressEvent(QKeyEvent *event);


private:
       QPixmap pixbackground;
       QGraphicsPixmapItem * ballon;
       QGraphicsPixmapItem * tete;
       QGraphicsPixmapItem *fond;
       QGraphicsPixmapItem *terre;
       QKeyEvent * touche;
       QTimer * timer;
};

#endif // MYSCENE_H
