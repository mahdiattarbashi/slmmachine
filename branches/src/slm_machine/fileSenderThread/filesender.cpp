#include "filesender.h"

static quint32 const PAYLOADSIZE = 65536;

fileSender::fileSender(QObject *parent):QThread(parent)
{
}
void fileSender::run()
{
    peerIP = "127.0.0.1";
    filePathOfOutgoingFile = "D:/My Pictures/untitled.bmp";

    block_size = 0;
    bytesWritten = 0;
    bytesRemaining = 0;
    fileSizeOfOutgoingFile = 0;
    fileContensOfOutgoingFile.clear();

    socket = new QTcpSocket();

    QObject::connect(socket, SIGNAL(connected()),this, SLOT(peerConnectionEstablished()),Qt::DirectConnection );
    QObject::connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(continueFileTransfer(qint64)),Qt::DirectConnection );
    QObject::connect(socket, SIGNAL(disconnected()),this, SLOT(peerConnectionClosed()),Qt::DirectConnection );

    socket->connectToHost(peerIP,3333,QIODevice::ReadWrite);

    QThread::exec();
}
void fileSender::peerConnectionEstablished()
{
    sendFileInfo();
    QObject::connect(socket,SIGNAL(readyRead()),this,SLOT(readPeerMessage()),Qt::DirectConnection );
}
void fileSender::peerConnectionClosed()
{
    //TODO
}
void fileSender::continueFileTransfer(qint64 miktar)
{

  bytesWritten += (int)miktar;

  if(bytesRemaining > 0)
  {
        fileContensOfOutgoingFile = outgoingFile->read(PAYLOADSIZE);
        bytesRemaining -= (int)socket->write(fileContensOfOutgoingFile.left(qMin(bytesRemaining, PAYLOADSIZE)));
  }

  if(bytesWritten >= fileSizeOfOutgoingFile)
  {
    //Inform GUI Thread that file Transfer is completed!
      //Stop the Thread
  }
}
void fileSender::sendFileInfo()
{
    QFile dosya(filePathOfOutgoingFile);

    if(!dosya.exists())
    {
        //TODO
        //Inform GUI Thread that file does not exists so sending is canceled
        //Stop the thread
    }

    //extract filename only (without the path)
    int index = filePathOfOutgoingFile.lastIndexOf('/');

    if(index != -1)
    {
        fileNameofOutgoingFile = filePathOfOutgoingFile.right(filePathOfOutgoingFile.length() - index - 1);
    }

    //send the file information
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    quint32 filesize = dosya.size();

    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << (quint8)'I' << fileNameofOutgoingFile << filesize;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    socket->write(block);
}

void fileSender::readPeerMessage()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);

    if(block_size == 0)
    {
       in >> block_size;
    }

    quint8 mesajTipi;
    in >> mesajTipi;
    if(mesajTipi == 'A')
    {
        startFileTransfer();
    }
    else
    {
        //TODO
        //Inform GUI Thread that an unknown Message is received.
    }
}

void fileSender::startFileTransfer()
{
    outgoingFile = new QFile(filePathOfOutgoingFile);

    if(!outgoingFile->open(QIODevice::ReadOnly))
    {
        //TODO
        //Inform GUI thread that file cannot be opened. Transfer cancelled,
        //Stop the thread
    }

    fileSizeOfOutgoingFile = outgoingFile->size();
    fileContensOfOutgoingFile = outgoingFile->read(PAYLOADSIZE);

    bytesRemaining = fileSizeOfOutgoingFile - (int)socket->write(fileContensOfOutgoingFile);
}
