#include "reader.h"
#include <QIODevice>
#include <unistd.h>

reader::reader(QObject* parent):QObject(parent) {

  ReadWorker = new myWorker(this);
  PackWorker = new myWorker(this);
  externalWorker = new myWorker(this);
  PackWorker->start();
  ReadWorker->start();

  ReadWorker->time = true;
  ReadWorker->setTimeMode();
  PackWorker->setTimeMode();
    QMutex m;

  connect(ReadWorker,SIGNAL(dataChange(QString)),this, SLOT(onDataChanged(QString)));
  connect(ReadWorker->timer,SIGNAL(timeout()),this,SLOT(clearData()));
  connect(externalWorker,SIGNAL(readyToRead()),ReadWorker,SLOT(read()));
  connect(externalWorker,SIGNAL(portSignal(QSerialPort*)),ReadWorker,SLOT(onPortSignal(QSerialPort*)));
    connect(externalWorker,SIGNAL(portSignal(QSerialPort*)),PackWorker,SLOT(onPortSignal(QSerialPort*)));
  connect(PackWorker,SIGNAL(dataLoaded(QVector<qreal>)),this,SLOT(onDataLoaded(QVector<qreal>)));
  connect(ReadWorker,SIGNAL(dataLoaded(QVector<qreal>)),externalWorker,SLOT(unpackData(QVector<qreal>)));

  qreal Interval = 33.3;
  QVector<qreal> data;
  bool timeLefted = false;
  bool connection = false;

};


void reader::loadData() {
    PackWorker->loadData(PackWorker->Udata,data);
      m.unlock();

};
void reader::onDataLoaded(QVector<qreal> vctr) {
 this->data = vctr;
        externalWorker->loadData(Udata,data);
};
void reader::overrideVectors() {
    QObject *obj= new QObject();


};
void reader::clearData(){
    if (this->timeLefted == true) {
      rPowPerOmega.clear();
      rMomPerOmega.clear();
      rEffPerOmega.clear();
      rEffPerMom.clear();
      data.clear();
      Udata.clear();
    };

}
void reader::onDataChanged(QString s){
    Udata =s;
    qDebug()<< Udata;
    qDebug()<< "Udata";

    qDebug()<< s;
    PackWorker->Udata = s;

    m.lock();
    loadData();

    s.clear();
}


