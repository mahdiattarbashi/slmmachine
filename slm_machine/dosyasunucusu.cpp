#include "dosyasunucusu.h"

static quint32 const PAYLOADSIZE = 65536;

DosyaSunucusu::DosyaSunucusu(QObject *parent):QThread(parent)
{

}
void DosyaSunucusu::initializeVariables()
{

    block_size = 0;
    DosyaBoyutu = 0;
    sunucuDurumu = 0;
    gelenDosyaMiktari = 0;
    DosyaIcerigi.clear();
}
void DosyaSunucusu::run()
{
    sunucu = new QTcpServer();
    // start listen for incoming connections
    if(!sunucu->listen(QHostAddress::Any, 3333))
    {
        qDebug()<<"File Server cannot be initialized";
    }
    else
    {
        qDebug()<<"File Server initialized";
        QObject::connect(sunucu,SIGNAL(newConnection()),this,SLOT(sunucuBaglantisi()),Qt::DirectConnection);
    }

    //Initialize Variables
    initializeVariables();

    QThread::exec();
}
void DosyaSunucusu::sunucuBaglantisi()
{
    if(sunucuDurumu == 0)
    {
        sunucuDurumu = 1;
        soket = new QTcpSocket();
        soket = sunucu->nextPendingConnection();
        QObject::connect(soket,SIGNAL(readyRead()),this,SLOT(mesajOku()),Qt::DirectConnection );
        QObject::connect(soket,SIGNAL(disconnected()),this,SLOT(soketImha()),Qt::DirectConnection );
    }
    else
    {
        //TODO
        //Inform GUI Thread that there is an ongoing transfer!
    }
}
void DosyaSunucusu::mesajOku()
{
    QDataStream in(soket);
    in.setVersion(QDataStream::Qt_4_0);

    if(block_size == 0)
    {
        in >> block_size;
    }

    quint8 mesajTipi;
    QString DosyaIsmi;
    QString DosyaBoyutuCumlesi;

    in >> mesajTipi;

    if(mesajTipi == 'I')
    {
        in >> DosyaIsmi >> DosyaBoyutu;

        if(DosyaBoyutu < 1024)
        {
            DosyaBoyutuCumlesi = tr("%1 Byte").arg(DosyaBoyutu);
        }
        else if(DosyaBoyutu < 1048576)
        {
            DosyaBoyutuCumlesi = tr("%1 KB").arg(static_cast<double>(DosyaBoyutu) / 1024, 0, 'f', 2);
        }
        else if(DosyaBoyutu < 1073741824)
        {
           DosyaBoyutuCumlesi = tr("%1 MB").arg(static_cast<double>(DosyaBoyutu) / 1048576, 0, 'f', 2);
        }
        else
        {
            DosyaBoyutuCumlesi = tr("%1 GB").arg(static_cast<double>(DosyaBoyutu) / 1073741824, 0, 'f', 2);
        }

        //Inform GUI Thread about incoming file
        emit yeniDosyaGeldi(DosyaIsmi, DosyaBoyutuCumlesi);

        //TODO
        //following code block will be updated!!!!!!!!!
        kullaniciCevabiniAl(1,"C:/deneme.bmp");
    }
    else
    {
    }

}
void DosyaSunucusu::kullaniciCevabiniAl(bool cevap, QString DosyaYeri)
{
    if(cevap == 1 && DosyaYeri != "")
    {
        yeniDokuman = new QFile(DosyaYeri);

        if(!yeniDokuman->open(QIODevice::WriteOnly))
        {
            //TODO
            //Inform GUI Thread that file cannot be written and quit transfer
            initializeVariables();
        }

        KabulMesajiGonder();

        DosyaIcerigi.resize(PAYLOADSIZE);
        QObject::disconnect(soket, SIGNAL(readyRead()), 0, 0);
        QObject::connect(soket,SIGNAL(readyRead()),this, SLOT(dosyayiTamamla()),Qt::DirectConnection );
    }
    else
    {
        //TODO
        //Inform GUI transfer is canceled and Go back to listening State again
        QObject::disconnect(soket, SIGNAL(readyRead()), 0, 0);
        QObject::connect(soket,SIGNAL(readyRead()),this, SLOT(mesajOku()),Qt::DirectConnection );
        initializeVariables();
    }
}
void DosyaSunucusu::KabulMesajiGonder()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << (quint8)'A';
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    soket->write(block);
}
void DosyaSunucusu::dosyayiTamamla()
{
      gelenDosyaMiktari += (int)soket->bytesAvailable();
      DosyaIcerigi.clear();
      DosyaIcerigi.resize(PAYLOADSIZE);
      DosyaIcerigi = soket->readAll();

      yeniDokuman->write(DosyaIcerigi);

      if(gelenDosyaMiktari == DosyaBoyutu)
      {

        QObject::disconnect(soket, SIGNAL(readyRead()), 0, 0);
        QObject::connect(soket,SIGNAL(readyRead()),this, SLOT(mesajOku()),Qt::DirectConnection );
        yeniDokuman->flush();
        yeniDokuman->close();
        emit GonderimTamamlandi();
  }
}
void DosyaSunucusu::soketImha()
{
    delete soket;
}
