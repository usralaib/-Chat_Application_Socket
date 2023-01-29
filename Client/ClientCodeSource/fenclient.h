#ifndef FENCLIENT_H
#define FENCLIENT_H

#include <QtWidgets>
#include <QtNetwork>
#include "ui_FenClient.h"


class FenClient : public QWidget, private Ui::FenClient
{
    Q_OBJECT

    public:
        FenClient();

    private slots:
        void on_boutonConnexion_clicked();
        void on_boutonEnvoyer_clicked();
        void on_message_returnPressed();
        void donneesRecues();
        void connecte();
        void deconnecte();
        void erreurSocket(QAbstractSocket::SocketError erreur);

    private:
        QTcpSocket *socket;
        quint16 tailleMessage;
};

#
#endif // FENCLIENT_H
