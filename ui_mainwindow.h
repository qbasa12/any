/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QComboBox *ports_box;
    QLineEdit *curentData;
    QHBoxLayout *horizontalLayout;
    QOpenGLWidget *openGLWidget;
    QSlider *verticalSlider;
    QCheckBox *comBox;
    QCheckBox *MomentumBox;
    QCheckBox *EfficiencyBoxw;
    QCheckBox *EffiencyBoxm;
    QCheckBox *PowerBox;
    QPushButton *setter_button;
    QPushButton *print_button;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menuInstructions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(543, 621);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 0, 421, 481));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        ports_box = new QComboBox(gridLayoutWidget);
        ports_box->setObjectName(QString::fromUtf8("ports_box"));
        ports_box->setEditable(true);

        gridLayout->addWidget(ports_box, 1, 3, 1, 1);

        curentData = new QLineEdit(gridLayoutWidget);
        curentData->setObjectName(QString::fromUtf8("curentData"));

        gridLayout->addWidget(curentData, 3, 0, 1, 4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        openGLWidget = new QOpenGLWidget(gridLayoutWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setMaximumSize(QSize(500, 720));

        horizontalLayout->addWidget(openGLWidget);

        verticalSlider = new QSlider(gridLayoutWidget);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalSlider);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 4);

        comBox = new QCheckBox(gridLayoutWidget);
        comBox->setObjectName(QString::fromUtf8("comBox"));
        comBox->setEnabled(true);
        comBox->setCheckable(false);

        gridLayout->addWidget(comBox, 2, 3, 1, 1);

        MomentumBox = new QCheckBox(gridLayoutWidget);
        MomentumBox->setObjectName(QString::fromUtf8("MomentumBox"));

        gridLayout->addWidget(MomentumBox, 1, 2, 1, 1);

        EfficiencyBoxw = new QCheckBox(gridLayoutWidget);
        EfficiencyBoxw->setObjectName(QString::fromUtf8("EfficiencyBoxw"));

        gridLayout->addWidget(EfficiencyBoxw, 2, 1, 1, 1);

        EffiencyBoxm = new QCheckBox(gridLayoutWidget);
        EffiencyBoxm->setObjectName(QString::fromUtf8("EffiencyBoxm"));

        gridLayout->addWidget(EffiencyBoxm, 2, 2, 1, 1);

        PowerBox = new QCheckBox(gridLayoutWidget);
        PowerBox->setObjectName(QString::fromUtf8("PowerBox"));

        gridLayout->addWidget(PowerBox, 1, 1, 1, 1);

        setter_button = new QPushButton(gridLayoutWidget);
        setter_button->setObjectName(QString::fromUtf8("setter_button"));

        gridLayout->addWidget(setter_button, 2, 0, 1, 1);

        print_button = new QPushButton(gridLayoutWidget);
        print_button->setObjectName(QString::fromUtf8("print_button"));

        gridLayout->addWidget(print_button, 1, 0, 1, 1);

        tableWidget = new QTableWidget(gridLayoutWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 543, 21));
        menuInstructions = new QMenu(menuBar);
        menuInstructions->setObjectName(QString::fromUtf8("menuInstructions"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuInstructions->menuAction());
        menuInstructions->addSeparator();
        menuInstructions->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        comBox->setText(QApplication::translate("MainWindow", "comunication", nullptr));
        MomentumBox->setText(QApplication::translate("MainWindow", "M(w)", nullptr));
        EfficiencyBoxw->setText(QApplication::translate("MainWindow", "N(w)", nullptr));
        EffiencyBoxm->setText(QApplication::translate("MainWindow", "N(M)", nullptr));
        PowerBox->setText(QApplication::translate("MainWindow", "P(w)", nullptr));
        setter_button->setText(QApplication::translate("MainWindow", "SetData", nullptr));
        print_button->setText(QApplication::translate("MainWindow", "DataPrint", nullptr));
        menuInstructions->setTitle(QApplication::translate("MainWindow", "Instructions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
