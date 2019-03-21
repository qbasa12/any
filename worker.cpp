#include "worker.h"
#include <unistd.h>

worker::worker(QObject *parent): QThread (parent)
{

};
void worker::run(){
    for(int i = 0; i<100; i++){
        qDebug() << i;
        msleep(100);
        qDebug() << this->isRunning();
        //emit numberChanged(i);
    }
};
