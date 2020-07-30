#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Scene= new QGraphicsScene;
    ui->graphicsView->setScene(Scene);
    Scene->setSceneRect(-200,-200,400,400);
    Scene->addRect(Scene->sceneRect());

    //              TIEMPO
    timer= new QTimer(this);
    tiempo=1;
    timer->stop();
    connect(timer,SIGNAL(timeout()),this,SLOT(Mover()));

    //             ACTIVIDAD 1
    astros.append(new planetas(0,0,0,0,70000,300));
    astros.append(new planetas(0,7000,2,0,70,120));
    astros.append(new planetas(4000,-5000,1.6,1.2,25,100));


    /*astros.append(new planetas(0,0,0,0,50000,300));
    astros.append(new planetas(5000,0,0,-2,70,150));
    astros.append(new planetas(-5000,0,0,2,70,150));
    astros.append(new planetas(0,5000,2,0,70,150));
    astros.append(new planetas(0,-5000,-2,0,70,150));*/

    //      FOR PARA COLOCAR EN SCENA Y EN UNA LISTA
    for( int i=0; i<astros.size();i++ ){
        astros.at(i)->iteracion(tiempo);
        Scene->addItem(astros.at(i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSimular_clicked()//          PARA EMPEZAR LA SIMULACION
{
    timer->start(tiempo);
}

void MainWindow::Mover()
{
    //      FOR PARA CALCULAR LAS ACELERACIONES
    for (int i=0 ; i <astros.size();i++){
        for (int j=0; j< astros.size();j++){
            if ( i != j ){
                astros.at(i)->aceleraciones(astros.at(j)->getPosx(), astros.at(j)->getPosy(), astros.at(j)->getMasa());
            }
        }
    }

    //      FOR PARA ACTUALIZAR
    for (int i=0; i< astros.size(); i++){
        astros.at(i)->iteracion(tiempo);
    }
}
