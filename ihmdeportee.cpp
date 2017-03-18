#include "ihmdeportee.h"
#include "ui_ihmdeportee.h"


IHMdeportee::IHMdeportee(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IHMdeportee)
{

    ui->setupUi(this);

    lancerTimer();
    updateValeurs();
    calendrier();
    layout();
    sizeWidget();
    styleWidget();
    //writeResume();




    /*int largeur = QApplication::desktop()->width();
    int hauteur = QApplication::desktop()->height();
    this->resize(largeur,hauteur);*/

    //Chrono

    chrono = new QTime ( 0, 0, 0 ) ;
    chronoTimer = new QTimer () ;

    connect(ui->start, SIGNAL(clicked(bool)), this, SLOT(lancerChronometre())); // quand on appuie sur commencer le chrono demarre
    connect(chronoTimer, SIGNAL (timeout()), this, SLOT (refreshChronometre())) ; // mise à jour de la valeur du chrono
    connect(ui->start, SIGNAL(clicked(bool)), this, SLOT (disabledWidgetsCommencer())) ;
    connect(ui->start, SIGNAL(clicked(bool)), this, SLOT(enablePauseReprendre()));
    connect(ui->start, SIGNAL(clicked(bool)), this, SLOT(sauvegarderValeurs()));


    connect(ui->stop, SIGNAL(clicked(bool)), this, SLOT (stopChronometre())) ; // quand on appuie sur stop, le chrono s'arrete
    connect(ui->stop, SIGNAL(clicked(bool)), this, SLOT (disabledWidgetsArret())) ;

    connect(ui->pause, SIGNAL(clicked(bool)), this, SLOT (pauseChronometre())) ; // pause
    connect(ui->reprendre, SIGNAL(clicked(bool)), this, SLOT (restartChronometre())) ; //reprendre
    connect(ui->reset, SIGNAL(clicked(bool)), this, SLOT (resetChronometre())) ; //remise à zéro

    connect(ui->suivantPatient, SIGNAL(clicked(bool)), this, SLOT(suivantFenetrePatient()));
    connect(ui->suivantReglages1, SIGNAL(clicked(bool)), this, SLOT(suivantFenetreReglages1()));
    connect(ui->precedentReglages1, SIGNAL(clicked(bool)), this, SLOT(precedentFenetreReglages1()));
    connect(ui->suivantReglages2, SIGNAL(clicked(bool)), this, SLOT(suivantFenetreReglages2()));
    connect(ui->precedentReglages2, SIGNAL(clicked(bool)), this, SLOT(precedentFenetreReglages2()));
    connect(ui->precedentResume, SIGNAL(clicked(bool)), this, SLOT(precedentFenetreResume()));


    // Courbe

   /* QwtPlot *myPlot = new QwtPlot(ui->simulation);


    QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1");
    curve1->setPen(* new QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    QwtPlotGrid *grid = new QwtPlotGrid;
    //grid->enableXMin(true);
    //grid->enableYMin(true);
    grid->setPen(* new QPen(Qt::gray));
    grid->attach(myPlot);

    QwtPointSeriesData* myData = new QwtPointSeriesData;


    QVector<QPointF>* samples = new QVector<QPointF>;

    samples->push_back(QPointF(0.0,0.0));
    samples->push_back(QPointF(0.3,0.0));
    samples->push_back(QPointF(0.3,600.0));
    samples->push_back(QPointF(0.5,600.0));
    samples->push_back(QPointF(0.5,-600.0));
    samples->push_back(QPointF(0.7,-600.0));
    samples->push_back(QPointF(0.7,0.0));
    samples->push_back(QPointF(0.9,0.0));
    samples->push_back(QPointF(0.9,600.0));
    samples->push_back(QPointF(1.1,600.0));
    samples->push_back(QPointF(1.1,-600.0));
    samples->push_back(QPointF(1.3,-600.0));
    samples->push_back(QPointF(1.3,0.0));
    samples->push_back(QPointF(1.5,0.0));
    samples->push_back(QPointF(1.5,600.0));
    samples->push_back(QPointF(1.7,600.0));
    samples->push_back(QPointF(1.7,-600.0));
    samples->push_back(QPointF(1.9,-600.0));
    samples->push_back(QPointF(1.9,0.0));
    samples->push_back(QPointF(2.1,0.0));
    samples->push_back(QPointF(2.1,600.0));
    //samples->push_back(QPointF(-4.0,-4.0));

    myData->setSamples(*samples);

    curve1->setData(myData);

    curve1->attach(myPlot);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(myPlot, 0, 1);
    ui->simulation->setLayout(layout);

    myPlot->replot();*/

}


