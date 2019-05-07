#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPainter>
#include "thread.h"
#include "chart.h"
#include <QTimer>

#define DSIZE    2
#define DSIZE2   (DSIZE/2)
#define N        360
#define RANDOM_MIN 100
#define RANDOM_MAX 360



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void externalThread_tick();
    void sendCommand();
    void testValues();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);

    Thread thread;
    QSerialPort serial;
    QByteArray senddata;
    QByteArray readdata;
    QVector<double> time;
    QVector<double> buffer;
    Chart chart;
    double full_angle;
    int n = N-1, index = 0;
    QTimer *timer;
};

#endif // MAINWINDOW_H
