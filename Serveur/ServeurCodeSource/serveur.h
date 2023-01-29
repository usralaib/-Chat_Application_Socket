#ifndef SERVEUR_H
#define SERVEUR_H

#include <QtWidgets>
#include <QtNetwork>


class Serveur : public QWidget
{
    Q_OBJECT

    public:
        Serveur();
        void envoyerATous(const QString &message);

    private slots:
        void nouvelleConnexion();
        void donneesRecues();
        void deconnexionClient();

    private:
        QLabel *etatServeur;
        QPushButton *boutonQuitter;

        QTcpServer *serveur;
        QList<QTcpSocket *> clients;
        quint16 tailleMessage;
};

#endif // SERVEUR_H
