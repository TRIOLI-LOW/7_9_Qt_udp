#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendTimeTEXT, this, &MainWindow::DisplayText);

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);



    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;

        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;
        qDebug() << " data"<< dataToSend;
        udpWorker->SendDatagram(dataToSend);
        qDebug() << " data"<< dataToSend;
        timer->start(TIMER_DELAY);
    });


    connect(ui->pb_sendDate, &QPushButton::clicked, this, [&] {
        if (!strReceived.isEmpty()) {

            QByteArray TextToSend;
            qDebug() << "Text to send: " << strReceived;

            QDataStream outStr1(&TextToSend, QIODevice::WriteOnly);
            outStr1 << strReceived;

            udpWorker->SendText(TextToSend);
        }
    });





}



void MainWindow::on_pb_sendDate_clicked()
{

    strReceived = ui->te_sendDate->toPlainText().toUtf8();

}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}

void MainWindow::DisplayText(QByteArray data, QHostAddress senderAddress)
{
    qDebug()<< "DisplayText &&&";
    ui->te_result->setText(QString("Принято сообщение от адреса %1, размер сообщения(%2 байт), %3")
                                    .arg(senderAddress.toString())
                                    .arg(data.size())
                                    .arg(QString(data)));

}

void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));

}


void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}




