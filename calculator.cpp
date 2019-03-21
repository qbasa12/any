#include "calculator.h"


qreal pi = M_PI;
calculator::calculator(QObject* parent):QObject(parent){

    Veliocity = 0.0;
    Momentum = 0.0;
    Voltage1 = 0.0;
    Curent = 0.0;
    Voltage2 = 0.0;
    Curent2 = 0.0;
    worker = new myWorker(this);

    connect(worker,SIGNAL(PlotData(QVector<QPointF>*)),this,SLOT(drawPlot(QVector<QPointF>*)));
    connect(worker,SIGNAL(unpackedData(qreal,qreal,qreal,qreal,qreal,qreal)),this,SLOT(calculate(qreal,qreal,qreal,qreal,qreal,qreal)));

    xmaxVal = 0;
    ymaxVal = 0;
    xminVal = 0;
    yminVal = 0;
    QVector<qreal> data;

    QVector<QPointF>* PowPerOmega = new QVector<QPointF>();
    QVector<QPointF>* MomPerOmega = new QVector<QPointF>();
    QVector<QPointF>* EffPerMom = new QVector<QPointF>();
    QVector<QPointF>* EffPerOmega = new QVector<QPointF>();
    QVector<qreal> *CalculatedData = new QVector<qreal>;
    QVector<QPointF> *p = &curentPlotValues;

   // if(!(worker->isRunning())) worker->run();

    QChart * curentPlot = new QChart();
    EnginePower = new QVector<QPointF>();
    EngineMomentum = new QVector<QPointF>();
    EngineEfficiency1 = new QVector<QPointF>();
    EngineEfficiency2 = new QVector<QPointF>();
    extremeValues(p,xmaxVal,ymaxVal,xminVal,yminVal);
};

void calculator::extremeValues(QVector<QPointF> *vector,qreal& xminVal,qreal& xmaxVal,qreal& yminVal,qreal& ymaxVal){

        qreal  xcurrentValue;
        qreal  ycurrentValue;

        for(int i = 0; i< vector->size(); ++i){
            xcurrentValue = vector->at(0).x();
            if(xcurrentValue <= vector->at(i).x() ){
                xmaxVal = vector->at(i).x();
            }else{
                xminVal = vector->at(0).x();
                };
            if(xcurrentValue >= vector->at(i).x() ){
                xminVal = vector->at(i).x();
            }else{
                xminVal = vector->at(0).x();
                };
            };

        for(int i = 0; i< vector->size(); ++i){
            ycurrentValue = vector->at(0).y();
            if(ycurrentValue <= vector->at(i).y() ){
                ymaxVal = vector->at(i).y();
            }else{
                yminVal = vector->at(0).y();
                };
            if(ycurrentValue >= vector->at(i).y() ){
                yminVal = vector->at(i).y();
            }else{
                yminVal = vector->at(0).y();
            };
        };
};
void calculator::calculate(qreal v,qreal m,qreal v1,qreal c1,qreal v2,qreal c2){

    qreal PowerIncoming = v1*c1;
    qreal PowerOutcoming = m*v*pi;
    qreal efficiency =  PowerOutcoming/PowerIncoming;
    qreal enginePower = m*v*2*pi;
    qreal breakingPower = v2*c2;
    qreal wastedPower= v1*c1;
    while(worker->timer->isActive()){
        for (int i = 0 ;i< 4;++i) {
            switch (i) {
                 case 0: {this->CalculatedData->insert(i,v);};
                 case 1: {this->CalculatedData->insert(i,PowerIncoming);};
                 case 2: {this->CalculatedData->insert(i,m);};
                 case 3: {this->CalculatedData->insert(i,efficiency);
                            i=0;
                                if(!worker->timer->isActive()){
                                    CalculatedData->clear();
                                    break;
                                    }
                         }
            }
        }
    }
   worker->packData(CalculatedData,PowPerOmega,MomPerOmega,EffPerOmega,EffPerMom);
}

void calculator::drawPlot(QVector<QPointF>* data) {

        qreal xmax =100.0;
        qreal ymax =100.0;
        qreal xmin =0.0;
        qreal ymin =0.0;

        QValueAxis *x = new QValueAxis();
        x->setMax(xmax);
        x->setMin(xmin);
        x->setTickCount(100);
        x->applyNiceNumbers();


        QValueAxis *y = new QValueAxis;
        y->setMax(ymax);
        y->setMin(ymin);
        y->setTickCount(100);
        y->applyNiceNumbers();

        QChart *plot = new QChart();
        plot->setTitle("STATE");
        plot->setTheme(QChart::ChartThemeDark);
        plot->addAxis(x,Qt::AlignBottom);
        plot->addAxis(y,Qt::AlignLeft);
        //plot.setAxisScale( QwtPlot::yLeft, 0.0, maxPosition);

        QLineSeries *series = new QLineSeries();

        for(int i =0; i<data->size(); i++){
            series->append(data->at(i).x(),data->at(i).y());
        };

        plot->addSeries(series);
        this->worker->curentPlot = plot;
        this->curentPlot = plot;
};

