#ifndef SLM_SOCKETMANAGER_H
#define SLM_SOCKETMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include "include/slm_server.h"

class slm_socketmanager : public QObject
{
    Q_OBJECT
public:
    slm_socketmanager(QTcpServer *server);
    QTcpSocket *newSocket;
    QByteArray IncomingMessage;

public slots:
    void readMessage();
signals:
    void messageReady(QByteArray, QHostAddress);

};

#endif // SLM_SOCKETMANAGER_H