IHMdeportee::~IHMdeportee()
{
    delete ui;
}


//Démarrer le chrono

void IHMdeportee::lancerChronometre()
{
   chronoTimer -> start ( 1000 ) ;    // On lance un affichage toutes les 1000 milisecondes
   displayChronometre();
}

void IHMdeportee::enablePauseReprendre()
{
        QPushButton *bouton1 = new QPushButton;
        bouton1 = ui->pause;
        bouton1->setEnabled(true);

        QPushButton *bouton2 = new QPushButton;
        bouton2 = ui->reprendre;
        bouton2->setEnabled(true);

}


//Pause

void IHMdeportee::pauseChronometre()
{
        chronoTimer->stop();

}

//Reset

void IHMdeportee::resetChronometre()
{
        chronoTimer->stop();
        chrono->setHMS(0,0,0,0);
        ui->chronometre->display(chrono->toString("h:mm:ss"));

        QPushButton *bouton1 = new QPushButton;
        bouton1 = ui->reprendre;
        bouton1->setEnabled(true);

        QPushButton *bouton2 = new QPushButton;
        bouton2 = ui->pause;
        bouton2->setEnabled(true);

        QPushButton *bouton3 = new QPushButton;
        bouton3 = ui->start;
        bouton3->setEnabled(true);

        QPushButton *bouton4 = new QPushButton;
        bouton4 = ui->precedentResume;
        bouton4->setEnabled(true);

        ui->tabWidget->setTabEnabled(0,true);
        ui->tabWidget->setTabEnabled(1,true);
        ui->tabWidget->setTabEnabled(2,true);

}


// arrêt d'urgence et pause

void IHMdeportee::stopChronometre()
{
        chronoTimer->stop();

}

//Relancer le chrono après la pause

void IHMdeportee::restartChronometre()
{
    chronoTimer->start(1000);

}

//Mise à jour du chrono

void IHMdeportee::refreshChronometre()
{
    *chrono = chrono->addSecs(1);
    displayChronometre();
}

//Afficher chrono

void IHMdeportee::displayChronometre()
{
    ui->chronometre -> display(chrono->toString("h:mm:ss")) ;
}


//Heure

void IHMdeportee::updateLabel()
{
    QTime time = QTime::currentTime();
    QString timeString = time.toString("hh:mm");
    ui->heure->setText(timeString);
}


//Timer pour l'heure

void IHMdeportee::lancerTimer()
{
    QTimer *updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateLabel()));
    updateTimer->start(1000);
}


//Date

void IHMdeportee::calendrier()
{
    QDateTime date = QDateTime::currentDateTime();


    QDate dateOfDay = QDate::currentDate();
    ui->dateManip->setDate(dateOfDay);


    QString dateString = date.toString("d/MM/yyyy");
    ui->date->setText(dateString);
}


//disable les bouton pause, reprendre et commencer quand on appuie sur arret d'urgence

void IHMdeportee::disabledWidgetsArret()
{
    QPushButton *bouton1 = new QPushButton;
    bouton1 = ui->reprendre;
    bouton1->setEnabled(false);

    QPushButton *bouton2 = new QPushButton;
    bouton2 = ui->pause;
    bouton2->setEnabled(false);

    QPushButton *bouton3 = new QPushButton;
    bouton3 = ui->start;
    bouton3->setEnabled(false);
}


//Rend inaccessible les onglets précédents après avoir appuyé sur Commencer

void IHMdeportee::disabledWidgetsCommencer()
{
    QPushButton *bouton1 = new QPushButton;
    bouton1 = ui->precedentResume;
    bouton1->setEnabled(false);


    //ui->patient->setEnabled(false);
    //ui->reglages1->setEnabled(false);
    //ui->reglages2->setEnabled(false);

    ui->tabWidget->setTabEnabled(0,false);
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);

    /*QPushButton *bouton2 = new QPushButton;
    bouton2 = ui->pause;
    bouton2->setEnabled(false);

    QPushButton *bouton3 = new QPushButton;
    bouton3 = ui->start;
    bouton3->setEnabled(false);*/
}


//Layouts

