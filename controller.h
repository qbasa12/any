#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "myworker.h"
#include <QtCharts>
#include <QSerialPort>
#include <QTextDocumentWriter>
#include <QFile>
#include <QPointF>
#include <QtGlobal>
using namespace QtCharts;

class controller: public QObject {

            Q_OBJECT
public:

    bool setData(QSerialPort*,QVector<qreal>);
    controller(QObject *parent = nullptr);
};


#endif // CONTROLLER_H
