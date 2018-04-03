#include "websocketinstance.h"
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>

WebSocketInstance::WebSocketInstance(QWebSocketServer::SslMode mode, QHostAddress host, qint16 port):
    QWebSocketServer("localhost",mode),
    mPort(port),
    mHost(host)
{
    //    QWebSocketServer("localhost",SecureMode);
    if(SecureMode == mode){
        QSslConfiguration sslConfiguration;
        QFile certFile(QStringLiteral(":/new/SSL/localhost.cert"));
        QFile keyFile(QStringLiteral(":/new/SSL/localhost.key"));
        certFile.open(QIODevice::ReadOnly);
        keyFile.open(QIODevice::ReadOnly);
        QSslCertificate certificate(&certFile, QSsl::Pem);
        QSslKey sslKey(&keyFile, QSsl::Rsa, QSsl::Pem);
        certFile.close();
        keyFile.close();
        sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
        sslConfiguration.setLocalCertificate(certificate);
        sslConfiguration.setPrivateKey(sslKey);
        sslConfiguration.setProtocol(QSsl::TlsV1SslV3);
        this->setSslConfiguration(sslConfiguration);
    }
}
WebSocketInstance::WebSocketInstance(quint8 SockMode, QFile & certFileName, QFile & keyFileName):
    QWebSocketServer("nullptr",SecureMode)
{
    Q_UNUSED(SockMode);Q_UNUSED(certFileName);Q_UNUSED(keyFileName);
}
bool WebSocketInstance::startServer()
{
    return this->listen(mHost, mPort);
}

QList<QHostAddress> WebSocketInstance::getAvailableAddress(QAbstractSocket::NetworkLayerProtocol Protocol)
{
    QList<QHostAddress> addresses;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
            addresses.append(address);
        }
    }

    return addresses;
}

void WebSocketInstance::setHostPort(qint16 port)
{
    this->mPort = port;
}

void WebSocketInstance::setHostIP(QHostAddress host)
{
    this->mHost = host;
}
