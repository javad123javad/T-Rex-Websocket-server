#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interpretermodel.h"
#include "clientinfoview.h"
#include "addnodedlg.h"
#include <QDebug>
#include <QWebSocket>
#include <QtCore/QFile>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>
#include <QLabel>
#include <QPixmap>
#include <QFileDialog>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mWebSockServer(new QWebSocketServer(nullptr,QWebSocketServer::SecureMode, this))
{
    ui->setupUi(this);
    //    QSslConfiguration sslConfiguration;
    //    QFile certFile(QStringLiteral(":/new/SSL/localhost.cert"));
    //    QFile keyFile(QStringLiteral(":/new/SSL/localhost.key"));
    //    certFile.open(QIODevice::ReadOnly);
    //    keyFile.open(QIODevice::ReadOnly);
    //    webSock = new WebSocketInstance(0,certFile, keyFile);
    //    QSslCertificate certificate(&certFile, QSsl::Pem);
    //    QSslKey sslKey(&keyFile, QSsl::Rsa, QSsl::Pem);
    //    certFile.close();
    //    keyFile.close();
    //    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    //    sslConfiguration.setLocalCertificate(certificate);
    //    sslConfiguration.setPrivateKey(sslKey);
    //    sslConfiguration.setProtocol(QSsl::TlsV1SslV3);
    //    mWebSockServer->setSslConfiguration(sslConfiguration);
    //    connect(mWebSockServer, &QWebSocketServer::newConnection, this, &MainWindow::onNewConnection);
    //    connect(mWebSockServer, &QWebSocketServer::closed, this, &MainWindow::onSockServClose);
    //    connect(webSock, &WebSocketInstance::closed, this, &MainWindow::onSockServClose);
    webSock = new WebSocketInstance(WebSocketInstance::SecureMode);
    connect(webSock, &WebSocketInstance::newConnection, this, &MainWindow::onNewConnection);
    connect(webSock, &WebSocketInstance::closed, this, &MainWindow::onSockServClose);
    connect(ui->action_Add_Node, &QAction::triggered, this, &MainWindow::on_actionAdd_Node_triggred);
    statusLabel = new QLabel(this);
    statusLED = new QLabel(this);
    statusLED->setPixmap(QPixmap(":/res/RED.png"));
    statusLabel->setText("Server Stoped.");
    ui->statusBar->addPermanentWidget(statusLabel);
    ui->statusBar->addPermanentWidget(statusLED);
    IntpModel = new InterpreterModel();
    connect(IntpModel, &InterpreterModel::sendMsgToClient, this, &MainWindow::dummySlot);
    // Below part is for Monitoring
    //    ClientInfoView * info1 = new ClientInfoView();
    //    ClientInfoView * info2 = new ClientInfoView();
    //    ClientInfoView * info3 = new ClientInfoView();
    //    ClientInfoView * info4 = new ClientInfoView();

    //    QWidget * tabBody = new QWidget();
    //    QGridLayout * mainLayout = new QGridLayout(tabBody);
    //    mainLayout->addWidget(info1,0,0,Qt::AlignTop);
    //    mainLayout->addWidget(info2,0,1,Qt::AlignTop);
    //    mainLayout->addWidget(info3,0,2,Qt::AlignTop);
    //    mainLayout->addWidget(info4,0,3,Qt::AlignTop);
    //    mainLayout->setVerticalSpacing(0);
    //    ui->tabWidget->addTab(tabBody,"Test");

    //    QHostInfo::lookupHost("localhost",
    //                          this, SLOT(onHostInfoFinished(QHostInfo)));
    foreach (const QHostAddress &address,
             webSock->getAvailableAddress(QAbstractSocket::IPv4Protocol)) {
        ui->cmbIpList->addItem(address.toString());
    }
    webSock->setHostIP(webSock->getAvailableAddress(QAbstractSocket::IPv4Protocol).at(2));

    // UI Settings
    ui->btnSend->setDisabled(true);
}