void IHMdeportee::layout()
{

    //Layout GroupBoxPatient


    QGridLayout *layoutPatient = new QGridLayout;
    layoutPatient->addWidget(ui->labelNom,0,0);
    layoutPatient->addWidget(ui->labelPrenom,1,0);
    layoutPatient->addWidget(ui->labelDate,2,0);
    layoutPatient->addWidget(ui->labelNum,3,0);

    layoutPatient->addWidget(ui->nom,0,1);
    layoutPatient->addWidget(ui->prenom,1,1);
    layoutPatient->addWidget(ui->dateManip,2,1);
    layoutPatient->addWidget(ui->numManip,3,1);

    layoutPatient->addWidget(ui->suivantPatient,5,2);

    ui->groupBoxPatient->setLayout(layoutPatient);


    //Layout GroupBoxReglages1

      // ** Paramètres

    QGridLayout *layoutReglages1 = new QGridLayout;
    layoutReglages1->addWidget(ui->labelLargeurImpulsion,0,0);
    layoutReglages1->addWidget(ui->labelAmplitudeMax,1,0);

    layoutReglages1->addWidget(ui->largeurImpulsion,0,1);
    layoutReglages1->addWidget(ui->amplitudeMax,1,1);

    layoutReglages1->addWidget(ui->valeurLargeurImpulsion,0,2);
    layoutReglages1->addWidget(ui->valeurAmplitude,1,2);

    layoutReglages1->addWidget(ui->imageReglage1,0,3,2,1);


      // ** Boutons suivant et précédent

    QHBoxLayout *layoutBoutonsReglages1 = new QHBoxLayout;

    layoutBoutonsReglages1->addWidget(ui->precedentReglages1,0);
    layoutBoutonsReglages1->addWidget(ui->suivantReglages1,1);

    layoutReglages1->addLayout(layoutBoutonsReglages1,3,3);


    ui->groupBoxReglages1->setLayout(layoutReglages1);


    //Layout GroupBox Reglages2

      // ** Réglage nombre impulsions

    QHBoxLayout *layoutNombreImpulsions = new QHBoxLayout;
    layoutNombreImpulsions->addWidget(ui->nombreImpulsions,0);
    layoutNombreImpulsions->addWidget(ui->moinsReglage2,1);
    layoutNombreImpulsions->addWidget(ui->plusReglage2,2);

    layoutNombreImpulsions->setSpacing(10);
    layoutNombreImpulsions->setAlignment(Qt::AlignCenter);

      // ** Paramètres

    QGridLayout *layoutReglages2 = new QGridLayout;
    layoutReglages2->addWidget(ui->labelNombreImpulsion,0,0);
    layoutReglages2->addWidget(ui->labelPeriode,1,0);

    layoutReglages2->addLayout(layoutNombreImpulsions,0,1);
    layoutReglages2->addWidget(ui->periodicite,1,1);

    layoutReglages2->addWidget(ui->valeurPeriode,1,2);

      // ** Image

    layoutReglages2->addWidget(ui->imageReglage2,0,3,2,2);

      // ** Boutons précédent et suivant

    QHBoxLayout *layoutBoutonsReglages2 = new QHBoxLayout;

    layoutBoutonsReglages2->addWidget(ui->precedentReglages2,0);
    layoutBoutonsReglages2->addWidget(ui->suivantReglages2,1);

    layoutBoutonsReglages2->setSpacing(10);
    layoutBoutonsReglages2->setAlignment(Qt::AlignRight);



      // ** Layout général

    layoutReglages2->addLayout(layoutBoutonsReglages2,3,4);

    ui->groupBoxReglages2->setLayout(layoutReglages2);

    layoutReglages2->setSpacing(20);
    //layoutReglages2->setAlignment(Qt::AlignLeft);



    //Layout de groupBox Resume

      // ** Paramètres

    QGridLayout *layoutgroupBoxResume = new QGridLayout;

    layoutgroupBoxResume->addWidget(ui->imageColonne,0,0,5,1);

    layoutgroupBoxResume->addWidget(ui->resumeLargeurImpulsion, 0,1);
    layoutgroupBoxResume->addWidget(ui->resumeAmplitude,1,1);
    layoutgroupBoxResume->addWidget(ui->resumeNombreImpulsion,2,1);
    layoutgroupBoxResume->addWidget(ui->resumePeriode,3,1);

    layoutgroupBoxResume->addWidget(ui->deuxPoints1,0,2);
    layoutgroupBoxResume->addWidget(ui->deuxPoints2,1,2);
    layoutgroupBoxResume->addWidget(ui->deuxPoints3,2,2);
    layoutgroupBoxResume->addWidget(ui->deuxPoints4,3,2);

    layoutgroupBoxResume->addWidget(ui->resumeValeurLargeurImpulsion,0,3);
    layoutgroupBoxResume->addWidget(ui->resumeValeurAmplitude,1,3);
    layoutgroupBoxResume->addWidget(ui->resumeValeurNombreImpulsion,2,3);
    layoutgroupBoxResume->addWidget(ui->resumeValeurPeriode,3,3);

      // ** Boutons précédent et commencer

    QHBoxLayout *layoutBoutonsResume = new QHBoxLayout;
    layoutBoutonsResume->addWidget(ui->precedentResume,0);
    layoutBoutonsResume->addWidget(ui->start,1);

    layoutBoutonsResume->setSpacing(10);
    layoutBoutonsResume->setAlignment(Qt::AlignRight);

    layoutgroupBoxResume->addLayout(layoutBoutonsResume,4,2,1,2);

    layoutgroupBoxResume->setAlignment(Qt::AlignRight);


    ui->groupBoxResume->setLayout(layoutgroupBoxResume);




    //Layout de l'onglet patient

    QGridLayout *layoutGroupBoxPatient = new QGridLayout;
    layoutGroupBoxPatient->addWidget(ui->groupBoxPatient,0,0);

    ui->patient->setLayout(layoutGroupBoxPatient);


    //Layout de l'onglet reglages1

    QGridLayout *layoutGroupBoxReglages1 = new QGridLayout;
    layoutGroupBoxReglages1->addWidget(ui->groupBoxReglages1,0,0);

    ui->reglages1->setLayout(layoutGroupBoxReglages1);


    //Layout de l'onglet reglages2

    QGridLayout *layoutGroupBoxReglages2 = new QGridLayout;
    layoutGroupBoxReglages2->addWidget(ui->groupBoxReglages2,0,0);

    ui->reglages2->setLayout(layoutGroupBoxReglages2);


    //Layout de l'onglet resume

    QGridLayout *layoutResume = new QGridLayout;
    layoutResume->addWidget(ui->groupBoxResume,0,0);

    ui->resume->setLayout(layoutResume);

    layoutgroupBoxResume->setSpacing(50);
    layoutgroupBoxResume->setAlignment(Qt::AlignRight);



    // Layout de l'onglet commentaires

      // ** editCommentaire dans groupBox

    QGridLayout *layoutGroupBoxCommentaires = new QGridLayout;
    layoutGroupBoxCommentaires->addWidget(ui->editCommentaires,0,0);

    ui->groupBoxCommentaires->setLayout(layoutGroupBoxCommentaires);

      // ** groupBox dans onglet commentaires

    QGridLayout *layoutCommentaires = new QGridLayout;
    layoutCommentaires->addWidget(ui->groupBoxCommentaires,0,0);

    ui->commentaires->setLayout(layoutCommentaires);


    //Layout fenetre principale

      // ** Layout date et heure

    QVBoxLayout *layoutBoutonTemps = new QVBoxLayout;
    layoutBoutonTemps->addWidget(ui->date, 0);
    layoutBoutonTemps->addWidget(ui->heure, 1);

      // ** Layout boutons pause et reprendre

    QHBoxLayout *layoutPauseReprendre = new QHBoxLayout;
    layoutPauseReprendre->addWidget(ui->pause, 0);
    layoutPauseReprendre->addWidget(ui->reprendre, 1);

      // ** Layout Pause/Reprendre + Reset

    QGridLayout *layoutBoutonChrono = new QGridLayout;;
    layoutBoutonChrono->addLayout(layoutPauseReprendre, 0, 0);
    layoutBoutonChrono->addWidget(ui->reset, 1, 0);

      // ** Layout Pause/Reprendre/Reset + Chronomètre

    QGridLayout *layoutBoutonsBas = new QGridLayout;
    layoutBoutonsBas->addLayout(layoutBoutonChrono,0,0,1,1);
    layoutBoutonsBas->addWidget(ui->chronometre,0,1,1,1);

      // ** Layout Pause/Reprendre/Reset/Chronomètre/heure/date/stop/batterie

    QGridLayout *layoutSousPrincipal = new QGridLayout;
    layoutSousPrincipal->addLayout(layoutBoutonTemps,0,0,1,1);
    layoutSousPrincipal->addLayout(layoutBoutonsBas,0,1,1,1);
    layoutSousPrincipal->addWidget(ui->stop,0,2,1,1);
    layoutSousPrincipal->addWidget(ui->batterie,0,3,1,1);

      // ** Ajout de la tabWidget à la fenêtre principale

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(ui->tabWidget);
    layoutPrincipal->addLayout(layoutSousPrincipal);

    QWidget *window = new QWidget();
    window->setLayout(layoutPrincipal);
    setCentralWidget(window);
}



