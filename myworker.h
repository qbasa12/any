#ifndef MYWORKER_H
#define MYWORKER_H

#include <algorithm>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "stdlib.h"
#include <QtCore>
#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QtCharts>




class myWorker: public QThread {
   Q_OBJECT
public:

    qreal xmaxVal;
    qreal ymaxVal;
    qreal xminVal;
    qreal yminVal;
    qreal size;
    bool time = false;
    QVector<QPointF> curentPlotValues;
    QTimer *timer;
    QTimer *timer1;
    QChart* curentPlot;
    int type;
    bool connection;
    bool portMode;
    quint8 Interval;
    QSerialPort* curentPort;
    QString Udata;
    explicit myWorker(QObject *parent = nullptr);
    QString curentPortName;
    void run();
    void loadData(QString,QVector<qreal>);

    void packData(QVector<qreal>*,QVector<QPointF>*,QVector<QPointF>*,QVector<QPointF>*,QVector<QPointF>*);
    void setPort(QString);
    void setPortMode();
    void setTimeMode();
    public slots:
                void onPortSignal(QSerialPort*);
                void replot();
                void read();
                void checkPortState();
                void unpackData(QVector<qreal>);
    signals:
                void portSignal(QSerialPort*);
                void dataLoaded(QVector<qreal>);
                void timeLefted();
                void numberChanged(int);
                void dataChange(QString);
                void unpackedData(qreal,qreal,qreal,qreal,qreal,qreal);
                void calculatedData(qreal,qreal,qreal,qreal);
                void PlotData(QVector<QPointF>*);
                void plotType(int);
                void newPort(qreal);
                void newView();
                void connectionState();
                void readyToRead();


};
#endif // MYWORKER_H
