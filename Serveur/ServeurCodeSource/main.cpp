#include <QApplication>
#include "serveur.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Serveur fenetre;
    fenetre.show();

    return app.exec();
}
