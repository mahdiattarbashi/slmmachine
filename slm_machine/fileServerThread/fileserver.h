#ifndef FILESERVER_H
#define FILESERVER_H

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QSemaphore>

class fileServer :public QThread
{
    Q_OBJECT
public:
    fileServer(QObject *parent=0);
    void run();
    bool userAnswer;
    bool userAnswered;
    QSemaphore *answerSemaphore;

private:
    QTcpServer *server;
    QTcpSocket *socket;
    QFile *newDocument;

    void sendAcceptMessage();

    quint16 block_size;
    quint32 IncomingFileSize;
    quint32 bytesWritten;
    QByteArray fileContents;
    bool serverState;
    void initializeVariables();
    QString defaultSaveDirectory;

public slots:
    void peerConnection();
    void readMessage();
    void destroySocket();
    void getUserAnswer(bool,QString);
    void finishDocument();

signals:
    void newDocumentArrived(QString,QString,quint32);
    void transferCompleted();
    void transferCanceled();
    void unknownMessageArrived();
    void ongoingTransfer();
    void receivingProgress(quint32);
};

#endif // FILESERVER_H
