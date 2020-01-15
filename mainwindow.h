#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "sslserver.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_start_server_clicked();
    void on_button_stop_server_clicked();
    void appendToLogSlot(const QString&);
    void updateClientListSlot(const QVector<QTcpSocket*>&);

private:
    Ui::MainWindow *ui;
    SSLServer server;

};
#endif // MAINWINDOW_H
