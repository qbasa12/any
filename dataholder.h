#ifndef DATAHOLDER_H
#define DATAHOLDER_H

#include <QObject>
#include "myworker.h"
#include <QtCharts>
#include <iostream>
#include <QCoreApplication>
#include <QTextStream>
#include <QVector>
#include <QFile>
#include <QtGlobal>

class dataholder : public QObject
{
    Q_OBJECT
public:
    QFile *file;

    bool setData(QVector<QPointF>);
    explicit dataholder(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DATAHOLDER_H




