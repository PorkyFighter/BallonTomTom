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
        event->isAccepted(); //Inutile, juste pour enlever les warnings
    }
    void mouseMoveEvent(QMouseEvent * event){
        extern int xTete;
        if(event->x() <= 680 && event->x() >= 0) xTete = (event->x());
    }
};

#endif // MYVIEW_H
