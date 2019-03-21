#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QSerialPort>
#include <QThread>
#include "reader.h"
#include "calculator.h"
#include "mainwindow.h"
#include "dataholder.h"

class worker: public QThread {
   Q_OBJECT
public:
    explicit worker(QObject *parent =nullptr);
    void run();

public slots:



               // QSerialPort *port;
               // void process(QSerialPort*,QVector<qreal>,reader*);
               // void windowProcess(qreal q1, qreal q2, qreal q3, qreal q4);
signals:
                void readedData();
                void numberChanged(int);

};
#endif // WORKER_H
