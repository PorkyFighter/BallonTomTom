#include "myscene.h"
/*
 *  Utilisation de Fichiers.qrc, conteneur de ressources ou se trouvent les images du projet
 */
    //Variables globales (accessibles depuis chaque fonction de MyScene)

    int xTete = 300;
    int scoreActuel = 0;
    int record = 0;
    int vitesseBallon = 5;
    float tailleBallon = 1;
    int sensBallonX = 1;
    int sensBallonY = 1;


MyScene::MyScene() : QGraphicsScene()
    {
        changementBackground("C:/Users/PorkyFighter/Documents/ProjetsQt/Tom/fond.png");

        //Ajout d'un fond en tant que QGraphicsPixmapItem, pour pouvoir ajouter un effet de rotation à cet objet
        fond = new QGraphicsPixmapItem(QPixmap("C:/Users/PorkyFighter/Documents/ProjetsQt/Tom/fond4.png"));
        fond->setTransformOriginPoint(QPointF(1000,1000));      //Origine au centre du fond
        this->addItem(fond);                                    //Ajout du fond a la scene
        fond->setPos(-500, -500);                               //Changement position
        fond->setScale(1.1);                                    //Petit zoom


        //Ajout d'une image de terre fixe
        terre = new QGraphicsPixmapItem(QPixmap("C:/Users/PorkyFighter/Documents/ProjetsQt/Tom/terre.png"));
        //terre->setTransformOriginPoint(QPointF(35,35));    //Origine au centre du ballon
        this->addItem(terre);
        terre->setPos(-2, 530);
        terre->setScale(1.1);

        //Ajout du ballon avec calque alpha (effet de transparence)
        ballon = new QGraphicsPixmapItem(QPixmap("C:/Users/PorkyFighter/Documents/ProjetsQt/Tom/ballon.png"));
        ballon->setTransformOriginPoint(QPointF(35,35));    //Origine au centre du ballon
        this->addItem(ballon);                              //Ajout du ballon a la scene
        ballon->setScale(1);

        //Ajout du personnage à contrôler
        tete = new QGraphicsPixmapItem(QPixmap("C:/Users/PorkyFighter/Documents/ProjetsQt/Tom/joueur4.png"));
        //tete->setTransformOriginPoint(QPointF(60,60));      //Origine au centre du personnage
        this->addItem(tete);                                //Ajout du personnage a la scene
        tete->setPos(300, 480);                             //Positionnement du personnage


        //Creation d'un signal appelant la fonction update toutes les 5ms
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer-> start(5);

    }

MyScene::~MyScene(){}

void MyScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);//macro Qt pour utiliser rect sinon il bug
    painter->drawPixmap(QPointF(0,0), pixbackground, sceneRect());
}

