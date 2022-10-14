#include "figure.h"
#include <time.h>
#include <stdlib.h>
#include <QtMath>

figure::figure(int type):type(type),isSelected(false)
{
    // Случайно определяем параметры
    srand (time(NULL));
    AX = rand() % (h/3);
    AR = rand() % (h/3);
    BX = rand() % (h/3);
    BR = rand() % (h/3);
    CX = rand() % (h/3);
    CR = rand() % (h/3);
    DX = rand() % (h/3);
    DR = rand() % (h/3);

    FQ = rand() % (w/4);
    FP = rand() % (w/4);
    EQ = rand() % (w/4);
    EP = rand() % (w/4);

    // По умолчанию поворот против часовой стрелки
    Angle = rand() % 181-180;

    calculatePolygon();
}

void figure::setCenter(int x, int y, int width, int height) {
    // Смотрим на границы полигона, чтобы он не вышел за границы
    centerOfTheFigure.setX(x);
    centerOfTheFigure.setY(y);

    calculateTransformedPolygon();

    QRect boundaries=rotatedPolygon.boundingRect();
    bool needRecalculation=false;
    if (boundaries.y()<0){
        needRecalculation=true;
        centerOfTheFigure.ry()+=-boundaries.y();
    }
    else if (boundaries.bottom()>height){
        needRecalculation=true;
        centerOfTheFigure.ry()-=(boundaries.bottom()-height);
    }

    if (boundaries.x()<0){
        needRecalculation=true;
        centerOfTheFigure.rx()+=-boundaries.x();
    }
    else if (boundaries.right()>width){
        needRecalculation=true;
        centerOfTheFigure.rx()-=(boundaries.right()-width);
    }

    calculateTransformedPolygon();
}

void figure::calculatePolygon() {
    polygon.clear();

    // Фигура 22
    if(type==22) {
        // Окружность AR
        for (int j=180;j<=270;j+=5) {
            int x=w+AR*cos(j*M_PI/180);
            int y=-AR*sin(j*M_PI/180);
            polygon.putPoints(polygon.size(),1,x,y);
        }

        // Окружность BR
        for (int j=0;j>=-90;j-=5) {
            int x=w-BR+BR*cos(j*M_PI/180);
            int y=h-BR-BR*sin(j*M_PI/180);
            polygon.putPoints(polygon.size(),1,x,y);
        }

        // Эллипс FQ
        for (int j=0;j<=180;j+=5) {
            int x=(w-FQ*cos(j*M_PI/180))/2;
            int y=h-FQ*sin(j*M_PI/180)/4;
            polygon.putPoints(polygon.size(),1,x,y);
        }

        // Окружность CR
        for (int j=0;j<=90;j+=5) {
            int x=CR*cos(j*M_PI/180);
            int y=h-CR*sin(j*M_PI/180);
            polygon.putPoints(polygon.size(),1,x,y);
        }

        polygon.putPoints(polygon.size(),2,
                          0,DX,
                          DX,0);

    }
    else if(type==32){
        // AX
        polygon.putPoints(polygon.size(),3,
                          w-AX,0,
                          w,AX,
                          w,h);

        // Окружность CR
        for (int j=0;j<=90;j+=5) {
            int x=CR*cos(j*M_PI/180);
            int y=h-CR*sin(j*M_PI/180);
            polygon.putPoints(polygon.size(),1,x,y);
        }

        polygon.putPoints(polygon.size(),2,
                          0,DX,
                          DX,0);
    }

    calculatePerimeter();
    calculateArea();
    calculateTransformedPolygon();
}

QPoint figure::getCenter() {
    return centerOfTheFigure;
}
void figure::setSelected(bool b) {
    isSelected=b;
}

bool figure::selected() {
    return isSelected;
}

void figure::paintFigure(QPainter& painter) {
    painter.setPen(Qt::NoPen);

    // Рисуем основную часть
    if (isSelected){
        painter.setBrush(Qt::red);
    }
    else {
        painter.setBrush(Qt::gray);
    }

    painter.drawPolygon(rotatedPolygon);
}

bool figure::containsPoint(const QPoint& point) {
    return rotatedPolygon.containsPoint(point,Qt::OddEvenFill);
}

bool isPointsInRadius(const QPoint& p1,const QPoint& p2,int radius){
    QPoint difference(p1-p2);
    return (difference.x()*difference.x()+difference.y()*difference.y())<=radius*radius;
}

void figure::calculateTransformedPolygon(){

    rotatedPolygon=polygon;
    rotatedPolygon.translate(-w/2, -h/2);

    // Поворачиваем на угол Angle и смещаем в centerOfTheFigure
    QTransform t = QTransform().rotate( Angle );
    rotatedPolygon=t.map(rotatedPolygon);
    rotatedPolygon.translate(centerOfTheFigure.x(),centerOfTheFigure.y());
}

void figure::calculatePerimeter() {
    double perim=0;
    for(int i=0;i<polygon.size()-1;i++){
        double dx=polygon[i+1].x()-polygon[i].x();
        double dy=polygon[i+1].y()-polygon[i].y();
        perim+=sqrt(dx*dx+dy*dy);
    }

    double dx=polygon[polygon.size()-1].x()-polygon[0].x();
    double dy=polygon[polygon.size()-1].y()-polygon[0].y();
    perim+=sqrt(dx*dx+dy*dy);

    // Запоминаем периметр фигуры. Cast в int сделан умышленно
    perimeter=perim;
}

void figure::calculateArea() {
    double area=w*h;
    if (type==22){
        area-=AR*AR*M_PI/4; // окружность AR
        area-=(1-M_PI/4)*BR*BR; // окружность BR
        area-=CR*CR*M_PI/4; // окружность CR
        area-=DX*DX*2; // треугольник DX
        area-=M_PI*FQ*FQ/2/2/4; // эллипс FQ
    }else if(type==32){
        area-=AX*AX*2; // треугольник AX
        area-=CR*CR*M_PI/4; // окружность CR
        area-=DX*DX*2; // треугольник DX
    }else throw;

    this->area=area;
}


bool figure::intersects(const figure& fig){
    return rotatedPolygon.intersects(fig.rotatedPolygon);
}
