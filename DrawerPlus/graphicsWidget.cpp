#include "graphicsWidget.h"

GraphicsWidget::GraphicsWidget(QWidget *parent) : QWidget(parent),
    lastPoint(-1,-1)
{}

void GraphicsWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    // Ломаная
    if(!control_points.empty()) {
        painter.setBrush(Qt::black);

        for(size_t i=1;i<control_points.size();i++) {
            painter.setPen(Qt::black);
            painter.drawLine(control_points[i-1],control_points[i]);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(control_points[i-1],4,4);
        }

        // Отрисовка последней пунктирной линии
        painter.setPen(QPen(Qt::black,1,Qt::DotLine,Qt::RoundCap));
        painter.drawLine(control_points.back(), lastPoint);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(control_points.back(),4,4);
    }

    QWidget::paintEvent(event);
}

void GraphicsWidget::mousePressEvent(QMouseEvent * event) {
    lastPoint = event->pos();

  switch(event->button()) {
    case Qt::LeftButton:
        // добавляем новую точку
        control_points.push_back(event->pos());

      repaint();

      break;

    case Qt::RightButton:

      if(!control_points.empty()) {
        // Убираем последний отрезочек ломанной
        control_points.pop_back();
        repaint();
      }

      break;
    default:
      break;
  }
}

void GraphicsWidget::mouseMoveEvent(QMouseEvent *event) {
   lastPoint = event->pos();
   repaint();
}
