#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QtCharts>
#include <myworker.h>
#include <QtCharts>
#include <QVector>
#include <QPointF>
#include <QPoint>
#include <QtMath>
#include <cmath>
#include <QThread>
#include <QtGlobal>
#include <QChart>
#include <QLineSeries>


using namespace QtCharts;

class calculator: QObject

{
    Q_OBJECT
public:

    explicit calculator(QObject *parent = nullptr);
    QVector<qreal> *CalculatedData;
    myWorker *worker;
    qreal Veliocity;
    qreal Momentum;
    qreal Voltage1;
    qreal Curent;
    qreal Voltage2;
    qreal Curent2;
    QChart * curentPlot;
    QPointF maxPoint;
    QPointF minPoint;
    QVector<QPointF> curentPlotValues;

    QVector<QPointF> *PowPerOmega;
    QVector<QPointF>* MomPerOmega;
    QVector<QPointF>* EffPerMom;
    QVector<QPointF> *EffPerOmega;

    QVector<QPointF>* EnginePower;
    QVector<QPointF>* EngineMomentum;
    QVector<QPointF>* EngineEfficiency1;
    QVector<QPointF>* EngineEfficiency2;
public slots:
    void calculate(qreal,qreal,qreal,qreal,qreal,qreal);
    void drawPlot(QVector<QPointF>*);
    void extremeValues(QVector<QPointF>*,qreal&,qreal&,qreal&,qreal&);



private:
    qreal xmaxVal;
    qreal ymaxVal;
    qreal xminVal;
    qreal yminVal;

    void make3d();
};

#endif // CALCULATOR_H