MainWindow::~MainWindow()
{
    // mWebSockServer->close();
    qDeleteAll(mClients.begin(), mClients.end());
    delete statusLabel;
    delete webSock;
    delete IntpModel;
    delete ui;
}

void MainWindow::on_btnStart_clicked()
{

    //    webSock->listen(QHostAddress::Any,1368);

    webSock->setHostIP(webSock->getAvailableAddress(
                           QAbstractSocket::IPv4Protocol).at(
                           ui->cmbIpList->currentIndex()));
    webSock->setHostPort(ui->linPortNum->text().toInt());
    webSock->startServer();
    statusLabel->setText("Server is running");
    statusLED->setPixmap(QPixmap(":/res/GREEN.png"));

    ui->btnStart->setDisabled(true);
    ui->btnStop->setEnabled(true);
    ui->btnSend->setEnabled(true);
}

void MainWindow::onNewConnection()
{
//    qDebug()<<"New client connected.";
    QWebSocket *pSocket = webSock->nextPendingConnection();
    connect(pSocket, &QWebSocket::textMessageReceived, this, &MainWindow::processTextMessage);
    connect(pSocket, &QWebSocket::textMessageReceived, IntpModel, &InterpreterModel::getMsgFromServer);
    connect(pSocket, &QWebSocket::disconnected, this, &MainWindow::onClientClosed);

    QString clientIP = "<font color=\"blue\">"+pSocket->peerAddress().toString()
            +" connected.</font>";
    ui->txtClientList->append(clientIP);
    mClients<<pSocket;

}
void MainWindow::onClientClosed()
{
    QWebSocket * clientSocket = static_cast<QWebSocket*>(sender());

    QString clientIP = "<font color=\"red\">"+clientSocket->peerAddress().toString()
            +" disconnected.</font>";
    ui->txtClientList->append(clientIP);
    mClients.removeOne(clientSocket);
}
void MainWindow::on_btnStop_clicked()
{
    //    mWebSockServer->close();
    webSock->close();
    ui->btnStart->setEnabled(true);
    ui->btnStop->setDisabled(true);

}

void MainWindow::processTextMessage(QString message)
{
    QWebSocket * clientSocket = static_cast<QWebSocket*>(sender());
        clientSocket->sendTextMessage("You are Server");
    QString peerIP = "<font color=\"red\">"+clientSocket->peerAddress().toString()+"</font>";
    ui->txtRecvData->append(peerIP+
                            ": "+message);
    //qDebug()<<"Received: "<<message;
}
void MainWindow::onSockServClose()
{
    statusLabel->setText("Server Stoped");
    statusLED->setPixmap(QPixmap(":/res/RED.png"));
}

void MainWindow::on_actionImport_Certification_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Certification File"), "~", tr("SSL Certification File (*.cert)"));

}

void MainWindow::on_actionImport_Key_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Key File"), "~", tr("SSL Key File (*.key)"));
}

void MainWindow::dummySlot(const QString & message)
{
    qDebug()<<"Horricaa.:"<< message;
}
void MainWindow::on_actionAdd_Node_triggred()
{
    AddNodeDlg * addNode = new AddNodeDlg();
    if(addNode->exec())
    {
        QHash<QString, QString> * mData = addNode->getData();
        qDebug()<<mData->value("nodeName");
    }
    delete addNode;
}



void MainWindow::on_btnSend_clicked()
{
    if(!mClients.isEmpty())
    {
        QWebSocket * clientSocket = mClients.first();
        if(clientSocket->sendTextMessage(ui->linCmd->text()) > 0)
        {
            ui->txtSentData->append("<font color=\"green\">Send to "+
                                    clientSocket->peerAddress().toString()+
                                    ":</font> "+
                                    ui->linCmd->text());
        };
    }
    else {
        QMessageBox::critical(this,"Send Error",
                              "No client is connected to the server.",QMessageBox::Ok);
        return;
    }

}
