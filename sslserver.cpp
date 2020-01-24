#include "sslserver.h"

SSLServer::SSLServer(QObject *parent) : QTcpServer(parent)
{
    pathToCert = QString(PRO_PWD)+"/cert/server.cert.pem";
    pathToPrivateKey= QString(PRO_PWD)+"/cert/server.key.pem";
    qDebug() << pathToCert;
}

void SSLServer::incomingConnection(qintptr socketDescriptor)
{
    QSslSocket* socket = new QSslSocket;

    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnectedSlot()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(errorSlot(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),this, SLOT(stateChangedSlot(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(sslErrors(const QList<QSslError> &)),this, SLOT(sslErrorsSlot(const QList<QSslError> &)));
    socket->setPrivateKey(pathToPrivateKey);
    socket->setLocalCertificate(pathToCert);
    socket->setSocketDescriptor(socketDescriptor);


    qDebug() << socket->localCertificate().isNull();

    this->sockets.push_back(socket);
    emit appendToLog("Server received a new connection [socket descriptor: " + QString::number(socketDescriptor) + "]");
    emit updateClientList(this->sockets);
}

void SSLServer::disconnectedSlot()
{
    QSslSocket* socket = qobject_cast<QSslSocket*>(sender());
    this->sockets.removeOne(socket);

    emit appendToLog("Client disconnected " + socket->peerAddress().toString() + ":" + QString::number(socket->peerPort()));
    emit updateClientList(this->sockets);
}

void SSLServer::errorSlot(QAbstractSocket::SocketError e)
{
    emit appendToLog("Socket Error: " + QString::number(e));
}

void SSLServer::stateChangedSlot(QAbstractSocket::SocketState s)
{
  emit appendToLog("Socket State: " + QString::number(s));
}

void SSLServer::sslErrorsSlot(const QList<QSslError> &)
{
    emit appendToLog("SSL Error");
}
