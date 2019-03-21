#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <unistd.h>
#include <chrono>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"
#include "myworker.h"
#include"ui_mainwindow.h"
#include "dataholder.h"
#include <QSerialPortInfo>
#include <QtCharts>
#include "controller.h"
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QMap>
#include <QMapNode>
#include <QMapIterator>
#include <stdlib.h>
#include <QtGlobal>
#include <QPrinter>
#include <QPrintDialog>
#include <QLayout>
#include "reader.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:

    enum type {None,PowPerOm,MomPerOm,EffPerOm,EffPerMom,TwoFirst};
    int t =0;
    myWorker *worker;
    myWorker *portWorker;
    QVector<qreal> *data;
    calculator *c;
    bool checked =false;
    bool change;
    bool printButtonState;
    int barPos;
    QString currentPortText;
    QChart *chart = new QChart();
    QChartView *view = new QChartView();
    QObject *obj;
    QObject *obj1;
    void sendDAtaByte();
    qreal size;

    void onPortAddedOrRemoved();
    void setDatatoView(QString&);
    bool on_PowerBox_checked();
    bool on_EfficiencyBoxm_checked();
    bool on_EfficiencyBoxw_checked();
    bool on_MomentumBox_checked();


    explicit MainWindow(QWidget *parent = nullptr);
     ~MainWindow();

    public slots:
            void SetPortList(qreal);
            void onNumberChanged(int);
            void SetValuesToTable(qreal,qreal,qreal,qreal);
            void setChartLayout();
            void SetComunicationState();



    private slots:

    void on_setter_button_clicked();
    void on_print_button_clicked(bool checked,QVector<qreal>);
    void on_ports_box_currentTextChanged(const QString &arg1);
    void on_ports_box_currentIndexChanged(const QString &arg1);
    void on_verticalSlider_sliderMoved(int position);
   // void startWorker();

    void on_ports_box_activated(int index);

    void on_MomentumBox_stateChanged(int arg1);

    void on_EffiencyBoxm_stateChanged(int arg1);

    void on_EfficiencyBoxw_stateChanged(int arg1);

    void on_PowerBox_stateChanged(int arg1);

    void on_print_button_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
