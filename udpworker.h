#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QDateTime>


#define BIND_PORT 12345
#define LOCAL_HOST 127.0.0.1

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);
    void InitSocket( void );
    void ReadDatagram( QNetworkDatagram datagram);
    void ReadDatagramText( QNetworkDatagram datagram);
    void SendDatagram(QByteArray data );
    void SendText(QByteArray data);
    void setText (QByteArray data );
    QHostAddress getSenderAddress() const;

private slots:
    void readPendingDatagrams(void);
    void readPendingText(void);

private:
    QUdpSocket* serviceUdpSocket;
    QUdpSocket* textUdpSocket;
    QByteArray textByte;
    QHostAddress senderAddress;
signals:
    void sig_sendTimeToGUI(QDateTime data);
    void sig_sendTimeTEXT (QByteArray data, QHostAddress senderAddress);
};

#endif // UDPWORKER_H
