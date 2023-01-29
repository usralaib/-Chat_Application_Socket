#include "fenclient.h"

FenClient::FenClient()
{

        setupUi(this);

        socket = new QTcpSocket(this);
        connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
        connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

        tailleMessage = 0;

}
void FenClient::on_boutonConnexion_clicked()
{
    listeMessages->append(tr("<em>Tentative de connexion en cours...</em>"));
    boutonConnexion->setEnabled(false);

    socket->abort();
    socket->connectToHost(serveurIP->text(), serveurPort->value());
}

void FenClient::on_boutonEnvoyer_clicked()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    QString messageAEnvoyer =message->text();

    out << (quint16) 0;
    out << messageAEnvoyer;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet);

    message->clear();
    message->setFocus();
}

void FenClient::on_message_returnPressed()
{
    on_boutonEnvoyer_clicked();
}

void FenClient::donneesRecues()
{

    QDataStream in(socket);

    if (tailleMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> tailleMessage;
    }

    if (socket->bytesAvailable() < tailleMessage)
        return;


    QString messageRecu;
    in >> messageRecu;

    listeMessages->append(messageRecu);

    tailleMessage = 0;
}
void FenClient::connecte()
{
    listeMessages->append(tr("<em>Connexion réussie !</em>"));
    boutonConnexion->setEnabled(true);
}
void FenClient::deconnecte()
{
    listeMessages->append(tr("<em>Déconnecté du serveur</em>"));
}
void FenClient::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur)
    {
        case QAbstractSocket::HostNotFoundError:
            listeMessages->append(tr("<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            listeMessages->append(tr("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            listeMessages->append(tr("<em>ERREUR : le serveur a coupé la connexion.</em>"));
            break;
        default:
            listeMessages->append(tr("<em>ERREUR : ") + socket->errorString() + tr("</em>"));
    }

    boutonConnexion->setEnabled(true);
}
