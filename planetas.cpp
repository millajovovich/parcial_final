#include "planetas.h"
#include "pelotas.h"

planetas::~planetas()
{   }

planetas::planetas(double x, double y, double _vx, double _vy, double _masa, double _radio): escala(0.045)
{
    color = rand()%5;
    posx = x;
    posy = y;
    vx = _vx;
    vy = _vy;
    masa = _masa;
    radio = _radio;
}

double planetas::getPosx() const
{
    return posx;
}

double planetas::getPosy() const
{
    return posy;
}

double planetas::getMasa() const
{
    return masa;
}

void planetas::aceleraciones(double posx2, double posy2, double masa2)//    SUMA LAS ACELERACIONES CON LOS DEMAS CUERPOS
{
    angulo= atan2((posy2-posy), (posx2-posx));
    dist = pow(posx2-posx,2) + pow(posy2-posy,2);
    Ax += (((G*masa2)/dist) * cos(angulo));
    Ay += (((G*masa2)/dist) * sin(angulo));

}

void planetas::iteracion(double tiempo)     //      PARA ACTUALIZAR LAS POSICIONES Y REINICIAR ACELERACIONES
{
    vx = vx + Ax*tiempo;
    vy = vy + Ay*tiempo;
    posx = posx + vx*tiempo + (Ax*tiempo*tiempo)/2;
    posy = posy + vy*tiempo + (Ay*tiempo*tiempo)/2;
    Ax=0;
    Ay=0;

    QList<QGraphicsItem *> colliding_items = collidingItems();  // para la colision con disparo
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(pelotas) ){
            color = rand()%5;
        }
    }

    setPos( posx*escala, posy*escala );
}

QRectF planetas::boundingRect() const
{
    return QRectF(-1*escala*radio,-1*escala*radio,2*escala*radio,2*escala*radio);
}

void planetas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if ( color == 0){
        painter->setBrush(Qt::yellow);
        painter->drawEllipse(boundingRect());
    }
    else if ( color == 1 ){
        painter->setBrush(Qt::black);
        painter->drawEllipse(boundingRect());
    }
    else if ( color == 2 ){
        painter->setBrush(Qt::blue);
        painter->drawEllipse(boundingRect());
    }
    else if ( color == 3 ){
        painter->setBrush(Qt::red);
        painter->drawEllipse(boundingRect());
    }
    else if ( color == 4 ){
        painter->setBrush(Qt::green);
        painter->drawEllipse(boundingRect());
    }
}
