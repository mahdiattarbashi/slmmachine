#ifndef SLM_CLIENT_H
#define SLM_CLIENT_H

#include <QtGui/QMainWindow>
#include <QTcpSocket>
#include <QDateTime>
#include <QHostAddress>
#include "ui_slm_client.h"
#include "securestring.h"

namespace Ui {
    class slm_client;
}

class slm_client : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY(slm_client)
public:
    explicit slm_client(QWidget *parent = 0);
    virtual ~slm_client();

    QTcpSocket *outgoingSocket;
    QString slmclientName;
    QString slmclientIPAddress;
    QString outGoingTextString;
    QByteArray outGoingTextArray;
    securestring encryptionObject;

    void initiateClient(QString, QString);
    void closeEvent(QCloseEvent *event);
    void readMessagefromBuddy(QString, QHostAddress);
    void setGuiKey(bool);
    bool getGuiKey();
    void setEncryptionKey(QString);

signals:
   void destroyClient(QString);

public slots:
   void sendMessagetoBuddy();
   void displayError(QAbstractSocket::SocketError socketError);

private:
    bool guiKey;
    QString EncryptionKey;
    Ui::slm_clientWindow *m_ui;
};

#endif // SLM_CLIENT_H