void MyScene::update(){             //Fonction appellée toutes les 5ms
    extern int xTete;
    static float  rotFond; //Création de variable statique afin qu'elle ne soit pas réinitialisée à chaque nouvel appel de update()
    int demiBallon = 30*tailleBallon; //Moitié de largeur du ballon
    int coteGauche = tete->x()-20-demiBallon; //Coordonnée du coté gauche du personnage
    int coteDroite = tete->x()+80+demiBallon; //Coordonnée du coté droit du personnage
    int xBallon = ballon -> x(); //Coordonnée en x du ballon
    int yBallon = ballon -> y(); //Coordonnée en y du ballon
    rotFond += 0.01; //Ajout de rotation du fond afin de donner un effet (rotFond = rotFond + 0.01)
    tete->setX(xTete); //Positionnement du personnage avec les coordonnées en x du pointeur souris


    //Si le ballon touche un des cotés, il repart dans la direction inverse (en modifiant le paramètre x ou y, et de la vitesse vitesseBallon)
    if(xBallon <= -30+demiBallon) //Si le ballon touche le coté gauche
    {
        sensBallonX = vitesseBallon;
    }
    else if(xBallon >= 760-demiBallon) //Si le ballon touche le coté droit
    {
        sensBallonX = -vitesseBallon;
    }
    if(yBallon <= -30+demiBallon) //Si le ballon touche le haut
    {
        sensBallonY = vitesseBallon;
    }
    else if(yBallon >= 565-demiBallon) //Si le ballon touche le bas == perdu
    {
        sensBallonY =-vitesseBallon;
        if(scoreActuel > record)
        {
            record = scoreActuel;
            emit setLabelRecord(QString("%1").arg(scoreActuel));    //Emet un signal pour changer le qLabel "setLabelRecord"
        }
        emit setLabelDernier(QString("%1").arg(scoreActuel));       //Emet un signal pour changer le qLabel "setLabelDernier"
        scoreActuel = 0;
        emit setLabelActuel(QString("%1").arg(scoreActuel));        //Emet un signal pour changer le qLabel "setLabelActuel"
        //qDebug() << "Perdu!";
    }
    if((xBallon >= coteGauche && xBallon <= coteDroite)&&(yBallon >= 445-demiBallon)&&(yBallon <=460-demiBallon)) //si le ballon touche le dessus du personnage
    {
        sensBallonY =-vitesseBallon;
        scoreActuel++;
        emit setLabelActuel(QString("%1").arg(scoreActuel)); //Emet un signal pour changer le qLabel "setLabelActuel"
        qDebug() << "Tete!";
    }

    if((xBallon >= coteGauche && xBallon <= coteGauche+15)&&(yBallon >=445-demiBallon)) //si le ballon touche le coté gauche du personnage
    {
        sensBallonX = -vitesseBallon;
    }

    if((xBallon <= coteDroite && xBallon >= coteDroite-15)&&(yBallon >=445-demiBallon)) //si le ballon touche le coté droit du personnage
    {
        sensBallonX = vitesseBallon;
    }

    if((xBallon >= coteGauche && xBallon < coteGauche+demiBallon)&&(yBallon >=445-demiBallon)) //si le ballon se trouve dans le personnage, coté gauche
    {
        ballon->setPos(coteGauche-demiBallon,yBallon);
    }

    if((xBallon <= coteDroite && xBallon >= coteDroite-demiBallon)&&(yBallon >=445-demiBallon)) //si le ballon se trouve dans le personnage, coté droit
    {
        ballon->setPos(coteDroite+demiBallon,yBallon);
    }

    fond->setRotation(rotFond); //Rotation du ciel étoilé
    ballon->setRotation(xBallon+sensBallonX); //Rotation du ballon
    ballon->setPos(xBallon+sensBallonX, yBallon+sensBallonY); //Position du ballon
    //qDebug()<<QString("x: %1 y: %2").arg(x).arg(y);
    //qDebug()<<QString("xBallon: %1 yBallon: %2").arg(xBallon).arg(yBallon);

}

void MyScene::keyPressEvent(QKeyEvent *event)   //evenement d'appui sur une touche du clavier
{
    extern int xTete;
    if(event->key() == Qt::Key_Right)           //Si la touche appuyée est la flèche droite
        {
            if(xTete<=740)xTete += 10;          //Sécurité, le défilement du personnage s'arrète lorsqu'on touche un coté
            //qDebug() << "droite!";
        }
    else if (event->key() == Qt::Key_Left)      //Si la touche appuyée est la flèche gauche
            {
                if(xTete>=30)xTete -= 10;       //Sécurité, le défilement du personnage s'arrète lorsqu'on touche un coté
            //qDebug() << "gauche!";
            }
    else if (event->key() == Qt::Key_Escape)    ////Si la touche appuyée est "echap"
            {
                qApp->quit();
            }
}

void MyScene::changementBackground(QString filename) //change l'image de fond par l'image se trouvant à l'adresse locale "filename"
{
    if(!filename.isEmpty()) //Si filename contient une adresse
    {
        pixbackground.load(filename); //chargement de l'image fond noir envoyée par la fonction (800*600)
        setBackgroundBrush(QBrush(pixbackground)); //Affichage de cette image, transformée en QBrush
        setSceneRect(0,0,pixbackground.width(),pixbackground.height()); //Redimensionnement
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

void MyScene::changementVitesse(int vitesse) //fonction d'accès pour pouvoir changer une variable de MyScene depuis une interruption extérieure
{
    vitesseBallon = vitesse;
    qDebug() << QString("vitesse = %1 vitesseBallon = %2").arg(vitesse).arg(vitesseBallon);
}

void MyScene::changementTailleBallon(int taille) //fonction d'accès pour pouvoir changer une variable de MyScene depuis une interruption extérieure
{
    tailleBallon = taille/10.0;
    ballon->setScale(tailleBallon);
}
