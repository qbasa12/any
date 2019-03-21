#include "controller.h"


//Serial Communication properties: Baud9600, Parity_none, Stop_bits_1, Data_8bits, Flow_control_Off
controller::controller(QObject* parent):QObject(parent)
{
    QObject *obj= new QObject();
    //worker = new myWorker(obj);
}
bool controller::setData(QSerialPort *port, QVector<qreal> dvctr){


    port->setBaudRate(9600);
    port->setDataBits(QSerialPort::Data8);
    port->setStopBits(QSerialPort::OneStop);
    port->setParity(QSerialPort::NoParity);

       bool responsibility = false;
       responsibility = port->open(QIODevice::WriteOnly | QIODevice::Unbuffered);
       if(responsibility){
            for(qreal& data : dvctr){
               char d = data;
               const char* p;
               p = &d;
               port->write(p,sizeof (char));
           };
       };
       return responsibility;
};

