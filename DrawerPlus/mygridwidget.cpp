#include "mygridwidget.h"

myGridWidget::myGridWidget(QWidget *parent) : QWidget(parent),
    drawLines(false)
{

}
void myGridWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    // Сетка для кнопки с решёткой
    if(drawLines){
        painter.setPen(QPen(Qt::black,1,Qt::DashLine,Qt::RoundCap));

        painter.drawLine(width()/5+10,0,width()/5+10,height());
        painter.drawLine(4*width()/5-10,0,4*width()/5-10,height());

        painter.drawLine(0,45,width(),45);
        painter.drawLine(0,height()-55,width(),height()-55);
    }

    QWidget::paintEvent(event);
}
