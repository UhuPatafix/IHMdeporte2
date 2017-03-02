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

    connect(ui->stop, SIGNAL(clicked(bool)), this, SLOT (stopChronometre())) ; // quand on appuie sur stop, le chrono s'arrete
    connect(ui->stop, SIGNAL(clicked(bool)), this, SLOT (disabledWidgetsArret())) ;

    connect(ui->pause, SIGNAL(clicked(bool)), this, SLOT (pauseChronometre())) ; // pause
    connect(ui->reprendre, SIGNAL(clicked(bool)), this, SLOT (restartChronometre())) ; //reprendre

    connect(ui->suivantPatient, SIGNAL(clicked(bool)), this, SLOT(suivantFenetrePatient()));
    connect(ui->suivantReglages1, SIGNAL(clicked(bool)), this, SLOT(suivantFenetreReglages1()));
    connect(ui->precedentReglages1, SIGNAL(clicked(bool)), this, SLOT(precedentFenetreReglages1()));
    connect(ui->suivantReglages2, SIGNAL(clicked(bool)), this, SLOT(suivantFenetreReglages2()));
    connect(ui->precedentReglages2, SIGNAL(clicked(bool)), this, SLOT(precedentFenetreReglages2()));
    connect(ui->precedentResume, SIGNAL(clicked(bool)), this, SLOT(precedentFenetreResume()));


    // Courbe

    /*QwtPlot *myPlot = new QwtPlot(ui->simulation);


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

//Pause

void IHMdeportee::pauseChronometre()
{
        chronoTimer->stop();

}


// arrêt d'urgence et pause

void IHMdeportee::stopChronometre()
{
        chronoTimer->stop();

}

//Relancer le chrono après la pause

void IHMdeportee::restartChronometre()
{
    chronoTimer->start();

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
    ui->chronometre -> display( chrono->toString("h:mm:ss")) ;
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

    QGridLayout *layoutReglages1 = new QGridLayout;
    layoutReglages1->addWidget(ui->labelNombreImpulsion,0,0);    
    layoutReglages1->addWidget(ui->labelAmplitudeMax,1,0);

    layoutReglages1->addWidget(ui->nombreImpulsions,0,1);
    layoutReglages1->addWidget(ui->amplitudeMax,1,1);

    layoutReglages1->addWidget(ui->valeurAmplitude,1,2);

    layoutReglages1->addWidget(ui->precedentReglages1,6,3);
    layoutReglages1->addWidget(ui->suivantReglages1,6,4);

    ui->groupBoxReglages1->setLayout(layoutReglages1);


    //Layout GroupBox Reglages2

    QGridLayout *layoutReglages2 = new QGridLayout;
    layoutReglages2->addWidget(ui->labelLargeurImpulsion,0,0);
    layoutReglages2->addWidget(ui->labelLargeurFenetre,1,0);
    layoutReglages2->addWidget(ui->labelPeriode,2,0);

    layoutReglages2->addWidget(ui->largeurImpulsion,0,1);
    layoutReglages2->addWidget(ui->largeurFenetre,1,1);
    layoutReglages2->addWidget(ui->periodicite,2,1);

    layoutReglages2->addWidget(ui->valeurLargeurImpulsion,0,2);
    layoutReglages2->addWidget(ui->valeurLargeurFenetre,1,2);
    layoutReglages2->addWidget(ui->valeurPeriode,2,2);

    layoutReglages2->addWidget(ui->precedentReglages2,3,3);
    layoutReglages2->addWidget(ui->suivantReglages2,3,4);

    ui->groupBoxReglages2->setLayout(layoutReglages2);


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

    QGridLayout *layoutLabels = new QGridLayout;
    layoutLabels->addWidget(ui->resumeNombreImpulsion,0,0);
    layoutLabels->addWidget(ui->resumeLargeurImpulsion,1,0);
    layoutLabels->addWidget(ui->resumeLargeurFenetre,2,0);
    layoutLabels->addWidget(ui->resumePeriode,3,0);
    layoutLabels->addWidget(ui->resumeAmplitude,4,0);

    layoutLabels->addWidget(ui->deuxPoints1,0,1);
    layoutLabels->addWidget(ui->deuxPoints2,1,1);
    layoutLabels->addWidget(ui->deuxPoints3,2,1);
    layoutLabels->addWidget(ui->deuxPoints4,3,1);
    layoutLabels->addWidget(ui->deuxPoints5,4,1);

    layoutLabels->addWidget(ui->resumeValeurNombreImpulsion,0,2);
    layoutLabels->addWidget(ui->resumeValeurLargeurImpulsion,1,2);
    layoutLabels->addWidget(ui->resumeValeurLargeurFenetre,2,2);
    layoutLabels->addWidget(ui->resumeValeurPeriode,3,2);
    layoutLabels->addWidget(ui->resumeValeurAmplitude,4,2);

    QGridLayout *layoutResume = new QGridLayout;
    layoutResume->addLayout(layoutLabels,0,0);
    layoutResume->addWidget(ui->precedentResume,1,1);
    layoutResume->addWidget(ui->start,1,2);

    ui->resume->setLayout(layoutResume);


    //Layout fenetre principale

    QVBoxLayout *layoutBoutonTemps = new QVBoxLayout;
    layoutBoutonTemps->addWidget(ui->date, 0);
    layoutBoutonTemps->addWidget(ui->heure, 1);

    QGridLayout *layoutBoutonChrono = new QGridLayout;
    layoutBoutonChrono->addWidget(ui->pause, 0, 0);
    layoutBoutonChrono->addWidget(ui->reprendre, 1, 0);

    QGridLayout *layoutBoutonsBas = new QGridLayout;
    layoutBoutonsBas->addLayout(layoutBoutonChrono,0,0,1,1);
    layoutBoutonsBas->addWidget(ui->chronometre,0,1,1,1);

    QGridLayout *layoutSousPrincipal = new QGridLayout;
    layoutSousPrincipal->addLayout(layoutBoutonTemps,0,0,1,1);
    layoutSousPrincipal->addLayout(layoutBoutonsBas,0,1,1,1);
    layoutSousPrincipal->addWidget(ui->stop,0,2,1,1);
    layoutSousPrincipal->addWidget(ui->batterie,0,3,1,1);

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

    ui->labelNombreImpulsion->setFixedSize(600,100);
    ui->labelLargeurImpulsion->setFixedSize(600,50);
    ui->labelLargeurFenetre->setFixedSize(600,50);
    ui->labelPeriode->setFixedSize(600,50);
    ui->labelAmplitudeMax->setFixedSize(600,50);

    ui->nombreImpulsions->setFixedSize(700,100);
    ui->largeurImpulsion->setFixedSize(700,80);
    ui->largeurFenetre->setFixedSize(700,80);
    ui->periodicite->setFixedSize(700,80);
    ui->amplitudeMax->setFixedSize(700,80);

    ui->suivantReglages1->setFixedSize(250,130);
    ui->precedentReglages1->setFixedSize(250,130);


   //Onglet reglages 2

    ui->suivantReglages2->setFixedSize(250,130);
    ui->precedentReglages2->setFixedSize(250,130);

    //Onglet resume

    ui->precedentResume->setFixedSize(300,130);
    ui->start->setFixedSize(350,130);

    ui->resumeNombreImpulsion->setFixedSize(600,110);
    ui->resumeLargeurImpulsion->setFixedSize(600,110);
    ui->resumeLargeurFenetre->setFixedSize(600,110);
    ui->resumePeriode->setFixedSize(600,110);
    ui->resumeAmplitude->setFixedSize(600,110);

    ui->resumeValeurNombreImpulsion->setFixedSize(300,110);
    ui->resumeValeurLargeurImpulsion->setFixedSize(300,110);
    ui->resumeValeurLargeurFenetre->setFixedSize(300,110);
    ui->resumeValeurPeriode->setFixedSize(300,110);
    ui->resumeValeurAmplitude->setFixedSize(300,110);

    ui->deuxPoints1->setFixedSize(300,110);
    ui->deuxPoints2->setFixedSize(300,110);
    ui->deuxPoints3->setFixedSize(300,110);
    ui->deuxPoints4->setFixedSize(300,110);
    ui->deuxPoints5->setFixedSize(300,110);

    //Fenetre principale

    ui->batterie->setFixedSize(400,200);

    ui->pause->setFixedSize(300,90);
    ui->reprendre->setFixedSize(300,90);
    ui->stop->setFixedSize(400,200);

    ui->chronometre->setFixedSize(500,180);

    ui->date->setFixedSize(240,50);
    ui->heure->setFixedSize(220,50);
}



//Style des widgets

void IHMdeportee::styleWidget()
{
    ui->tabWidget->setStyleSheet("QTabBar::tab { width: 400 px; }");

    int valeurBatterie = ui->batterie->value();

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
    }



    ui->stop->setStyleSheet("QPushButton{"
                            "color : rgb(255,255,255);"
                            "background-color : rgb(255,0,0);}");

    //ui->labelResume->setStyleSheet("QLabel{background-color : green}");
    //ui->stop->setText("");
    //ui->stop->setIcon(QIcon("dangerj.jpg"));
    //ui->stop->setIconSize(QSize(20,20));
    ui->stop->setText("Arrêt \nd'urgence");



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
    ui->resumeLargeurFenetre->setText("Largeur de la fenêtre  ");
    ui->resumePeriode->setText("Période  ");
    ui->resumeAmplitude->setText("Amplitude maximale  ");

    int valeurNombreImpulsions = ui->nombreImpulsions->value();
    //QString nombreImpulsions = valeurNombreImpulsions.toString;
    QString nombreImpulsions = QString::number(valeurNombreImpulsions);

    QString largeurImpulsions = ui->valeurLargeurImpulsion->text();
    QString largeurFenetre = ui->valeurLargeurFenetre->text();
    QString periodicite = ui->valeurPeriode->text();
    QString amplitudeMax = ui->valeurAmplitude->text();

    ui->resumeValeurNombreImpulsion->setText(nombreImpulsions);
    ui->resumeValeurLargeurImpulsion->setText(largeurImpulsions);
    ui->resumeValeurLargeurFenetre->setText(largeurFenetre);
    ui->resumeValeurPeriode->setText(periodicite);
    ui->resumeValeurAmplitude->setText(amplitudeMax);

}




