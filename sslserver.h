#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class SSLServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit SSLServer(QObject *parent = nullptr);
private:
    QTcpSocket* socket;
protected:
    void incomingConnection(qintptr socketDescriptor) override;

signals:

};

#endif // SSLSERVER_H
