#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int t = type(None);
    QObject *obj = new QObject();
    QObject *obj1 = new QObject();
    worker = new myWorker(obj);
    portWorker = new myWorker(obj);
    portWorker->setPortMode();
    worker->setTimeMode();

    connect(worker,SIGNAL(numberChanged(int)),this,SLOT(onNumberChanged(int)));

    connect(worker,SIGNAL(calculatedData(qreal,qreal,qreal,qreal)),this,SLOT(SetValuesToTable(qreal,qreal,qreal,qreal)));
    connect(portWorker,SIGNAL(newPort(qreal)),this,SLOT(SetPortList(qreal)));
    connect(worker,SIGNAL(newView()),this,SLOT(setChartLayout()));
    connect(worker,SIGNAL(connectionState()),this,SLOT(SetComunicationState()));

    worker->start();
    portWorker->start();
    size =0;
    qDebug() <<"size" <<size;
    ui->setupUi(this);
    bool change = false;

    if(!(worker->isRunning())) worker->run();
    if(!(portWorker->isRunning())) portWorker->run();
    usleep(100000);
    qDebug() <<"portWorker" <<portWorker->isRunning();
    qDebug() <<"worker" <<worker->isRunning();
    SetValuesToTable(0,0,0,0);

    QVector<qreal>* data = new QVector<qreal>();
    QString currentPortText;
    int barPos;

}

MainWindow::~MainWindow()
{


    delete ui;
}
void MainWindow::SetComunicationState(){
    ui->comBox->setCheckable(1);
    ui->comBox->setEnabled(1);
    ui->comBox->setChecked(1);


    ui->comBox->setCheckState(Qt::Checked);
};
void MainWindow::setDatatoView(QString &d){
    ui->curentData->setText(d);
};
bool MainWindow::on_PowerBox_checked(){return MainWindow::ui->PowerBox->QAbstractButton::isChecked();};
bool MainWindow::on_EfficiencyBoxw_checked(){return MainWindow::ui->EfficiencyBoxw->QAbstractButton::isChecked();}
bool MainWindow::on_EfficiencyBoxm_checked(){return MainWindow::ui->EffiencyBoxm->QAbstractButton::isChecked();}
bool MainWindow::on_MomentumBox_checked(){return MainWindow::ui->MomentumBox->QAbstractButton::isChecked();};
void MainWindow::SetValuesToTable(qreal q1, qreal q2, qreal q3, qreal q4){
    qDebug() << "value";

        ui->tableWidget->setRowCount(4);
        ui->tableWidget->setColumnCount(2);
        ui->tableWidget->setStyleSheet("QTableView {selection-background-color: grey;}");

        std::string s1;
        std::string s2;
        std::string s3;
        std::string s4;

        s1 = std::to_string(q1);
        s2 = std::to_string(q2);
        s3 = std::to_string(q3);
        s4 = std::to_string(q4);

        QString qs1 = QString::fromLocal8Bit(s1.c_str());
        QString qs2 = QString::fromLocal8Bit(s2.c_str());
        QString qs3 = QString::fromLocal8Bit(s3.c_str());
        QString qs4 = QString::fromLocal8Bit(s4.c_str());


        QTableWidgetItem *item1 = new QTableWidgetItem("EnginePower");
        QTableWidgetItem *item2 = new QTableWidgetItem("Efficiency");
        QTableWidgetItem *item3 = new QTableWidgetItem("BreakingPower");
        QTableWidgetItem *item4 = new QTableWidgetItem("WastedPower");
        QTableWidgetItem *item5 = new QTableWidgetItem(qs1);
        QTableWidgetItem *item6 = new QTableWidgetItem(qs2);
        QTableWidgetItem *item7 = new QTableWidgetItem(qs3);
        QTableWidgetItem *item8 = new QTableWidgetItem(qs4);


        ui->tableWidget->setItem(0,0,item1);
        ui->tableWidget->setItem(1,0,item2);
        ui->tableWidget->setItem(2,0,item3);
        ui->tableWidget->setItem(3,0,item4);
        ui->tableWidget->setItem(0,1,item5);
        ui->tableWidget->setItem(1,1,item6);
        ui->tableWidget->setItem(2,1,item7);
        ui->tableWidget->setItem(3,1,item8);

};
void MainWindow::SetPortList(qreal s){
    int i = -1 ;
    qDebug() <<"size mainwindow";

            if(s != this->size){
                if(s > this->size){
                      for (QSerialPortInfo info : QSerialPortInfo::availablePorts()){
                            portWorker->setPort(ui->ports_box->currentText());
                            ui->ports_box->addItem(info.portName());
                                if(i != this->ui->ports_box->currentIndex())ui->ports_box->setCurrentIndex(i);
                                else {
                                    i +=this->ui->ports_box->currentIndex();
                                }
                            ui->ports_box->blockSignals(false);
                            i++;
                            qDebug() <<"portlist is changng";
                            this->size = s;
                        }
                }else {
                    ui->ports_box->clear();
                    this->size = s;
                    i=-1;
                }
    }
};
void MainWindow::setChartLayout(){

    if(0 !=0){
       ui->openGLWidget->layout()->addWidget(this->view);
       ui->openGLWidget->doneCurrent();
    }
    qDebug() <<"view";
}
void MainWindow::on_setter_button_clicked(){
worker->start();
sleep(1);
}
void MainWindow::on_print_button_clicked(bool checked,QVector<qreal> vctr)
{

}
void MainWindow::on_ports_box_currentTextChanged(const QString &arg1){
   // ui->ports_box->setCurrentText(arg1);
    
    this->change = true;
}
void MainWindow::on_ports_box_currentIndexChanged(const QString &arg1)
{

    //ui->ports_box->setCurrentText(arg1);
    this->change = true;

}


