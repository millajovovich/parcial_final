#ifndef PELOTAS_H
#define PELOTAS_H

#include <QGraphicsItem>
#include "stdio.h"

class pelotas: public QGraphicsItem
{
    int radio = 30;
    int count = 0;

    double posx;
    double posy;

    double g;
    double vx = 0;
    double vy = 0;

    bool destruccion = 0;

public:
    pelotas();
    void movimiento();

    bool getDestruccion() const;

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // PELOTAS_H
