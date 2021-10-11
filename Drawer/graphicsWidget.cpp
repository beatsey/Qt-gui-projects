#include "graphicsWidget.h"

GraphicsWidget::GraphicsWidget(QWidget *parent) : QWidget(parent),
    leftMouseDown(false),
    lastPoint(-1,-1),
    mode(LINE),
    painterPenColor(Qt::black)
{
    pixmap = QPixmap(this->size());
    pixmap.fill();
}

void GraphicsWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    // Ломаная
    if(mode==LINE && !control_points.empty()) {
        painter.setBrush(Qt::black);

        for(int i=1;i<control_points.size();i++) {
            painter.setPen(control_points[i].second);
            painter.drawLine(control_points[i-1].first,control_points[i].first);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(control_points[i-1].first,4,4);
        }

        // Отрисовка последней пунктирной линии
        painter.setPen(QPen(painterPenColor,1,Qt::DotLine,Qt::RoundCap));
        painter.drawLine(control_points.back().first, lastPoint);
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(control_points.back().first,4,4);

    } else if(mode==DRAW) {
        painter.drawPixmap(0,0,pixmap);
    }

    QWidget::paintEvent(event);
}


void GraphicsWidget::mousePressEvent(QMouseEvent * event){
    lastPoint = event->pos();

  switch(event->button()) {
    case Qt::LeftButton:
      leftMouseDown=true;

      if(mode==LINE) {
        // добавляем новую точку
        control_points.push_back(std::make_pair(event->pos(),
                  QPen(painterPenColor,2)));

      }else if(mode==DRAW) {

          QPainter painter(&pixmap);
          painter.setBrush(painterPenColor);
          painter.setPen(Qt::NoPen);
          painter.drawEllipse(event->pos(),4,4);
      }

      repaint();

      break;

    case Qt::RightButton:

      if(mode==LINE && !control_points.empty()){
        // Убираем последний отрезочек ломанной
        control_points.pop_back();
        repaint();
      }

      break;
    default:
      break;
  }
}


void GraphicsWidget::mouseReleaseEvent(QMouseEvent* event){
    // Если разжали левую кнопку мыши
    if (event->button()==Qt::LeftButton){
        leftMouseDown=false;
    }
}

void GraphicsWidget::mouseMoveEvent(QMouseEvent *event) {
   if(leftMouseDown && mode==DRAW) {
       QPainter painter(&pixmap);
       painter.setPen(QPen(painterPenColor,8,Qt::SolidLine,Qt::RoundCap));
       painter.drawLine(event->pos(),lastPoint);
   }
   lastPoint = event->pos();
   repaint();
}