//Taille des widgets

void IHMdeportee::sizeWidget()
{
    //Onglet patient

    ui->labelNom->setFixedSize(600,40);
    ui->labelPrenom->setFixedSize(600,40);
    ui->labelDate->setFixedSize(600,40);
    ui->labelNum->setFixedSize(600,40);

    ui->nom->setFixedSize(700,80);
    ui->prenom->setFixedSize(700,80);
    ui->dateManip->setFixedSize(700,100);
    ui->numManip->setFixedSize(700,80);

    ui->suivantPatient->setFixedSize(250,130);


    //Onglet reglages 1


    ui->labelLargeurImpulsion->setFixedSize(600,100);
    ui->labelAmplitudeMax->setFixedSize(600,100);

    ui->largeurImpulsion->setFixedSize(600,80);
    ui->amplitudeMax->setFixedSize(600,80);

    ui->imageReglage1->setFixedSize(500,700);

    ui->suivantReglages1->setFixedSize(250,130);
    ui->precedentReglages1->setFixedSize(250,130);


   //Onglet reglages 2

    ui->labelNombreImpulsion->setFixedSize(400,100);
    ui->labelPeriode->setFixedSize(400,100);

    ui->nombreImpulsions->setFixedSize(300,100);
    ui->periodicite->setFixedSize(600,80);

    ui->moinsReglage2->setFixedSize(100,100);
    ui->plusReglage2->setFixedSize(100,100);

    ui->suivantReglages2->setFixedSize(250,130);
    ui->precedentReglages2->setFixedSize(250,130);

    //Onglet resume

    ui->precedentResume->setFixedSize(250,130);
    ui->start->setFixedSize(300,130);

    ui->resumeNombreImpulsion->setFixedSize(600,110);
    ui->resumeLargeurImpulsion->setFixedSize(600,110);
    ui->resumePeriode->setFixedSize(600,110);
    ui->resumeAmplitude->setFixedSize(600,110);

    ui->resumeValeurNombreImpulsion->setFixedSize(300,110);
    ui->resumeValeurLargeurImpulsion->setFixedSize(300,110);
    ui->resumeValeurPeriode->setFixedSize(300,110);
    ui->resumeValeurAmplitude->setFixedSize(300,110);

    ui->deuxPoints1->setFixedSize(300,110);
    ui->deuxPoints2->setFixedSize(300,110);
    ui->deuxPoints3->setFixedSize(300,110);
    ui->deuxPoints4->setFixedSize(300,110);

    // Onglet commentaires

    ui->editCommentaires->setFixedSize(1950,1000);

    //Fenetre principale


    ui->batterie->setFixedSize(400,200);

    ui->pause->setFixedSize(150,100);
    ui->reprendre->setFixedSize(150,100);
    ui->reset->setFixedSize(310,100);

    ui->stop->setFixedSize(450,200);

    ui->chronometre->setFixedSize(500,210);

    ui->date->setFixedSize(240,50);
    ui->heure->setFixedSize(220,50);
}



