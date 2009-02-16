#ifndef SLM_SERVER_H
#define SLM_SERVER_H

#include <QObject>
#include <QtNetwork>

class slm_server : public QObject
{
    Q_OBJECT
public:
    static slm_server* getInstance();
    QTcpServer *server;
public slots:
    void connectionEstablished();
    void informUI(QByteArray, QHostAddress);
private:
    slm_server();
    static slm_server *m_instance;

signals:
    void sendtoUI(QByteArray, QHostAddress);
};

#endif // SLM_SERVER_H
