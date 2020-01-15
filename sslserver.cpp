#include "sslserver.h"

SSLServer::SSLServer(QObject *parent) : QTcpServer(parent)
{

}

void SSLServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnectedSlot()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(errorSlot(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),this, SLOT(stateChangedSlot(QAbstractSocket::SocketState)));
    this->sockets.push_back(socket);
    emit appendToLog("Server received a new connection [socket descriptor: " + QString::number(socketDescriptor) + "]");
    emit updateClientList(this->sockets);
}

void SSLServer::disconnectedSlot()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    this->sockets.removeOne(socket);

    emit appendToLog("Client disconnected " + socket->peerAddress().toString() + ":" + QString::number(socket->peerPort()));
    emit updateClientList(this->sockets);
}

void SSLServer::errorSlot(QAbstractSocket::SocketError)
{

}

void SSLServer::stateChangedSlot(QAbstractSocket::SocketState)
{

}