/*********************/
/* Style des widgets */
/*********************/


void IHMdeportee::styleWidget()
{


    ui->tabWidget->setStyleSheet("QTabBar::tab { width: 400 px; }");

    /*int valeurBatterie = ui->batterie->value();

    if (valeurBatterie >= 50)
    {
        ui->batterie->setStyleSheet("QProgressBar::chunk{background-color : rgb(15,211,15);}");
    }
    else if (valeurBatterie >= 20)
    {
        ui->batterie->setStyleSheet("QProgressBar::chunk{background-color : rgb(227,222,20);}");
    }
    else if (valeurBatterie >= 10)
    {
        ui->batterie->setStyleSheet("QProgressBar::chunk{background-color : rgb(255,102,0);}");
    }
    else
    {
        ui->batterie->setStyleSheet("QProgressBar::chunk{background-color : rgb(243,35,13);}");
    }*/



    /*this->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                "stop: 0 #a5c7cc, stop: 1 #a5c7cc);"
    "min-width: 80px");*/


    // Style de la batterie

    ui->batterie->setStyleSheet("QProgressBar::chunk {"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                "stop: 0 #5eaf3b, stop: 1 #539935);"
    "min-width: 80px}");


    ui->patient->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                "stop: 0 #ffffff, stop: 1 #ffffff);"
    "min-width: 80px");


    ui->groupBoxPatient->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                "stop: 0 #ffffff, stop: 1 #ffffff);"
    "min-width: 80px");



    ui->moinsReglage2->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");

    ui->plusReglage2->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");


    // A REVOIR


    ui->largeurImpulsion->setStyleSheet("QSlider::handle:horizontal {"
        "color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");


   //






    /*ui->stop->setStyleSheet("QPushButton {"
        "border: 2px solid #544f4f;"
        "border-radius: 10px;"
        "text-align: left;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #e21f1f, stop: 1 #ff4747);"
        "min-width: 80px;}");*/

    ui->stop->setStyleSheet("QPushButton {"
        "border: 2px solid #544f4f;"
        "border-radius: 10px;"
        "text-align: left;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #e21f1f, stop: 1 #ff4747);"
        "min-width: 80px;}");




    ui->pause->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");

    /*ui->pause->setStyleSheet("QPushButton {"
        "border: 2px solid #544f4f;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #e21f1f, stop: 1 #ff4747);"
        "min-width: 80px;}");*/

    /*ui->pause->setStyleSheet("QPushButton {"
        "border: 2px solid #999289;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #ed9a2f, stop: 1 #ffcd8e);"
        "min-width: 80px;}");*/



    ui->reprendre->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");

    /*ui->reprendre->setStyleSheet("QPushButton {"
        "border: 2px solid #6d726b;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #45a51d, stop: 1 #9cf279);"
        "min-width: 80px;}");*/

    /*ui->reprendre->setStyleSheet("QPushButton {"
        "border: 2px solid #565e60;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #5bb7d8, stop: 1 #509cb7);"
        "min-width: 80px;}");*/





    /*ui->reset->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #ada9a6, stop: 1 #fff8f4);"
        "min-width: 80px;}");*/

    ui->reset->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");





    ui->suivantPatient->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");


    ui->suivantReglages1->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");

    ui->suivantReglages2->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");


    ui->precedentReglages1->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");


    ui->precedentReglages2->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");


    ui->precedentResume->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");

    ui->start->setStyleSheet("QPushButton {"
        "border: 2px solid #898481;"
        "border-radius: 10px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                          "stop: 0 #cccccc, stop: 1 #e0dede);"
        "min-width: 80px;}");



    //"color : rgb(255,255,255);"

    //"background-color : rgb(255,0,0);}");
    //ui->labelResume->setStyleSheet("QLabel{background-color : green}");
    //ui->stop->setText("");

    ui->stop->setText(" Arrêt");

    ui->stop->setIcon(QIcon(":/icones/danger.png"));
    //ui->stop->setStyleSheet("text-align: left");
    ui->stop->setIconSize(QSize(150,150));


    QPixmap monImage(":/image/SignauxIHMImp.jpg");
    ui->imageReglage1->setPixmap(monImage);
    ui->imageReglage1->setScaledContents(true);
    ui->imageReglage1->adjustSize();

    ui->pause->setIcon(QIcon(":/image/pause.ico"));
    ui->pause->setIconSize(QSize(60,60));

    ui->reprendre->setIcon(QIcon(":/image/reprendre.png"));
    ui->reprendre->setIconSize(QSize(60,60));


    QPixmap monImage2(":/image/IHMReglage2.jpg");
    ui->imageReglage2->setPixmap(monImage2);
    ui->imageReglage2->setScaledContents(true);
    ui->imageReglage2->adjustSize();

    QPixmap colonneVertebrale(":/image/Colonne-vertébrale.jpg");
    ui->imageColonne->setPixmap(colonneVertebrale);
    ui->imageReglage2->setScaledContents(true);
    ui->imageReglage2->adjustSize();


}


