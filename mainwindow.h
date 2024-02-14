#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "UdpWorker.h"

#define TIMER_DELAY 1000

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void receivedText(QString strDate);
    void on_pb_start_clicked();
    void DisplayTime(QDateTime data);
    void DisplayText(QByteArray data, QHostAddress senderAddress);
    void on_pb_stop_clicked();


    void on_pb_sendDate_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    UDPworker* udpWorker;
    UDPworker* udpWorkerTEXT;
    uint32_t counterPck = 0;
    QByteArray strReceived ;


};
#endif // MAINWINDOW_H
