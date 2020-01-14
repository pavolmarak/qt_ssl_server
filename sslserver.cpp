#include "sslserver.h"

SSLServer::SSLServer(QObject *parent) : QTcpServer(parent), socket(new QTcpSocket)
{

}

void SSLServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "We have a new connection";
}
