#include "clientinfoview.h"
#include "ui_clientinfoview.h"

ClientInfoView::ClientInfoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientInfoView)
{
    ui->setupUi(this);
}

ClientInfoView::~ClientInfoView()
{
    delete ui;

}

void ClientInfoView::updateInfo(const QHash<QString, int>& receivedData)
{
    ui->progTemp->setValue(receivedData["temperature"]);
    ui->progTemp->update();

    ui->progPress->setValue(receivedData["pressure"]);
    ui->progPress->update();

    ui->progHumi->setValue(receivedData["humidity"]);
    ui->progHumi->update();
}

void ClientInfoView::onNewDataReceived(const QHash<QString, int> & receivedData )
{
    updateInfo(receivedData);
}
