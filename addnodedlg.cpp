#include "addnodedlg.h"
#include "ui_addnodedlg.h"

AddNodeDlg::AddNodeDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNodeDlg),
    mData(new QHash<QString, QString>)
{
    ui->setupUi(this);

}

AddNodeDlg::~AddNodeDlg()
{
    delete mData;
    delete ui;
}

QHash<QString, QString>* AddNodeDlg::getData() const
{
    mData->insert("nodeID", ui->linID->text());
    mData->insert("nodeIP",ui->linIP->text());
    mData->insert("nodeName", ui->linName->text());
    mData->insert("nodeDesc", ui->txtDesc->toPlainText());

    return mData;
}
