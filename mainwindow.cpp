#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&thread, SIGNAL(tick()), this, SLOT(externalThread_tick()));
    connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(sendCommand()));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(testValues()));
    timer->start(100);

    time.resize(N);
    time.fill(0);
    buffer.resize(N);
    buffer.fill(0);

    chart.gridNumX=N/10;
    chart.gridCircle=10;
    chart.gridNumY=11;
    chart.minValueX= 1;
    chart.maxValueX= N;
    chart.minValueY=0;
    chart.maxValueY=4.0;
    chart.dataSize=N;



    ui->statusBar->showMessage("No device");
    QString portname;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {

        if(info.serialNumber()=="NXP-77"){

            portname=info.portName();
            serial.setPortName(portname);
            if (serial.open(QIODevice::ReadWrite)) {

                serial.setBaudRate( serial.Baud115200,  serial.AllDirections);
                ui->statusBar->showMessage(tr("Device: %1").arg(info.serialNumber()));
                serial.clear();
                thread.start(thread.HighestPriority);
            }
            else
            {
                ui->statusBar->showMessage(tr("Can't open %1, error code %2") .arg(serial.portName()).arg(serial.error()));
                return;
            }
            break;
        }
    }


}

MainWindow::~MainWindow()
{
    thread.terminate();
    thread.wait();
    serial.close();
    delete ui;
}

void MainWindow::externalThread_tick()
{
    if (serial.size() >= 2){

        qDebug()<<serial.size();
        readdata=serial.readAll();

        uint16_t *sample=reinterpret_cast<uint16_t*>(readdata.data());
        qDebug() << *sample;
        buffer[n] = static_cast<double>((*sample))/4096;

        for(int i = 0; i < N; i++){
            time[i] = buffer[(i+(n))%N];
        }
        n--;
        if(n<0){
            n = N-1;
        }
        update();

        if(ui->actionRun->isChecked()){
            sendCommand();
        }
    }
}

void MainWindow::sendCommand()
{
    senddata.clear();
    senddata[0]=static_cast<char>(128);
    serial.write(senddata);
}

void MainWindow::testValues(){
    time.replace(index,static_cast<double>(qrand() % ((RANDOM_MAX) - RANDOM_MIN) + RANDOM_MIN)/N);
    index++;
    if(index>359){
        index = 0;
    }
    update();
    qDebug() <<"index" << index << " value:" << time.at(index);

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    chart.drawCircle(painter,centralWidget()->geometry());
    chart.drawCircleData(painter,time, index);
    qDebug() <<"test";
}




