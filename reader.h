

#ifndef READER_H
#define READER_H

#include <QtCharts>
#include <QtGlobal>
#include <QString>
#include "myworker.h"
#include <QTimer>
#include <QVector>
#include <QPointF>
#include <QTypeInfo>
#include <QTextStream>
#include <QSerialPort>
#include <iostream>

class reader: public QObject {

    Q_OBJECT
public:
    explicit reader(QObject *parent = nullptr);
    QObject *obj;
    myWorker *ReadWorker;
    myWorker *PackWorker;
    myWorker *externalWorker;
    QSerialPort* curentport;
    QVector<qreal> data;
    QVector<QPointF> rPowPerOmega;
    QVector<QPointF> rMomPerOmega;
    QVector<QPointF> rEffPerOmega;
    QVector<QPointF> rEffPerMom;
    QString controlString;
    QString Udata;
      QMutex m;


    void setPort(QString);
    void loadData();
    bool ptimelefted;
    bool connection;

    public slots:
    void onDataLoaded(QVector<qreal>);
    void onDataChanged(QString s);
    void clearData();

    //signals:
private:


    void overrideVectors();
    void setTimer();
    enum type{};
    qreal Interval;
    bool timeLefted;

};


#endif // READER_H
