#include "figure.h"
#include <time.h>
#include <stdlib.h>

figure::figure(int type):type(type),isSelected(false)
{
    // Случайно определяем параметры
    srand (time(NULL));
    AX = rand() % (h/3);
    FP = rand() % (w/4);
    DR = rand() % (h/3);

    // По умолчанию поворот против часовой стрелки
    Angle = rand() % 181-180;

    if(type==61){
        BX = rand() % (h/3);
        CX = rand() % (h/3);
        EQ = rand() % (w/4);
    }else if (type==51){
        BX=CX=EQ=0;
    }else{
        throw;
    }

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

    // Фигура 51
    if(type==51) {
        polygon.setPoints(8,
                          w-AX,0,           // 3
                          w,AX,             // 4
                          w,h,              // 5
                          w/2+FP/2,h,       // 6
                          w/2+FP/2,h-FP/2,  // 7
                          w/2-FP/2,h-FP/2,  // 8
                          w/2-FP/2,h,       // 9
                          0,h              // 10
                          );

        // Добавляем точки для окружности
        for (int j=0;j<=90;j+=5) {
            int x=DR-DR*cos(j*M_PI/180);
            int y=DR-DR*sin(j*M_PI/180);
            polygon.putPoints(polygon.size(),1,x,y);
        }
    }
    else if(type==61){
        // Начинаем с эллипса EQ
        for (int j=0;j<=180;j+=5) {
            int x=(w-EQ*cos(j*M_PI/180))/2;
            int y=EQ*sin(j*M_PI/180)/4;
            polygon.putPoints(polygon.size(),1,x,y);
        }

        polygon.putPoints(polygon.size(),
                          10,
                          w-AX,0,           // 2
                          w,AX,             // 3
                          w,h-BX,           // 4
                          w-BX,h,           // 5
                          w/2+FP/2,h,       // 6
                          w/2+FP/2,h-FP/2,  // 7
                          w/2-FP/2,h-FP/2,  // 8
                          w/2-FP/2,h,       // 9
                          CX,h,             // 10
                          0,h-CX            // 11
                          );

        // Добавляем точки для окружности
        for (int j=0;j<=90;j+=5) {
            int x=DR*sin(j*M_PI/180);
            int y=DR*cos(j*M_PI/180);
            polygon.putPoints(polygon.size(),1,x,y);
        }

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
        painter.setBrush(Qt::blue);
    }
    else {
        painter.setBrush(Qt::black);
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
    if (type==51){
        area-=(1-M_PI/4)*DR*DR; // окружность DR
    }else if(type==61){
        area-=M_PI/4*DR*DR; // вычитаем окружность DR
        area-=M_PI*EQ*EQ/2/2/4; // площадь полуэллипса
        area-=BX*BX*0.5; // BX
        area-=CX*CX*0.5; // CX
    }else throw;

        area-=FP*FP*0.5; // FP
        area-=AX*AX*0.5; // AX

    this->area=area;
}


bool figure::intersects(const figure& fig){
    return rotatedPolygon.intersects(fig.rotatedPolygon);
}
