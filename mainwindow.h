#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <planetas.h>
#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnSimular_clicked();
    void Mover();                           // ACTUALIZAR

private:
    Ui::MainWindow *ui;
    QGraphicsScene *Scene;
    QTimer *timer;
    planetas *cuerpo;
    double tiempo;
    QList <planetas*> astros;

};

#endif // MAINWINDOW_H
