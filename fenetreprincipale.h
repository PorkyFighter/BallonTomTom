#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QMenu>
#include <QGroupBox>
#include <QMenuBar>
#include <QtGui>
#include <myscene.h>
#include <myview.h>
#include <QPushButton.h>
#include <QFileDialog>
#include <QAction>
#include <QUrl>
#include <QDesktopServices>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QRectF>
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
    
public:
    FenetrePrincipale();
    ~FenetrePrincipale();
    QGroupBox * BuildGroupBoxControle();

public slots:
    void slot_changeTete();
    void slot_changeBallon();
    void slot_changeFond();
    void monSlot1();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QWidget * widget_general;
    QMenu * menuFichier;
    MyScene * scene;
    QPushButton * button2;
    QPushButton * button3;
    QPushButton * button4;
    MyView * vue;

};

#endif // FENETREPRINCIPALE_H