void IHMdeportee::suivantFenetrePatient()
{

    ui->tabWidget->setCurrentWidget(ui->reglages1);

}


void IHMdeportee::suivantFenetreReglages1()
{

    ui->tabWidget->setCurrentWidget(ui->reglages2);

}

void IHMdeportee::precedentFenetreReglages1()
{

    ui->tabWidget->setCurrentWidget(ui->patient);

}

void IHMdeportee::suivantFenetreReglages2()
{

    ui->tabWidget->setCurrentWidget(ui->resume);

}

void IHMdeportee::precedentFenetreReglages2()
{

    ui->tabWidget->setCurrentWidget(ui->reglages1);

}

void IHMdeportee::precedentFenetreResume()
{

    ui->tabWidget->setCurrentWidget(ui->reglages2);

}

void IHMdeportee::updateValeurs()
{

    QTimer *timer = new QTimer;
    connect(timer, SIGNAL(timeout()),this, SLOT(writeResume()));
    timer->start(100);


}


void IHMdeportee::writeResume()
{
    //QString nom = ui->nom->text();

    //ui->labelResume->setText("Nombre d'impulsions : \n\n\nLargeur des impulsions : \n\n\nLargeur de la fenêtre : \n\n\nPériode : \n\n\nAmplitude maximale : ");
    ui->resumeNombreImpulsion->setText("Nombre d'impulsions  ");
    ui->resumeLargeurImpulsion->setText("Largeur des impulsions  ");
    ui->resumePeriode->setText("Période  ");
    ui->resumeAmplitude->setText("Amplitude maximale  ");

    int valeurNombreImpulsions = ui->nombreImpulsions->value();
    //QString nombreImpulsions = valeurNombreImpulsions.toString;
    QString nombreImpulsions = QString::number(valeurNombreImpulsions);

    QString largeurImpulsions = ui->valeurLargeurImpulsion->text();
    //QString largeurFenetre = ui->valeurLargeurFenetre->text();
    QString periodicite = ui->valeurPeriode->text();
    QString amplitudeMax = ui->valeurAmplitude->text();

    ui->resumeValeurNombreImpulsion->setText(nombreImpulsions);
    ui->resumeValeurLargeurImpulsion->setText(largeurImpulsions);
    //ui->resumeValeurLargeurFenetre->setText(largeurFenetre);
    ui->resumeValeurPeriode->setText(periodicite);
    ui->resumeValeurAmplitude->setText(amplitudeMax);

}

