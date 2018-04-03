#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocketServer>
#include <QLabel>
#include "websocketinstance.h"
#include "interpretermodel.h"
#include <QHostInfo>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnStart_clicked();

private:
    Ui::MainWindow *ui;
    QWebSocketServer * mWebSockServer;
    QList<QWebSocket*> mClients;
    QLabel *statusLabel;
    QLabel *statusLED;
    WebSocketInstance * webSock;
    InterpreterModel * IntpModel;

private Q_SLOTS:
    void onNewConnection();
    void onClientClosed();
    void on_btnStop_clicked();
    void processTextMessage(QString message);
    void onSockServClose();
    void on_actionImport_Certification_File_triggered();
    void on_actionImport_Key_File_triggered();
    void on_actionAdd_Node_triggred();
    void dummySlot(const QString & message);
    void on_btnSend_clicked();
};

#endif // MAINWINDOW_H
