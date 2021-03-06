#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Scene= new QGraphicsScene;
    ui->graphicsView->setScene(Scene);
    Scene->setSceneRect(-300,-250,600,500);
    Scene->addRect(Scene->sceneRect());

    //              TIEMPO
    timer= new QTimer(this);
    tiempo=1;
    timer->stop();
    connect(timer,SIGNAL(timeout()),this,SLOT(Mover()));

    //   CREACION DE LOS PLANETAS
    astros.append(new planetas(0    ,0    ,0  ,0  ,50000,200));
    astros.append(new planetas(5000 ,0    ,0  ,-2 ,70   ,70));
    astros.append(new planetas(-5000,0    ,0  ,2  ,70   ,70));
    astros.append(new planetas(0    ,5000 ,2  ,0  ,70   ,70));
    astros.append(new planetas(0    ,-5000,-2 ,0  ,70   ,70));

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



void MainWindow::Mover()
{
    // FOR MOVIMIENTO BOLAS
    for ( int i = 0; i< bolas.size(); i++ ){
        bolas.at(i)->movimiento();
    }
    //      FOR PARA CALCULAR LAS ACELERACIONES
    for (int i=0 ; i <astros.size();i++){
        for (int j=0; j< astros.size();j++){
            if ( i != j ){
                astros.at(i)->aceleraciones(astros.at(j)->getPosx(), astros.at(j)->getPosy(), astros.at(j)->getMasa());
            }
        }
    }
    // FOR ELIMINACION DE LAS BOLAS
    for ( int i = 0; i< bolas.size(); i++ ){
        if ( bolas.at(i)->getDestruccion() == true ){
            Scene->removeItem( bolas.at(i) );
            delete bolas.at(i);
            bolas.removeOne(bolas.at(i));
        }
    }


    //      FOR PARA ACTUALIZAR
    for (int i=0; i< astros.size(); i++){
        astros.at(i)->iteracion(tiempo);
        Scene->removeItem( astros.at(i) );
        Scene->addItem(astros.at(i));
    }
}

void MainWindow::on_btnSimular_clicked()//          PARA EMPEZAR LA SIMULACION
{
    timer->start(tiempo);
}

void MainWindow::on_poner_clicked()
{
    bolas.push_back( new pelotas );
    Scene->addItem( bolas.back() );
}
