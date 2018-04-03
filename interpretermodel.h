#ifndef INTERPRETERMODEL_H
#define INTERPRETERMODEL_H

#include <QObject>

class InterpreterModel : public QObject
{
    Q_OBJECT
public:
    explicit InterpreterModel(QObject *parent = nullptr);

private:
    void encodeMsg(const QString & message);
    void decodeMsg(const QString & message);
signals:
    void sendMsgToClient(const QString & message);// Send decoded message to the server.
    void sendMsgToServer(const QString & message);// send encoded Message to the server.
public slots:
    void getMsgFromServer(const QString & message);// get Encoded message from server.
    void getMsgFromClient(const QString & message);// get plain message from server.
};

#endif // INTERPRETERMODEL_H
