#ifndef FILESENDER_H
#define FILESENDER_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QByteArray>
#include <QDataStream>
#include <QRunnable>

class fileSender : public QThread
{
    Q_OBJECT
public:
    fileSender(QObject *parent=0);
    virtual ~fileSender(){}
    void run();
private:
    QTcpSocket *socket; //soket
    QString peerIP; //karsiIP
    QString filePathOfOutgoingFile; //gidecekDosyaYolu
    QString fileNameofOutgoingFile; //gidecekDosyaIsmi
    QFile *outgoingFile;//gonderilenDosya

    quint16 block_size;
    quint32 bytesWritten;//gonderilenMiktar
    quint32 bytesRemaining;//gonderilecekMiktar
    quint32 fileSizeOfOutgoingFile;//dosyaBoyutu
    QByteArray fileContensOfOutgoingFile;//dosyaIcerigi

    void sendFileInfo();//dosyaBilgisiGonder
    void startFileTransfer();//dosyaGonderBasla

public slots:
    void peerConnectionEstablished();//baglantiKuruldu
    void continueFileTransfer(qint64);//DosyaAkatarimiDevam
    void peerConnectionClosed();//baglantiKesildi
    void readPeerMessage();//mesajOku
};

#endif // FILESENDER_H
