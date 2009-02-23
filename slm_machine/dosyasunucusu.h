#ifndef DOSYASUNUCUSU_H
#define DOSYASUNUCUSU_H

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QFile>

class DosyaSunucusu :public QThread
{
    Q_OBJECT
public:
    DosyaSunucusu(QObject *parent=0);
    void run();

private:
    QTcpServer *sunucu;
    QTcpSocket *soket;
    QFile *yeniDokuman;

    void KabulMesajiGonder();

    quint16 block_size;
    quint32 DosyaBoyutu;
    quint32 gelenDosyaMiktari;
    QByteArray DosyaIcerigi;
    bool sunucuDurumu;
    void initializeVariables();

public slots:
    void sunucuBaglantisi();
    void mesajOku();
    void soketImha();
    void kullaniciCevabiniAl(bool,QString);
    void dosyayiTamamla();
signals:
    void yeniDosyaGeldi(QString,QString);
    void GonderimTamamlandi();
};

#endif // DOSYASUNUCUSU_H
