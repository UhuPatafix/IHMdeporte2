#include <QApplication>
#include <QtWidgets>
#include "ihmdeportee.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    IHMdeportee fenetre;
    fenetre.resize(1000,800);

    fenetre.show();

    return app.exec();
}
