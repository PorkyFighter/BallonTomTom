#include "myscene.h"

    int mode=0;
    int y=0;
    int x=0;
    int xTete = 300;


MyScene::MyScene() : QGraphicsScene()
    {
        changementBackground("C:/Users/PorkyFighter/Documents/ProjetsQt/Tom/fond.png");
        //QGraphicsRectItem * qgri = new QGraphicsRectItem(10, 10, 300, 300); //pour créer un rectangle sur le background
       // this->addItem(qgri); //affiche le rectangle
        ballon = new QGraphicsPixmapItem(QPixmap("C:/Users/PorkyFighter/Documents/ProjetsQt/Tom/tete.png"));
        ballon->setTransformOriginPoint(QPointF(35,35));    //Origine au centre du ballon
        this->addItem(ballon);                              //Ajout du ballon a la scene

        tete = new QGraphicsPixmapItem(QPixmap("C:/Users/PorkyFighter/Documents/ProjetsQt/Tom/joueur.png"));
        tete->setTransformOriginPoint(QPointF(60,60));      //Origine au centre du personnage
        this->addItem(tete);                                //Ajout du personnage a la scene
        tete->setPos(300, 470);                             //Positionnement du personnage

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer-> start(5);                                   //Creation d'un signal appelant la fonction update toutes les 5ms
    }

MyScene::~MyScene(){}

void MyScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);//macro Qt pour utiliser rect sinon il bug
    painter->drawPixmap(QPointF(0,0), pixbackground, sceneRect());
}

void MyScene::update(){             //Fonction appellée toutes les 5ms

    extern int xTete;
    //qDebug() << QString("height: %1 width: %2").arg(height()).arg(width());
    //qDebug() << QString("x: %1 y: %2").arg(x).arg(y);
    //qDebug() << QString("objet: x: %1 y: %2").arg(tete->x()).arg(tete->y());

    int coteGauche = tete->x()-60;
    int coteDroite = tete->x()+60;
    if (mode == 0) //Sud Est
    {
        x = ballon -> x()+1;
        y = ballon -> y()+1;
        if(y >= 530)
        {
            mode=1;
            qDebug() << "Perdu!";
        }
        else if((x-50 >= coteGauche && x <= coteDroite)&&(y ==410))
        {
            mode=1;
            qDebug() << "Tete!";
        }
        else if(x >= 730) mode=3;
        else if((x-50 >= coteGauche && x <= coteDroite&&(y >= 410)))mode=3;
    }

    if (mode == 1) //Nord Est
    {
        x = ballon -> x()+1;
        y = ballon -> y()-1;
        if(y <= 0) mode=0;
        else if(x >= 730 || (x-50 >= coteGauche && x <= coteDroite&&(y >= 410))) mode=2;
    }

    if (mode == 2) //Nord Ouest
    {
        x = ballon -> x()-1;
        y = ballon -> y()-1;
        if(y <= 0) mode=3;
        else if(x <= 0 ||(x-50 >= coteGauche && x <= coteDroite&&(y >= 410))) mode=1;
    }

    if (mode == 3) //Sud Ouest
    {
        x = ballon -> x()-1;
        y = ballon -> y()+1;
        if(y >= 530)
        {
            mode=2;
            qDebug() << "Perdu!";
        }
        else if((x-50 >= coteGauche && x <= coteDroite)&&(y ==410))
        {
            mode=2;
            qDebug() << "Tete!";
        }
        else if(x <= 0) mode=0;
        else if((x-50 >= coteGauche && x <= coteDroite&&(y >= 410)))mode=0;
    }

    ballon->setRotation(x);
    ballon->setPos(x, y);
    tete->setX(xTete-50);
}

void MyScene::keyPressEvent(QKeyEvent *event)   //evenement d'appui sur une touche du clavier
{
    extern int xTete;
    if(event->key() == Qt::Key_Right)           //Si la touche appuyée est la flèche droite
        {
            if(xTete<=740)xTete += 10;
            //qDebug() << "droite!";
        }
    else if (event->key() == Qt::Key_Left)      //Si la touche appuyée est la flèche gauche
            {
                if(xTete>=30)xTete -= 10;
            //qDebug() << "gauche!";
            }
    else if (event->key() == Qt::Key_Escape)    ////Si la touche appuyée est "echap"
            {
                qApp->quit();
            }
}

void MyScene::changementBackground(QString filename) //change l'image de fond par l'image se trouvant à l'adresse locale "filename"
{
    if(!filename.isEmpty())
    {
        pixbackground.load(filename);
        setBackgroundBrush(QBrush(pixbackground));
        setSceneRect(0,0,pixbackground.width(),pixbackground.height());
    }
}

void MyScene::changementBallon(QString filename) //change l'image du ballon par l'image se trouvant à l'adresse locale "filename"
{
    if(!filename.isEmpty())ballon->setPixmap(QPixmap(filename));
}

void MyScene::changementPersonnage(QString filename) //change l'image du personnage par l'image se trouvant à l'adresse locale "filename"
{
    if(!filename.isEmpty())tete->setPixmap(QPixmap(filename));
}
