#ifndef IHMDEPORTEE_H
#define IHMDEPORTEE_H

#include <QApplication>
#include <QGraphicsView>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <QIcon>
#include <QDateTimeEdit>
#include <QGroupBox>
#include <QSpinBox>
#include <QSlider>
#include <QDialog>
#include <QString>
#include <QTimer>
#include <QTime>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QPixmap>
#include <QScreen>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

/*#include "D:/Qwt/qwt-6.1.3/qwt-6.1.3/src/qwt_plot.h"
#include "D:/Qwt/qwt-6.1.3/qwt-6.1.3/src/qwt_plot_curve.h"
#include "D:/Qwt/qwt-6.1.3/qwt-6.1.3/src/qwt_series_data.h"
#include <D:/Qwt/qwt-6.1.3/qwt-6.1.3/src/qwt_plot_grid.h>*/


namespace Ui {
class IHMdeportee;
}

class IHMdeportee : public QMainWindow
{
    Q_OBJECT

public:
    explicit IHMdeportee(QWidget *parent = 0);
    ~IHMdeportee();
    void lancerTimer();
    void calendrier();
    void layout();
    void sizeWidget();
    void styleWidget();
    void updateValeurs();
    void orientationScreen();

    //QwtCourbe(QWidget *parent = 0);


public slots:
void lancerChronometre();
void pauseChronometre();
void stopChronometre();
void restartChronometre();
void refreshChronometre();
void displayChronometre();
void disabledWidgetsArret();
void disabledWidgetsCommencer();
void enablePauseReprendre();
void updateLabel();
void suivantFenetrePatient();
void suivantFenetreReglages1();
void precedentFenetreReglages1();
void suivantFenetreReglages2();
void precedentFenetreReglages2();
void precedentFenetreResume();
void writeResume();
void resetChronometre();
void sauvegarderValeurs();

//void index();

//signals:

private:
    Ui::IHMdeportee *ui;
    QTime *chrono;
    QTimer *chronoTimer;
};

#endif // IHMDEPORTEE_H