void IHMdeportee::sauvegarderValeurs()
{

        //ui->editCommentaires->setReadOnly(true);

        QString texte;
        texte = ui->nom->text();
        QFile fichierDonnees("donnees.txt");

        //fichierDonnees.open(QIODevice::ReadWrite);

        QTextStream flux(&fichierDonnees);
        flux << texte;

        if(fichierDonnees.open(QIODevice::ReadWrite))
            {
                QTextStream flux(&fichierDonnees);
                while(!flux.atEnd())
                    texte += flux.readLine();
                fichierDonnees.close();
            }
        else texte = "Impossible d'ouvrir le fichier !";

        ui->test->setText(texte);
        ui->test->setFixedSize(1000,200);


    //QFile fichierDonnees("donnees.txt");
    //fichierDonnees.open(QIODevice::ReadOnly | QIODevice::Text);

    //QTextStream flux(&fichierDonnees);

    //flux << texte;
    //fichierDonnees.close();

    /*if(fichierDonnees.open(QIODevice::ReadOnly | QIODevice::Text))
       {
            texte = fichierDonnees.readAll();
            fichierDonnees.close();
       }
       else texte = "Impossible d'ouvrir le fichier !";

    ui->test->setFixedSize(200,200);
    ui->test->setText(texte);*/

    /*QString texte;


    if(fichierDonnees.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichierDonnees);
        while(!flux.atEnd())
            texte += flux.readLine();
        fichierDonnees.close();
    }
    else texte = "Impossible d'ouvrir le fichier !";

    ui->test->setFixedSize(200,1000);
    ui->test->setText(texte);*/




    /*if(fichierDonnees.open(QIODevice::ReadOnly | QIODevice::Text))
        {
             texte = fichierDonnees.readAll();
             fichierDonnees.close();
        }
    else texte = "Impossible d'ouvrir le fichier !";

        ui->test->setText(texte);
        ui->test->setFixedSize(1000,200);*/



}




