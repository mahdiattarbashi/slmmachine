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
#include <QMutex>
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
    QTcpServer *server;//sunucu
    QTcpSocket *socket;//soket
    QFile *newDocument;//yeniDokuman

    void sendAcceptMessage();//KabulMesajiGonder

    quint16 block_size;
    quint32 IncomingFileSize;//DosyaBoyutu
    quint32 bytesWritten;//gelenDosyaMiktari
    QByteArray fileContents;//DosyaIcerigi
    bool serverState;//sunucuDurumu
    void initializeVariables();//initializeVariables

public slots:
    void peerConnection();//sunucuBaglantisi
    void readMessage();//mesajOku
    void destroySocket();//soketImha
    void getUserAnswer(bool,QString);//kullaniciCevabiniAl
    void finishDocument();//dosyayiTamamla

signals:
    void newDocumentArrived(QString,QString,quint32);//yeniDosyaGeldi
    void transferCompleted();//GonderimTamamlandi
    void transferCanceled();
    void unknownMessageArrived();
    void ongoingTransfer();
    void receivingProgress(quint32);
};

#endif // FILESERVER_H
