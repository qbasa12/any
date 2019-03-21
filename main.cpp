#include "mainwindow.h"
#include "reader.h"
#include <unistd.h>
#include "worker.h"
#include "calculator.h"
#include "dataholder.h"
#include "controller.h"
#include "myworker.h"
#include <QThread>
#include <QApplication>
#include <QMutex>
#include <QObject>
#include <QOpenGLWidget>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QVector<qreal> sessionData;
    QVector<qreal> sPackedData;
    
    QVector<QPointF> *sPowPerOmega = new QVector<QPointF>();
    QVector<QPointF> *sMomperOmega = new QVector<QPointF>;
    QVector<QPointF> *sEffPerOmega = new QVector<QPointF>;
    QVector<QPointF> *sEffPerMom = new QVector<QPointF>;
    qreal sEnginePower;
    qreal sEfficiency;
    qreal sBreakingPower;
    qreal sWastedPower;
    QPointF maxPoint;
    QPointF minPoint;
    QString portName;

    bool timer;

    portName = w.portWorker->curentPort->Text;

    QObject *obj = new QObject();
    QSerialPort *sessionPort;
    calculator *mcalculator = new calculator(obj);
    reader *r = new reader();

        while((!mcalculator->worker->isRunning()))
         {
             mcalculator->worker->start();
         };


    sessionPort = w.worker->curentPort;

    myWorker* p ;
    //p = ;
    w.worker = mcalculator->worker;
    r->externalWorker = w.worker;
    sessionPort =  w.worker->curentPort;
    r->externalWorker->curentPort =sessionPort;
    qDebug()<< portName;


    //w.c = mcalculator;

        qDebug() << sessionPort;


 r->externalWorker->curentPort = w.worker->curentPort;
   return a.exec();

}