void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    bool cstate = false;
    qreal startPosition = 0;
    std::string s;
    int x = ui->openGLWidget->x();
    int y = ui->openGLWidget->y();
    const QRectF r1(x,y,50,72);
    s = std::to_string(ui->verticalSlider->value());
    QString qs = QString::fromUtf8(s.c_str());
    ui->curentData->setText(qs);
    ui->verticalSlider->setTickInterval(10);
    if(position > startPosition){
        position = ui->verticalSlider->value();
        chart->zoomIn(r1);
        cstate = this->chart->isZoomed();
        if(cstate){
            position = ui->verticalSlider->value();
            }
    }else {
        position = ui->verticalSlider->value();
        chart->zoomOut();
        cstate = this->chart->isZoomed();
    };
    ui->openGLWidget->setSizeIncrement(ui->verticalSlider->value(),ui->openGLWidget->maximumHeight());
}
void MainWindow::on_ports_box_activated(int index){
    qDebug() <<this->thread();
    qDebug() <<".....................................................................................";
   //if((this->thread())!=(worker->thread())){
    usleep(500000);
    worker->setPort(ui->ports_box->itemText(ui->ports_box->currentIndex()));
    worker->curentPortName = ui->ports_box->itemText(ui->ports_box->currentIndex());
    //}//else {
//worker->run();
//worker->moveToThread(worker->thread());
//}

};
void MainWindow::on_MomentumBox_stateChanged(int arg1){  
    this->t = type(MomPerOm); 
    worker->type = type(MomPerOm);
    usleep(1000);
    if(c->curentPlotValues.size() != 0){
        chart = worker->curentPlot;
        view->setChart(chart);
    }
    
}

void MainWindow::on_EffiencyBoxm_stateChanged(int arg1)
{   
     this->t = type(EffPerMom);
     worker->type = type(MomPerOm);
     usleep(1000);
     if(c->curentPlotValues.size() != 0){
         chart = worker->curentPlot;
         view->setChart(chart);
    }
     checked = true;
}

void MainWindow::on_EfficiencyBoxw_stateChanged(int arg1)
{    
    this->t = type(EffPerOm);
    worker->type = type(MomPerOm);
    usleep(1000);
    if(c->curentPlotValues.size() != 0){
        chart = worker->curentPlot;

    }
     checked = true;
}

void MainWindow::on_PowerBox_stateChanged(int arg1)
{    
    this->t = type(PowPerOm);
    worker->type = type(PowPerOm);
    usleep(1000);
    if(c->curentPlotValues.size() != 0){
        chart = worker->curentPlot;
    }
     checked = true;

}


void MainWindow::on_print_button_clicked()
{
    if(checked){
        QVector<QPointF> vctr =c->curentPlotValues;
        dataholder *dh = new dataholder();
            if(dh->setData(vctr)){
                QPrinter *printer = new QPrinter();
                printer->setOrientation(QPrinter::Landscape);
                printer->setOutputFormat(QPrinter::PdfFormat);
                QPrintDialog *dialog = new QPrintDialog(printer);
                QPainter *painter = new QPainter();
                painter->begin(printer);
                ui->openGLWidget->render(painter);
                painter->end();
            };
    };

}
void MainWindow::onNumberChanged(int a){

        ui->curentData->setEnabled(true);
        ui->curentData->setText(QString::number(a));
};



