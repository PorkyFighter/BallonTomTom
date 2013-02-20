#include "fenetreprincipale.h"


FenetrePrincipale::FenetrePrincipale() : QMainWindow()
    {
        // le widget dans lequel tout s'affiche
        widget_general = new QWidget;
        QHBoxLayout * qbl_general = new QHBoxLayout;
        widget_general->setLayout(qbl_general);
        this->setCentralWidget(widget_general);
        this->setWindowTitle("SarkoZizi 3000!");//Titre de fenetre principale
        //exemple de creation d'une zone ou mettre boutons...
        qbl_general->addWidget(BuildGroupBoxControle());
        // exemple de création d'un menu
        QMenu *menuFichier = menuBar()->addMenu("&Fichier");
            QAction *actionScore = new QAction("&Score", this);
            menuFichier->addAction(actionScore);

            QMenu *fichiersRecents = menuFichier->addMenu("Fichiers &récents");
            fichiersRecents->addAction("Fichier bidon 1.txt");
            fichiersRecents->addAction("Fichier bidon 2.txt");
            fichiersRecents->addAction("Fichier bidon 3.txt");

            QAction *actionQuitter = new QAction("&Quitter", this);
            menuFichier->addAction(actionQuitter);
            actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
            actionQuitter->setIcon(QIcon("C:/Users/user/Downloads/quitter.png"));
            connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

        QMenu *menuEdition = menuBar()->addMenu("&Edition");

        QMenu *menuAffichage = menuBar()->addMenu("&Affichage");

        QMenu *menuAide = menuBar()->addMenu("&Aide");
            QAction *actionHelp = new QAction("&Help", this);
            actionHelp->setShortcut(QKeySequence("Ctrl+H"));
            menuAide->addAction(actionHelp);
            actionHelp->setIcon(QIcon("C:/Users/user/Downloads/aide.png"));
            connect(actionHelp,  SIGNAL(triggered()), this, SLOT(monSlot1()));

        scene = new MyScene();
        vue = new MyView();
        vue->setCursor(Qt::BlankCursor);
        vue -> setScene(scene);
        qbl_general ->addWidget(vue);
        vue->setMouseTracking(true);
    }

FenetrePrincipale::~FenetrePrincipale() {}

QGroupBox * FenetrePrincipale::BuildGroupBoxControle() {
        QGroupBox * qgb = new QGroupBox(tr(""));

        QVBoxLayout * vbl = new QVBoxLayout;

        button2 = new QPushButton("Nouveau ballon");
        button2 ->setFont (QFont ("Arial", 8, QFont::Bold));
        button2 -> setMinimumSize (40,20);
        connect(button2, SIGNAL(clicked()), this, SLOT(slot_changeBallon()));
        vbl -> addWidget(button2);

        button3 = new QPushButton("Nouveau personnage");
        button3 ->setFont (QFont ("Arial", 8, QFont::Bold));
        button3 -> setMinimumSize (40,20);
        connect(button3, SIGNAL(clicked()), this, SLOT(slot_changeTete()));
        vbl -> addWidget(button3);

        button4 = new QPushButton("Nouveau fond");
        button4 ->setFont (QFont ("Arial", 8, QFont::Bold));
        button4 -> setMinimumSize (40,20);
        connect(button4, SIGNAL(clicked()), this, SLOT(slot_changeFond()));
        vbl -> addWidget(button4);

        qgb->setLayout(vbl);

        return qgb;
}

void FenetrePrincipale::slot_changeTete(){
    QString filename = QFileDialog::getOpenFileName(this,"Open Tete","/Cours_itii5_c++/Tete","120*120 pixels(*.png *.jpg *.bmp)");
    scene ->changementPersonnage(filename);
}

void FenetrePrincipale::slot_changeBallon(){
    QString filename = QFileDialog::getOpenFileName(this,"Open Ballon","/Cours_itii5_c++/Ballon","70*70 pixels (*.png *.jpg *.bmp)");
    scene->changementBallon(filename);
}

void FenetrePrincipale::slot_changeFond(){
    QString filename = QFileDialog::getOpenFileName(this,"Open Fond","/Cours_itii5_c++/Fond","800*600 pixels (*.png *.jpg *.bmp)");
    scene->changementBackground(filename);
}

void FenetrePrincipale::monSlot1()
    {
        qDebug()<<"Appuie sur Help";
        QDesktopServices::openUrl(QUrl("http://www.google.com"));
    }

void FenetrePrincipale::keyPressEvent(QKeyEvent *event)
{
   if (event->key() == Qt::Key_Escape)
   {
        qApp->quit();
   }
}
