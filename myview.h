#ifndef MYVIEW_H
#define MYVIEW_H

#include <QtGui>
#include <QResizeEvent>
#include <QGraphicsView>

class MyView : public QGraphicsView
{
    Q_OBJECT

public:
    MyView(){}
    ~MyView(){}

protected:
    virtual void resizeEvent (QResizeEvent * event) {
        this->fitInView(sceneRect());
    }
    void mouseMoveEvent(QMouseEvent * event){
        extern int xTete;
        if(event->x() <= 750 && event->x() >= 20) xTete = (event->x());
        //qDebug() << QString("xTete:%1").arg(xTete);
    }
};

#endif // MYVIEW_H
