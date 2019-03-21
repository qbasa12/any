#include "myworker.h"




myWorker::myWorker(QObject *parent): QThread (parent)
{    qreal xmaxVal = 0;
     qreal ymaxVal = 0;
     qreal xminVal = 0;
     qreal yminVal = 0;
     int type = 0;
     timer = new QTimer(this);
     timer1 = new QTimer(this);
     this->curentPort = nullptr;
     timer->start(this->Interval);
     curentPort = new QSerialPort();
        qDebug() << this->time;
        qDebug() << this->timer1->isActive();

};
void myWorker::read(){
    
    QString d;
    QTextStream inStream;

    if((this->curentPort != nullptr) && (curentPort->isOpen()) && (curentPort->isReadable()) ){
         while(this->timer->isActive()) {
            if((curentPort != nullptr) && (curentPort->isOpen())){
                this->connection = true;
                qDebug() << "inStream.readLine";
                curentPort->waitForReadyRead(300000);
                QTextStream inStream(curentPort);
                inStream >> (d);
                emit dataChange(d);
                //qDebug() << "inStream.readLine";
                qDebug() << d;
                qDebug() <<"name" <<this->parent();
                // qDebug() <<"name" <<this->metaObject()->constructor();
                //usleep(1000000);
                emit dataChange(d);
                Udata = d;

                qDebug() << thread()->currentThread();


             }
             else {
                qDebug() << "data is not reading";
                qDebug() << "curentPort->bytesAvailable();" << curentPort->bytesAvailable();
                qDebug() << "curentPort->isOpen();" << curentPort->isOpen();
                if(!curentPort->isOpen())curentPort->open(QSerialPort::ReadOnly);

            }

        }
        this->timer->setInterval(this->Interval);
        qDebug() << this->curentPort->isReadable();

        msleep(500);
    }else {
        if(!curentPort->isOpen() )curentPort->open(QSerialPort::ReadOnly);

        qDebug() << "there is no port";
        if(this->portMode != true)setPort(curentPortName);
        }

}
void myWorker::setTimeMode(){

       qDebug() << this->time;
       if(time ==true){connect(timer,SIGNAL(timeout()),this,SLOT(read()));}
       connect(timer,SIGNAL(timeout()),this,SLOT(replot()));
}
void myWorker::setPortMode(){
        qDebug() << "portMode"<< this->portMode;
        connect(timer1,SIGNAL(timeout()),this,SLOT(checkPortState()));
        timer1->start(500);

}
void myWorker::run(){
    msleep(500);
    QMutex m;
    m.lock();
    for(int i =0; i<100 ; i++){
        msleep(100);
        emit numberChanged(i);
    }
    m.unlock();
    qDebug() << "isRunning"<<this->isRunning();
};
void myWorker::checkPortState(){
    qDebug() <<size;
       if(QSerialPortInfo::availablePorts().size() != this->size) {
            size =  QSerialPortInfo::availablePorts().size();
            qDebug() << "size" <<size;
            emit newPort(size);
       }
      this->timer1->start(500);
}
void myWorker::setPort(QString portName) {
    if(portName.size()!=0){
        curentPortName = portName;
        QObject *obj = new QObject();
        QSerialPort *port = new QSerialPort(portName, obj);
        port->setPortName(portName);
        port->open(QSerialPort::ReadOnly);
        port->setBaudRate(9600);
        port->setDataBits(QSerialPort::DataBits());
        port->setStopBits(QSerialPort::OneStop);
        port->setParity(QSerialPort::Parity());
        port->setFlowControl(QSerialPort::NoFlowControl);
        curentPort = port;
            //if(port->isReadable()){this->timer->setInterval(this->Interval);
            emit connectionState();//}
                qDebug() <<"port->isDataTerminalReady();"<< port->isDataTerminalReady();
                qDebug() << "port->isOpen();"<<port->isOpen();
                qDebug() << "port->isReadable();"<<port->isReadable();
                    if(port->isDataTerminalReady() && port->isOpen()&& port->isReadable())
                        emit readyToRead();
                        emit portSignal(port);
                        //read();
    }
};
void  myWorker::loadData(QString dataQString,QVector<qreal> vctr){
    
    std::string dataString =  dataQString.toStdString();
    std::string clearedDataString;
        if((dataString.size() != 0) && (this->curentPort != nullptr)){
            const auto pos = dataString.find("DATA");
            std::copy_if(dataString.begin()+pos,dataString.end(),clearedDataString.begin(),[dataString,pos](char l = ';',int i =0 )
                {   i++;
                    if(dataString.at(pos+i) != l)
                    return true;});

                    for(char c : clearedDataString){
                        int i =0;
                        int k = 0;
                        std::string s =clearedDataString.erase(i,sizeof (qreal));
                        i +=8;
                        qreal p = atof(s.c_str());
                        vctr.insert(k,p);
                        k++;
                    }
                emit dataLoaded(vctr);
                qDebug() << "thereis  dataString";
        }
        else {
            qDebug() << "thereis no dataString yet";
    }
};
void myWorker::unpackData(QVector<qreal> Data){

    qreal  omega;
    qreal  momentum;
    qreal  Voltage1;
    qreal  Curent1;
    qreal  Voltage2;
    qreal  Curent2;
    if(Data.size()!=0){
        int s = Data.size();
        int n =0;
            for(int i = 0;i < s;i++){
                switch(n){
                    case 0 : { omega = Data.at(i);};
                    case 1 :  { momentum = Data.at(i);}
                    case 2 : { Voltage1 = Data.at(i);}
                    case 3 :   {Curent1 = Data.at(i);}
                    case 4 :   {Voltage2 = Data.at(i);}
                    case 5 :  {Curent2 = Data.at(i);}
                    }
                    if(i==5){
                        emit unpackedData(omega,momentum,Voltage1,Curent1,Voltage2,Curent2);
                        n=0;
                    }else{
                        n++;
                    }
       }
    }else{
        qDebug() << "no data";
    }
};
void myWorker::replot(){
     if((curentPlot != nullptr) && (Udata.size() != 0)){
        QChart* plot = this->curentPlot;
        QValueAxis *x = new QValueAxis();
        x->setMax(this->xmaxVal);
        x->setMin(this->xminVal);
        x->setTickCount(100);
        x->applyNiceNumbers();

        QValueAxis *y = new QValueAxis;
        y->setMax(this->ymaxVal);
        y->setMin(this->yminVal);
        y->setTickCount(100);
        y->applyNiceNumbers();

        plot->setTitle("STATE");
        plot->setTheme(QChart::ChartThemeDark);
        plot->addAxis(x,Qt::AlignBottom);
        plot->addAxis(y,Qt::AlignLeft);

        QLineSeries *series = new QLineSeries();
        plot->removeAllSeries();
        if(curentPlotValues.size() != 0){
            for(QPointF p : this->curentPlotValues){
                series->append(p.x(),p.y());
             };

        plot->addSeries(series);
        };
        series->attachAxis(x);
        series->attachAxis(y);
        qDebug() << "is reploting";
    }
};
void myWorker::onPortSignal(QSerialPort*p){
    this->curentPort = p;
}
void myWorker::packData(QVector<qreal> *vctr,QVector<QPointF> *powPerOm,QVector<QPointF>* momPerOm,QVector<QPointF>* effPerMom,QVector<QPointF> *effPerVel){
   int d = 0;
   int n = 0;
    QVector<qreal> V;
     QVector<qreal> *p = &V;
     p = vctr;


        for(int i = 0; i< V.size(); ++i){
                   QPointF *p = new QPointF();
                   QPointF *p1 = new QPointF();
                   QPointF *p2 = new QPointF();
                   QPointF *p3 = new QPointF();
                   switch(n){
                        case 0 : { 
                                    p->rx() = vctr->at(i);
                                    p1->rx() = vctr->at(i);
                                    p3->rx() = vctr->at(i);
                                    } //veliocity
                        case 1 : {
                                    p->ry() = vctr->at(i);
                                    } //power
                        case 2 : {
                                    p2->rx() = vctr->at(i);
                                    p1->ry() = vctr->at(i);
                                    } //momentum
                        case 3 :{ 
                                    p2->ry() = vctr->at(i);
                                    p3->ry() = vctr->at(i);
                                    n=0;
                                    
                                    powPerOm->insert(d,*p);
                                    momPerOm->insert(d,*p1);
                                    effPerMom->insert(d,*p2);
                                    effPerVel->insert(d,*p3);
                                    d++;
                                    } //efficiecy
                       if(i==3){

                           ///
                           emit calculatedData(p1->x(),p1->y(),p2->y(),p->y());
                           n=0;
                       }else{
                           n++;
                       }
                   }
                }
                      
        switch (this->type) {
             case 0: break;
             case 1 : emit PlotData(powPerOm);
             case 2 : emit PlotData(momPerOm);
             case 3 : emit PlotData(effPerMom);
             case 4 : emit PlotData(effPerVel);
             //case 5 : 
        
        } 

};
