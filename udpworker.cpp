#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{



}


/*!
 * @brief Метод инициализирует UDP сервер
 */
void UDPworker::InitSocket()
{
    senderAddress = QHostAddress();
    serviceUdpSocket = new QUdpSocket(this);
    textUdpSocket = new QUdpSocket(this);
    /*
     * Соединяем присваиваем адрес и порт серверу и соединяем функцию
     * обраотчик принятых пакетов с сокетом
     */
    serviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT);

    textUdpSocket ->bind(QHostAddress::LocalHost, BIND_PORT);


    connect(serviceUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingDatagrams);
    qDebug() << "connect";
    connect(textUdpSocket, &QUdpSocket::readyRead, this, &UDPworker::readPendingText);



}

/*!
 * @brief Метод осуществляет обработку принятой датаграммы
 */\

QHostAddress UDPworker::getSenderAddress() const
{

    return senderAddress;
}
void UDPworker::ReadDatagram(QNetworkDatagram datagram)
{
    qDebug() << "ReadDatagram";
    QByteArray data;
    data = datagram.data();


    QDataStream inStr(&data, QIODevice::ReadOnly);
    QDateTime dateTime;
    inStr >> dateTime;

    emit sig_sendTimeToGUI(dateTime);
}

void UDPworker::ReadDatagramText(QNetworkDatagram datagram)
{

    qDebug() << "ReadDatagramText";
    QByteArray data;
    data = datagram.data();
    senderAddress = datagram.senderAddress();
    qDebug() << data << "qqqqq";

    emit sig_sendTimeTEXT (data, senderAddress);

}
/*!
 * @brief Метод осуществляет опередачу датаграммы
 */
void UDPworker::SendDatagram(QByteArray data)
{
    /*
     *  Отправляем данные на localhost и задефайненный порт
     */

    serviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}
void UDPworker::SendText(QByteArray data)
{
     qDebug() << "SendText";
    textUdpSocket -> writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}

/*!
 * @brief Метод осуществляет чтение датаграм из сокета
 */
void UDPworker::readPendingDatagrams( void )
{
    /*
     *  Производим чтение принятых датаграмм
     */qDebug() << "Read pending for service";
    while (serviceUdpSocket->hasPendingDatagrams()){
            QNetworkDatagram datagram = serviceUdpSocket->receiveDatagram();
            ReadDatagram(datagram);
    }
}
void UDPworker::readPendingText( void )
{
    qDebug() << "Read pending for textUdpSocket";

    while (textUdpSocket->hasPendingDatagrams()){
         QNetworkDatagram datagram = textUdpSocket->receiveDatagram();
         ReadDatagramText(datagram);
     };
}
