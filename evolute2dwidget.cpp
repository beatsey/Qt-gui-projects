#include "evolute2dwidget.h"
#include <QPainter>
#include "variables.h"
Evolute2dWidget::Evolute2dWidget(QWidget *parent) : QWidget(parent){

}

void Evolute2dWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen old = painter.pen();


    if(!statusX)
        painter.drawText(30,30,"Неизвестная функция x(t)");

    if(!statusY)
        painter.drawText(30,60,"Неизвестная функция y(t)");

    if((statusX&&statusY)){
        int width = this->geometry().width()/2;
        int height = this->geometry().height()/2;

        std :: vector<QPoint> qevolvent;
        qevolvent.resize(evolventCurve.size());

        painter.setPen(QPen(Qt::red));

        // Кривая
        for(size_t q=0,n=evolventCurve.size();q<n;++q){
            Vector2 &pt=evolventCurve[q];
            qevolvent[q].setX(100*pt.x+width);
            qevolvent[q].setY(-100*pt.y+height);
        }
        painter.drawPolyline(&(qevolvent[0]), static_cast<int>(evolventCurve.size()));


        std :: vector<QPoint> qevolute;
        qevolute.resize(evoluteCurve.size());

        painter.setPen(QPen(Qt::black));

        // Эволюта
        for(size_t q=0,n=evoluteCurve.size();q<n;++q){
            Vector2 &pt=evoluteCurve[q];
            qevolute[q].setX(100*pt.x+width);
            qevolute[q].setY(-100*pt.y+height);
        }

        if(showEvolute)
            painter.drawPolyline(&(qevolute[0]), static_cast<int>(evoluteCurve.size()));

        if(showCircle){


            size_t pos=evolventCurve.size()*circlePos/100;

            // Соприкасающаяся окружность
            int radius = (evolventCurve[pos]-evoluteCurve[pos]).len()*100;
            painter.setPen(QPen(Qt::blue));
            painter.drawEllipse(
                        QRect(qevolute[pos].x()-radius,qevolute[pos].y()-radius,radius*2,radius*2));
            painter.drawEllipse(
                        QRect(qevolute[pos].x()-3,qevolute[pos].y()-3,3*2,3*2));
            painter.drawEllipse(
                        QRect(qevolvent[pos].x()-3,qevolvent[pos].y()-3,3*2,3*2));
        }

        qevolvent.clear();
        qevolute.clear();
    }

    painter.setPen(old);
    QWidget::paintEvent(event);
}
