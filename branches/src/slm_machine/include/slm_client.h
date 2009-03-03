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
#include <QThreadPool>
#include "../ui_slm_client.h"
#include "../include/securestring.h"
#include "../fileCrypto/filecrypter.h"
#include "../fileSenderThread/filesender.h"

namespace Ui {
    class slm_client;
}

class slm_client : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY(slm_client)
public:
    explicit slm_client(QWidget *parent = 0);
    virtual ~slm_client();
    //TODO: Generate Getters&Setters
    QTcpSocket *outgoingSocket;
    QString slmclientIPAddress;
    QString outGoingTextString;
    QByteArray outGoingTextArray;
    QProgressDialog *progress;

    QMessageBox *encrypting;
    securestring encryptionObject;
    fileCrypter *crypto;
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
   void encryptingStarted();
   void encryptingFinished();

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
   void transfer();
//Getters & Setters
   void setClientName(QString clientName);
   QString getClientName() const;
private:
   enum EchoType
   {
     ERROR = 0,
     WARNING,
     INFO
   };
    bool guiKey;
    QString m_slmclientName;
    quint32 file_size_;
    QString EncryptionKey;
    Ui::slm_clientWindow *m_ui;
    QString filepathString;
    QString encryptedFileName;
    bool m_isLastMessageSendByMe;
    void echo(EchoType type, QString message);

};

#endif // SLM_CLIENT_H
