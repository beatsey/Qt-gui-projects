#ifndef FIGURE_H
#define FIGURE_H

#include <QPoint>
#include <QPolygon>
#include <QPainter>
#include <QTransform>
#include "editdialog.h"

class figure
{
    // Константы высоты и ширины фигур

    int AX, AR, BX, BR, CX, CR, DX, DR, EP, EQ, FP, FQ, Angle, type;
    QPoint centerOfTheFigure;
    QPolygon polygon;
    QPolygon rotatedPolygon;

    bool isSelected;

    // Периметр и площадь фигуры
    int perimeter;
    int area;

    bool isPointsInRadius(const QPoint& p1,const QPoint& p2,int radius);

    void calculateTransformedPolygon();

    void calculatePerimeter();

    void calculateArea();

public:
    bool marker;
    static constexpr int h=100, w=200;

    figure(int type);

    // Расчёт полигона в случае изменения параметров
    void calculatePolygon();

    void setCenter(int x, int y, int width, int height);

    QPoint getCenter();

    void setSelected(bool b);
    bool selected();

    void paintFigure(QPainter& painter);

    bool intersects(const figure& fig);

    bool containsPoint(const QPoint& point);

    friend class EditDialog;
};

#endif // FIGURE_H
