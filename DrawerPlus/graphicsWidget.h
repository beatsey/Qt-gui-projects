#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <vector>
#include <QPoint>
#include <QPen>
#include <QPainter>
#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QPainterPath>


class GraphicsWidget : public QWidget
{
    Q_OBJECT
    QPoint lastPoint;

public:
    std :: vector<QPoint> control_points;

    explicit GraphicsWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;
};

#endif // GRAPHICSWIDGET_H
