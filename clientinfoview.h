#ifndef CLIENTINFOVIEW_H
#define CLIENTINFOVIEW_H

#include <QWidget>
#include <QHash>
namespace Ui {
class ClientInfoView;
}

class ClientInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit ClientInfoView(QWidget *parent = 0);
    ~ClientInfoView();

private:
    Ui::ClientInfoView *ui;
    void updateInfo(const QHash<QString, int> & receivedData);
private Q_SLOTS:
    void onNewDataReceived(const QHash<QString, int> & receivedData );

signals:
    void updateClient();
};

#endif // CLIENTINFOVIEW_H
