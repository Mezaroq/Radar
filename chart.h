#ifndef CHART_H
#define CHART_H

#include <QPainter>
#include <math.h>
#include <vector>
#include<QtMath>

#define MX      40
#define MY      40
#define LOGMAX  50
#define FS 96000

enum ChartMode {
    LinearChart,
    LogChart,
    SemiLogChart
};

class Chart
{
public:
    Chart();
    void drawLogGrid(QPainter &painter, QRect geometry);
    void drawLogData(QPainter &painter, QVector<double> &data);
    void drawSemiLogData(QPainter &painter, QVector<double> &data);
    void drawLinearGrid(QPainter &painter, QRect geometry);
    void drawLinearData(QPainter &painter, QVector<double> &data);
    void showMarkers(QPainter &painter, QVector<double> &data);
    void showTimeWindow(QPainter &painter, QVector<double> &data);
    void getMousePosition(int x, int y);
    void getLeftLimits(int x);
    void getRightLimits(int x);
    void drawCircle(QPainter &painter, QRect geometry);
    void drawCircleData(QPainter &painter, QVector<double> &data, int position);

    int gridNumX=10, gridNumY=10;
    int minValueX=0, maxValueX=100;
    int gridCircle=10;
    double limitsmin = minValueX, limitsmax = maxValueX;
    int minValueY=-100, maxValueY=100;
    int chartMode=0;
    double markerX=1, markerY=0;
    int dataSize;
    int firstX = (gw/2+gx);
    int firstY = (gh/2+gy);
    int lastX;
    int lastY;

    QColor backgroundColor=Qt::black;
    QColor gridColor=Qt::gray;
    QColor textColor=Qt::white;
    QColor plotColor=Qt::cyan;
    QColor markersColorA=Qt::red;
    QColor markersColorB=Qt::yellow;

private:
    double dx, dy, dvx, dvy, dmkx, dmky;
    int gx, gy, gw, gh, gmy;
    double logTable[LOGMAX];

};

#endif // CHART_H
