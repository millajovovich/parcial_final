#include "pelotas.h"
#include "planetas.h"

bool pelotas::getDestruccion() const
{
    return destruccion;
}

pelotas::pelotas()
{
    g = rand()%5+1;
    posx = rand()%550-280;
    posy = 250;
    setPos( posx, -posy );
}

void pelotas::movimiento()
{
    vy = vy - g *0.05;
    posy += vy*0.05 - g*0.05*0.05;


    if ( posy <= -240 ){
        vy = -vy;
        posy = -240;
    }

    setPos(posx, -posy);

    QList<QGraphicsItem *> colliding_items = collidingItems();  // para la colision con disparo
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(planetas) ){
            count++;
        }
    }
    if ( count >= 3 ){
        destruccion = 1;
    }
}

QRectF pelotas::boundingRect() const
{
    return QRectF(-radio/2, -radio/2, radio, radio);
}

void pelotas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(boundingRect());
}
