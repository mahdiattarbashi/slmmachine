#ifndef DOSYAGONDERICIS_H
#define DOSYAGONDERICIS_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QFile>
#include <QByteArray>
#include <QDataStream>
#include <QRunnable>

class DosyaGondericis : public QThread
{
    Q_OBJECT
public:
    DosyaGondericis(QObject *parent=0);
    virtual ~DosyaGondericis(){}
    void run();
private:
    QTcpSocket *soket;
    QString karsiIP;
    QString gidecekDosyaYolu;
    QString gidecekDosyaIsmi;
    QFile *gonderilenDosya;

    quint16 block_size;
    quint32 gonderilenMiktar;
    quint32 gonderilecekMiktar;
    quint32 dosyaBoyutu;
    QByteArray dosyaIcerigi;

    void dosyaBilgisiGonder();
    void dosyaGonderBasla();

public slots:
    void baglantiKuruldu();
    void DosyaAkatarimiDevam(qint64);
    void baglantiKesildi();
    void mesajOku();
};

#endif // DOSYAGONDERICIS_H
