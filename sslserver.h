#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class SSLServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit SSLServer(QObject *parent = nullptr);
private:
    QVector<QTcpSocket*> sockets;
protected:
    void incomingConnection(qintptr socketDescriptor) override;
private slots:
    void disconnectedSlot();
    void errorSlot(QAbstractSocket::SocketError);
    void stateChangedSlot(QAbstractSocket::SocketState);

signals:
    void appendToLog(const QString&);
    void updateClientList(const QVector<QTcpSocket*>&);
};

#endif // SSLSERVER_H
