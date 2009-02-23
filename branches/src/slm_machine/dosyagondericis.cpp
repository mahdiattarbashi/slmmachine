#include "dosyagondericis.h"

static quint32 const PAYLOADSIZE = 65536;

DosyaGondericis::DosyaGondericis(QObject *parent):QThread(parent)
{
}
void DosyaGondericis::run()
{
    karsiIP = "127.0.0.1";
    gidecekDosyaYolu = "D:/My Pictures/untitled.bmp";

    block_size = 0;
    gonderilenMiktar = 0;
    gonderilecekMiktar = 0;
    dosyaBoyutu = 0;
    dosyaIcerigi.clear();

    soket = new QTcpSocket();

    QObject::connect(soket, SIGNAL(connected()),this, SLOT(baglantiKuruldu()),Qt::DirectConnection );
    QObject::connect(soket, SIGNAL(bytesWritten(qint64)),this, SLOT(DosyaAkatarimiDevam(qint64)),Qt::DirectConnection );
    QObject::connect(soket, SIGNAL(disconnected()),this, SLOT(baglantiKesildi()),Qt::DirectConnection );

    soket->connectToHost(karsiIP,3333,QIODevice::ReadWrite);

    QThread::exec();
}
void DosyaGondericis::baglantiKuruldu()
{
    dosyaBilgisiGonder();
    QObject::connect(soket,SIGNAL(readyRead()),this,SLOT(mesajOku()),Qt::DirectConnection );
}
void DosyaGondericis::baglantiKesildi()
{
    //TODO
}
void DosyaGondericis::DosyaAkatarimiDevam(qint64 miktar)
{

  gonderilenMiktar += (int)miktar;

  if(gonderilecekMiktar > 0)
  {
        dosyaIcerigi = gonderilenDosya->read(PAYLOADSIZE);
        gonderilecekMiktar -= (int)soket->write(dosyaIcerigi.left(qMin(gonderilecekMiktar, PAYLOADSIZE)));
  }

  if(gonderilenMiktar >= dosyaBoyutu)
  {
    //Inform GUI Thread that file Transfer is completed!
      //Stop the Thread
  }
}
void DosyaGondericis::dosyaBilgisiGonder()
{
    QFile dosya(gidecekDosyaYolu);

    if(!dosya.exists())
    {
        //TODO
        //Inform GUI Thread that file does not exists so sending is canceled
        //Stop the thread
    }

    //extract filename only (without the path)
    int index = gidecekDosyaYolu.lastIndexOf('/');

    if(index != -1)
    {
        gidecekDosyaIsmi = gidecekDosyaYolu.right(gidecekDosyaYolu.length() - index - 1);
    }

    //send the file information
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    quint32 filesize = dosya.size();

    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << (quint8)'I' << gidecekDosyaIsmi << filesize;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    soket->write(block);
}

void DosyaGondericis::mesajOku()
{
    QDataStream in(soket);
    in.setVersion(QDataStream::Qt_4_0);

    if(block_size == 0)
    {
       in >> block_size;
    }

    quint8 mesajTipi;
    in >> mesajTipi;
    if(mesajTipi == 'A')
    {
        dosyaGonderBasla();
    }
    else
    {
        //TODO
        //Inform GUI Thread that an unknown Message is received.
    }
}

void DosyaGondericis::dosyaGonderBasla()
{
    gonderilenDosya = new QFile(gidecekDosyaYolu);

    if(!gonderilenDosya->open(QIODevice::ReadOnly))
    {
        //TODO
        //Inform GUI thread that file cannot be opened. Transfer cancelled,
        //Stop the thread
    }

    dosyaBoyutu = gonderilenDosya->size();
    dosyaIcerigi = gonderilenDosya->read(PAYLOADSIZE);

    gonderilecekMiktar = dosyaBoyutu - (int)soket->write(dosyaIcerigi);
}
