#include "interpretermodel.h"
#include <QDebug>
InterpreterModel::InterpreterModel(QObject *parent) : QObject(parent)
{

}

void InterpreterModel::getMsgFromServer(const QString & message)
{
    qDebug()<<"Intp Class: Message received from server successfully."<<message;
    decodeMsg(message);
}
void InterpreterModel::getMsgFromClient(const QString &message)
{
    qDebug()<<"Intp Class: Message Received from Client Widget.";
    encodeMsg(message);
}
void InterpreterModel::encodeMsg(const QString & message)
{
    emit sendMsgToServer("Encoded:" + message);
}

void InterpreterModel::decodeMsg(const QString &message)
{
    emit sendMsgToClient("Encoded: " + message);
}
