#ifndef WEBSOCKETINSTANCE_H
#define WEBSOCKETINSTANCE_H

#include <QWebSocketServer>
#include <QSslSocket>
#include <QFile>
#include <QObject>
#include <QNetworkInterface>
class WebSocketInstance:  public QWebSocketServer
{

public:
    WebSocketInstance(QWebSocketServer::SslMode mode = SecureMode,
                      QHostAddress host= QHostAddress::Any,
                      qint16 port = 1368);
    WebSocketInstance(quint8 SockMode, QFile & certFileName, QFile & keyFileName);
public:
    bool startServer();
    QList<QHostAddress> getAvailableAddress(QAbstractSocket::NetworkLayerProtocol Protocol);
    void setHostPort(qint16 port);
    void setHostIP(QHostAddress host);
private:
    qint16 mPort;
    QHostAddress mHost;
signals:

};

#endif // WEBSOCKETINSTANCE_H
