#ifndef SGRAPH2DWIDGET_H
#define SGRAPH2DWIDGET_H

#include <QWidget>
#include "vec.h"
#include "variables.h"

class SGraph2dWidget : public QWidget
{
    Q_OBJECT

    std::vector<QPoint> qpoints;

    size_t changing_point_num;

    QPoint current_pointer;

    QCursor cursor_target;
    QCursor cursor_green;

    // Преобразовать Vector2 в qpoints
    void convert(std::vector<Vector2> list){
        size_t n=list.size();
        qpoints.resize(n);
        for(size_t q=0; q < n; ++q)qpoints[q]=list[q];
    }

public:
    explicit SGraph2dWidget(QWidget *parent = nullptr);

    void BeginCurve();
    void EndCurve();

    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *) Q_DECL_OVERRIDE;

signals:
    void updatePoint(size_t);
    void updateDerivEnd(size_t);
    void ChangedPoints(int);

public slots:
};

#endif // SGRAPH2DWIDGET_H
