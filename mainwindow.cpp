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
    if(this->server.listen(QHostAddress(ui->ip->text()),ui->port->text().toUInt())){
        ui->log->append("Server listening on " + ui->ip->text() + ":" + ui->port->text());
    }
    connect(&this->server,SIGNAL(appendToLog(const QString&)), this, SLOT(appendToLogSlot(const QString&)));
    connect(&this->server,SIGNAL(updateClientList(const QVector<QTcpSocket*>&)), this, SLOT(updateClientListSlot(const QVector<QTcpSocket*>&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_start_server_clicked()
{
    if(this->server.listen(QHostAddress(ui->ip->text()),ui->port->text().toUInt())){
        ui->log->append("Server listening on " + ui->ip->text() + ":" + ui->port->text());
    }
}

void MainWindow::on_button_stop_server_clicked()
{
    this->server.close();
    if(!this->server.isListening()){
        ui->log->append("Server is stopped");
    }
}

void MainWindow::appendToLogSlot(const QString & str)
{
    ui->log->append(str);
}

void MainWindow::updateClientListSlot(const QVector<QTcpSocket*>& connectedSockets)
{
    ui->client_table->clearContents();
    ui->client_table->setRowCount(0);

    for(QTcpSocket* const &  s : connectedSockets){
        ui->client_table->insertRow(ui->client_table->rowCount());

       ui->client_table->setItem(ui->client_table->rowCount()-1,0, new QTableWidgetItem(s->peerAddress().toString() + ":" + QString::number(s->peerPort()) + " [" + QString::number(s->socketDescriptor()) + "]"));
      //ui->client_table->setItem(ui->client_table->rowCount()-1,0, new QTableWidgetItem("ahoj"));

    }
}
