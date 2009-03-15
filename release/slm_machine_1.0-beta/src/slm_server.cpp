#include "slm_server.h"
#include "slm_socketmanager.h"

slm_server* slm_server::m_instance = NULL;

slm_server::slm_server()
{
    server = new QTcpServer();

    server->listen(QHostAddress::Any, 29999);
    connect(server, SIGNAL(newConnection()), this, SLOT(connectionEstablished()));
}

void slm_server::connectionEstablished()
{
    //Create a socket object
    slm_socketmanager *client = new slm_socketmanager(server);
    connect(client, SIGNAL(messageReady(QByteArray,QHostAddress)), this, SLOT(informUI(QByteArray,QHostAddress)));
}

void slm_server::informUI(QByteArray message, QHostAddress peerAddress)
{
    emit sendtoUI(message,peerAddress);
}

slm_server* slm_server::getInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new slm_server();

    }
    return m_instance;
}
