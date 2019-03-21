#include "dataholder.h"


dataholder::dataholder(QObject* parent):QObject(parent)
{
    QObject *obj= new QObject();

};
bool dataholder::setData(QVector<QPointF> vector){


    QString path= "/home/yesys/Desktop/something.txt";

    file->setFileName(path);
    file->open(QIODevice::WriteOnly);
    qDebug() << file->isOpen();
    if(file->isOpen()){
        for(int i =0; i< vector.size();++i){
            QTextStream out(file);
            out << vector.at(i).x();
            out << vector.at(i).y();
            };
            return true;
     }else{
            return false;
    };
};
