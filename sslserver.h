#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QSslSocket>
#include <QVector>
#include <QDir>

class SSLServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit SSLServer(QObject *parent = nullptr);
private:
    QVector<QSslSocket*> sockets;
    QString pathToCert,pathToPrivateKey;
protected:
    void incomingConnection(qintptr socketDescriptor) override;
private slots:
    void disconnectedSlot();
    void errorSlot(QAbstractSocket::SocketError);
    void stateChangedSlot(QAbstractSocket::SocketState);
    void sslErrorsSlot(const QList<QSslError> &);

signals:
    void appendToLog(const QString&);
    void updateClientList(const QVector<QSslSocket*>&);
};

#endif // SSLSERVER_H
