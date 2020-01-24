#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->client_table->insertColumn(0);
    ui->client_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->client_table->setHorizontalHeaderLabels(QStringList() << "Client information");
    startServer();
    connect(&this->server,SIGNAL(appendToLog(const QString&)), this, SLOT(appendToLogSlot(const QString&)));
    connect(&this->server,SIGNAL(updateClientList(const QVector<QSslSocket*>&)), this, SLOT(updateClientListSlot(const QVector<QSslSocket*>&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startServer()
{
    if(this->server.listen(QHostAddress(ui->ip->text()),ui->port->text().toUInt())){
        ui->log->append("Server listening on " + ui->ip->text() + ":" + ui->port->text());
    }
    else{
        ui->log->append("Server has failed to start.");
    }
}

void MainWindow::stopServer()
{
    this->server.close();
    if(!this->server.isListening()){
        ui->log->append("Server is stopped");
    }
    else{
        ui->log->append("Server has failed to stop.");
    }
}


void MainWindow::on_button_start_server_clicked()
{
    startServer();
}

void MainWindow::on_button_stop_server_clicked()
{
    stopServer();
}

void MainWindow::appendToLogSlot(const QString & str)
{
    ui->log->append(str);
}

void MainWindow::updateClientListSlot(const QVector<QSslSocket*>& connectedSockets)
{
    ui->client_table->clearContents();
    ui->client_table->setRowCount(0);

    for(QSslSocket* const &  s : connectedSockets){
        ui->client_table->insertRow(ui->client_table->rowCount());

       ui->client_table->setItem(ui->client_table->rowCount()-1,0, new QTableWidgetItem(s->peerAddress().toString() + ":" + QString::number(s->peerPort()) + " [" + QString::number(s->socketDescriptor()) + "]"));
      //ui->client_table->setItem(ui->client_table->rowCount()-1,0, new QTableWidgetItem("ahoj"));

    }
}
