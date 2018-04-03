#ifndef ADDNODEDLG_H
#define ADDNODEDLG_H

#include <QDialog>
#include <QHash>
namespace Ui {
class AddNodeDlg;
}

class AddNodeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddNodeDlg(QWidget *parent = 0);
    QHash<QString, QString>* getData() const;
    ~AddNodeDlg();

private slots:

private:
    Ui::AddNodeDlg *ui;
    QHash<QString, QString> * mData;
};

#endif // ADDNODEDLG_H
