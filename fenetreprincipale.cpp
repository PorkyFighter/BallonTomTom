#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

/*
 *  Utilisation de fenetreprincipale.ui, fichier contenant une partie de l'interface graphique, créée à l'aide de Qt Designer
 */

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this); //Installation du fichier .ui (créé avec Qt Designer)
    ui->centralWidget->setLayout(ui->qbl_general); //Ajout du layout principal (VHBoxLayout)
    this->setCentralWidget(ui->centralWidget); //Définition de centralWidget comme widget principal
    this->setWindowTitle("Lunar Module Defender");//Titre de fenetre principale
    scene = new MyScene(); //Création d'objet de classe MyScene (voir myscene.cpp et myscene.h)== QGraphicsScene modifié
    vue = new MyView(); //Création d'objet de classe MyView, (voir myview.h) == QGraphicsView modifié
    vue->setCursor(Qt::BlankCursor); //Curseur invisible lorsqu'on survole vue
    vue -> setScene(scene); //Selection de l'objet scene que la vue doit afficher
    ui->qbl_general ->addWidget(vue); //ajout du widget vue au VHBoxLayout principal
    vue->setMouseTracking(true); //Activation de la capture du pointeur souris

    //Gestion des interruptions entre interface graphique et programme
    connect(ui->buttonFond, SIGNAL(clicked()), this, SLOT(slot_changeFond()));
    connect(ui->buttonBallon, SIGNAL(clicked()), this, SLOT(slot_changeBallon()));
    connect(ui->buttonJoueur, SIGNAL(clicked()), this, SLOT(slot_changeTete()));
    connect(scene, SIGNAL(setLabelActuel(QString)), ui->labelActuel, SLOT(setText(QString)));
    connect(scene, SIGNAL(setLabelDernier(QString)), ui->labelDernier, SLOT(setText(QString)));
    connect(scene, SIGNAL(setLabelRecord(QString)), ui->labelRecord, SLOT(setText(QString)));
    connect(ui->sliderVitesse, SIGNAL(valueChanged(int)), scene, SLOT(changementVitesse(int)));
    connect(ui->sliderTailleBallon, SIGNAL(valueChanged(int)), scene, SLOT(changementTailleBallon(int)));

}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

void FenetrePrincipale::slot_changeTete()
    {
        qDebug()<<"Clic sur Nouveau Personnage";
        QString filename = QFileDialog::getOpenFileName(this,"Open Tete","/Cours_itii5_c++/Tete","120*120 pixels(*.png *.jpg *.bmp *.gif)");
        scene->changementPersonnage(filename);
    }

void FenetrePrincipale::slot_changeBallon()
    {
        qDebug()<<"Clic sur Nouveau Ballon";
        QString filename = QFileDialog::getOpenFileName(this,"Open Ballon","/Cours_itii5_c++/Ballon","70*70 pixels (*.png *.jpg *.bmp)");
        scene->changementBallon(filename);
    }

void FenetrePrincipale::slot_changeFond()
    {
        qDebug()<<"Clic sur Nouveau Fond";
        QString filename = QFileDialog::getOpenFileName(this,"Open Fond","/Cours_itii5_c++/Fond","800*600 pixels (*.png *.jpg *.bmp)");
        scene->changementBackground(filename);
    }

void FenetrePrincipale::slot_help()
    {
        qDebug()<<"Clic sur Help";
        QDesktopServices::openUrl(QUrl("http://www.google.com"));
    }

void FenetrePrincipale::keyPressEvent(QKeyEvent *event) //Gestion d'évènements
    {
       if (event->key() == Qt::Key_Escape) //Si on a appuyé sur Echap
           {
                qApp->quit();
           }
    }
