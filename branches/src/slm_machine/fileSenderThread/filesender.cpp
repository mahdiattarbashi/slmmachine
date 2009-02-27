#include "filesender.h"

static quint32 const PAYLOADSIZE = 65536;

fileSender::fileSender(QObject *parent):QThread(parent)
{
}
void fileSender::run()
{
    block_size = 0;
    bytesWritten = 0;
    bytesRemaining = 0;
    fileSizeOfOutgoingFile = 0;
    fileContensOfOutgoingFile.clear();

    socket = new QTcpSocket();

    QObject::connect(socket, SIGNAL(connected()),this, SLOT(peerConnectionEstablished()),Qt::DirectConnection );
    QObject::connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(continueFileTransfer(qint64)),Qt::DirectConnection );
    QObject::connect(socket, SIGNAL(disconnected()),this, SLOT(peerConnectionBroken()),Qt::DirectConnection );

    socket->connectToHost(peerIP,3333,QIODevice::ReadWrite);

    QThread::exec();
}
void fileSender::peerConnectionEstablished()
{
    sendFileInfo();
    QObject::connect(socket,SIGNAL(readyRead()),this,SLOT(readPeerMessage()),Qt::DirectConnection );
}
void fileSender::peerConnectionBroken()
{
    emit peerConnectionClosed();
}
void fileSender::continueFileTransfer(qint64 miktar)
{

  bytesWritten += (int)miktar;

  if(bytesRemaining > 0)
  {
        fileContensOfOutgoingFile = outgoingFile->read(PAYLOADSIZE);
        bytesRemaining -= (int)socket->write(fileContensOfOutgoingFile.left(qMin(bytesRemaining, PAYLOADSIZE)));
        emit sendingCondition(bytesWritten);
  }

  if(bytesWritten >= fileSizeOfOutgoingFile && fileSizeOfOutgoingFile != 0)
  {
      qDebug() << fileSizeOfOutgoingFile;
      qDebug() << "Bytes Written: " << bytesWritten;
      outgoingFile->close();
      emit transferFinished();
  }
}
void fileSender::sendFileInfo()
{
    QFile dosya(filePathOfOutgoingFile);

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
        emit unknownMessageReceived();
    }
}

void fileSender::startFileTransfer()
{
    outgoingFile = new QFile(filePathOfOutgoingFile);

    outgoingFile->open(QIODevice::ReadOnly);
    fileSizeOfOutgoingFile = outgoingFile->size();
    fileContensOfOutgoingFile = outgoingFile->read(PAYLOADSIZE);
    emit sendingStarted(fileSizeOfOutgoingFile);
    bytesRemaining = fileSizeOfOutgoingFile - (int)socket->write(fileContensOfOutgoingFile);
}
