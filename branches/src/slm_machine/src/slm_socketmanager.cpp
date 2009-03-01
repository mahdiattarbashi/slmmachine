#include "include/slm_socketmanager.h"

slm_socketmanager::slm_socketmanager(QTcpServer *server)
{
    newSocket = new QTcpSocket();
    newSocket = server->nextPendingConnection();
    connect(newSocket,SIGNAL(disconnected()),newSocket,SLOT(deleteLater()));
    connect(newSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));

}

void slm_socketmanager::readMessage()
{
    QHostAddress client_IPAddress;
    IncomingMessage = newSocket->readAll();
    client_IPAddress = newSocket->peerAddress();
    emit messageReady(IncomingMessage, client_IPAddress);
}
