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

enum MODE {
    DRAW,
    LINE
};

class GraphicsWidget : public QWidget
{
    Q_OBJECT
    bool leftMouseDown;
    QPoint lastPoint;

public:
    MODE mode;
    QColor painterPenColor;
    QPixmap pixmap;
    std :: vector<std::pair<QPoint, QPen>> control_points;

    explicit GraphicsWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;
};

#endif // GRAPHICSWIDGET_H
