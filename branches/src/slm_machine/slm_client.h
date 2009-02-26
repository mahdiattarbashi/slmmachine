#ifndef SLM_CLIENT_H
#define SLM_CLIENT_H

#include <QtGui/QMainWindow>
#include <QTcpSocket>
#include <QDateTime>
#include <QHostAddress>
#include <QTimer>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QProgressDialog>
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
    QProgressDialog *progress;
    securestring encryptionObject;
    fileCrypter crypto;
    fileSender *fileSenderThread;

    void initiateClient(QString, QString);
    void closeEvent(QCloseEvent *event);
    void readMessagefromBuddy(QString, QHostAddress);
    void setGuiKey(bool);
    bool getGuiKey();
    void setEncryptionKey(QString);

signals:
   void destroyClient(QString);
   void showTrayMessageTransferCompleted();

public slots:
   void sendMessagetoBuddy();
   void displayError(QAbstractSocket::SocketError socketError);
   void clearTextArea();
   void fileSentCompleted();
   void sendFileToBuddy();
   void unknownMessage();
   void connectionBroken();
   void createFileProgress(quint32);
   void updateFileProgress(quint32);
   //TODO
   //Following Code is only for test purposes and will be discarded after real implementation.
   void startDecoding();
   //

private:
    bool guiKey;
    quint32 file_size_;
    QString EncryptionKey;
    Ui::slm_clientWindow *m_ui;

};

#endif // SLM_CLIENT_H