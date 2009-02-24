#ifndef SLM_CLIENT_H
#define SLM_CLIENT_H

#include <QtGui/QMainWindow>
#include <QTcpSocket>
#include <QDateTime>
#include <QHostAddress>
#include <QTimer>
#include <QCloseEvent>
#include <QMessageBox>
#include "ui_slm_client.h"
#include "securestring.h"
#include "fileCrypto/filecrypter.h"
#include "fileSenderThread/filesender.h"

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
    fileCrypter crypto;

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
   void clearTextArea();
   
   //TODO
   //Following Code is only for test purposes and will be discarded after real implementation.
   void sendFileToBuddy();
   void startDecoding();
   //

private:
    bool guiKey;
    QString EncryptionKey;
    Ui::slm_clientWindow *m_ui;
    fileSender *yyy;
};

#endif // SLM_CLIENT_H
