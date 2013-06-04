#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include "myscene.h"
#include "myview.h"

namespace Ui {
class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();
    
public slots:
    void slot_changeTete();
    void slot_changeBallon();
    void slot_changeFond();
    void slot_help();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::FenetrePrincipale *ui;
    MyScene * scene;
    MyView * vue;
};

#endif // FENETREPRINCIPALE_H
