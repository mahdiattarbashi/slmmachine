#ifndef FILESENDER_H
#define FILESENDER_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QByteArray>
#include <QDataStream>

class fileSender : public QThread
{
    Q_OBJECT
public:
    fileSender(QObject *parent=0);
    virtual ~fileSender(){}
    void run();
    QString peerIP;
    QString filePathOfOutgoingFile;
    bool encOrNot;
private:
    QTcpSocket *socket;

    QString fileNameofOutgoingFile;
    QFile *outgoingFile;

    quint16 block_size;
    quint32 bytesWritten;
    quint32 bytesRemaining;
    quint32 fileSizeOfOutgoingFile;
    QByteArray fileContensOfOutgoingFile;

    void sendFileInfo();
    void startFileTransfer();

public slots:
    void peerConnectionEstablished();
    void continueFileTransfer(qint64);
    void peerConnectionBroken();
    void readPeerMessage();
signals:
    void sendingStarted(quint32);
    void sendingCondition(quint32);
    void transferFinished();
    void unknownMessageReceived();
    void peerConnectionClosed();
    void transferRejected();
    void waitingUserResponse();
};

#endif // FILESENDER_H
