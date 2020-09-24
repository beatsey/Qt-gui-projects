#include "sgraph2dwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

const int vertex_radius = 5; // Радиус окружности вокруг точки

SGraph2dWidget::SGraph2dWidget(QWidget *parent) : QWidget(parent)
{
  editMode = Still;
  changing_point_num = 0;

  cursor_green = QCursor(QPixmap(":/cursor/cursorarrovgreen.png"));
  cursor_target = QCursor(QPixmap(":/cursor/cursortarget.png"));
  setMouseTracking(true);
}

void SGraph2dWidget::BeginCurve(){
  editMode = SetupNewControlLine;
  setCursor(cursor_target);
  repaint();
}

void SGraph2dWidget::EndCurve(){
  editMode = Still;
  setCursor(Qt::ArrowCursor);
  repaint();
}

void drawText(QPainter&painter){
    QPen Pens[2]={QPen(Qt::red),QPen(Qt::blue)};

    if(curve_type==Rotation){
        char const * str[5]={" Право"," Лево"," Низ"," Верх"," Коллин"};

        bool flag1=classification[0];
        bool flag2=classification[1];

        if(flag1) painter.drawText(30, 30, QString("Классификация Верх/Низ"));
        else painter.drawText(30, 30, QString("Классификация Справа/Слева"));

        for(size_t q=2,n=control_points.size(); q < n; ++q){
            QString text = QString::number(q+1);
            painter.setPen(Pens[classification[q]&1]);
            if(classification[q]>=2)
                text += str[4]; // Коллинеарны
            else
                text += str[((flag1<<1)|flag2)^classification[q]];

            // Надписи
            painter.drawText(static_cast<int>(control_points[q].x) + vertex_radius*2,
                             static_cast<int>(control_points[q].y) + vertex_radius*2,text);
        }
    }else if(curve_type==insideTriangle){
        char const * str[2]={" Out"," In"};

        for(size_t q=3,n=control_points.size(); q < n; ++q){
            QString text = QString::number(q+1);
            painter.setPen(Pens[classification[q]]);

                text += str[classification[q]];

            // Надписи
            painter.drawText(static_cast<int>(control_points[q].x) + vertex_radius*2,
                             static_cast<int>(control_points[q].y) + vertex_radius*2,text);
        }
    }else if(curve_type==insidePolygon){
        char const * str[2]={" Out"," In"};

        for(size_t q=static_cast<size_t>(vertices),n=control_points.size(); q < n; ++q){
            QString text = QString::number(q+1);
            painter.setPen(Pens[classification[q]]);

                text += str[classification[q]];

            // Надписи
            painter.drawText(static_cast<int>(control_points[q].x) + vertex_radius*2,
                             static_cast<int>(control_points[q].y) + vertex_radius*2,text);
        }
    }
}

void SGraph2dWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen old = painter.pen();

    size_t n=control_points.size();

    // Окружности вокруг точек
    for(size_t q=0; q < n; ++q){
        int x = static_cast<int>(control_points[q].x);
        int y = static_cast<int>(control_points[q].y);

        painter.drawEllipse(
          QRect(x - vertex_radius,y - vertex_radius,vertex_radius*2,vertex_radius*2));
    }


    // Предикат поворота
    if(curve_type==Rotation){
        // Первые две
        for(size_t q=0; q < 2; ++q){
            int x = static_cast<int>(control_points[q].x);
            int y = static_cast<int>(control_points[q].y);

            painter.drawText(x + vertex_radius*2,y + vertex_radius*2,QString::number(q+1));
        }

        // Подписи всех остальных точек
        drawText(painter);

    }else if(curve_type==insideTriangle){
        // Первые три
        for(size_t q=0; q < 3; ++q){
            int x = static_cast<int>(control_points[q].x);
            int y = static_cast<int>(control_points[q].y);

            painter.drawText(x + vertex_radius*2,y + vertex_radius*2,QString::number(q+1));
        }
        drawText(painter);

    }else if(curve_type==insidePolygon){
        // Первые три
        for(size_t q=0; q < static_cast<size_t>(vertices); ++q){
            int x = static_cast<int>(control_points[q].x);
            int y = static_cast<int>(control_points[q].y);

            painter.drawText(x + vertex_radius*2,y + vertex_radius*2,QString::number(q+1));
        }
        drawText(painter);

    }else
        // Просто нумерация
        for(size_t q=0; q < n; ++q){
            int x = static_cast<int>(control_points[q].x);
            int y = static_cast<int>(control_points[q].y);

            painter.drawText(x + vertex_radius*2,y + vertex_radius*2,QString::number(q+1));
        }

    // Сохранили кисть
    painter.setPen(QPen(Qt::DashLine));

    // Ломаная
    if(showBrokenLine && curve_type!=DelaunayTriangulation){
        convert(control_points);
        painter.drawPolyline(&(qpoints[0]), static_cast<int>(n));
    }

    // Редактирование
    if(editMode == SetupNewControlLine){
      painter.drawText(30, 30, QString("Добавить точку левой кнопкой мыши. Выход из режима - правая кнопка мыши."));
      if(showBrokenLine&&n) painter.drawLine(control_points.back(), current_pointer);
    }

    painter.setPen(QPen(Qt::red));

    if(curve_type==DelaunayTriangulation){

        const std::vector<Triangle> &triangles = triangulation.getTriangles();
        for(auto &tri : triangles){
            painter.drawLine(tri.p1, tri.p2);
            painter.drawLine(tri.p2, tri.p3);
            painter.drawLine(tri.p3, tri.p1);
        }

        // Красим треугольники

        int color=0;
        const int delta=30;

        for(auto &tri : triangles){
            if(tri.colored==false)continue;
            // Красим треугольник

            QPainterPath polygonPath;

            polygonPath.moveTo(tri.p1.x,tri.p1.y);
            polygonPath.lineTo(tri.p2.x,tri.p2.y);
            polygonPath.lineTo(tri.p3.x,tri.p3.y);
            polygonPath.closeSubpath();

            painter.fillPath(polygonPath, QColor(color,color,color));

            color+=delta;
            if(color>255-delta)color=0;
        }

    }else if(curve_points.size()){ // Кривая
      convert(curve_points);
      painter.drawPolyline(&(qpoints[0]), static_cast<int>(curve_points.size()));

      if(editDerivatives){
          // Касательные векторы
          painter.setPen(QPen(Qt::blue));
          if(curve_type==HermitCurve){
              for(size_t q=0;q<n;++q){
                 QPoint start(control_points[q]);
                 QPoint end = tangent_ends[q];

                 painter.drawLine(start,end);
                 painter.drawEllipse(
                   QRect(end.x() - vertex_radius,end.y() - vertex_radius,vertex_radius*2,vertex_radius*2));

              }
          }else if(curve_type==CubicCurve){
              // Рисуем только для двух точек

              QPoint start(control_points[0]);
              QPoint end = tangent_ends[0];
              painter.drawLine(start,end);
              painter.drawEllipse(
                QRect(end.x() - vertex_radius,end.y() - vertex_radius,vertex_radius*2,vertex_radius*2));

              start=control_points[control_points.size()-1];
              end = tangent_ends[1];
              painter.drawLine(start,end);
              painter.drawEllipse(
                QRect(end.x() - vertex_radius,end.y() - vertex_radius,vertex_radius*2,vertex_radius*2));
          }else if(curve_type==RationalBezierCurve){
              for(size_t q=0;q<n;++q){
                 QPoint start(control_points[q]);
                 QPoint end = tangent_ends[q];

                 painter.drawLine(start,end);
                 painter.drawEllipse(
                   QRect(end.x() - vertex_radius,end.y() - vertex_radius,vertex_radius*2,vertex_radius*2));
                 painter.drawText(end.x() + vertex_radius*2,end.y() + vertex_radius*2,QString::number(bezierWeights[q]));

                 int size = static_cast<int>(sqrt(control_points[q].squareDist(tangent_ends[q])));
                 painter.drawEllipse(
                   QRect(start.x()-size,start.y()-size,size*2,size*2));
              }
          }
      }
    }

    // Вернули прежнюю кисть
    painter.setPen(old);
    QWidget::paintEvent(event);
}

inline bool checkPtInRadius(const Vector2& a,const Vector2& b){
    return a.squareDist(b) < vertex_radius * vertex_radius * 4;
}

void SGraph2dWidget::mousePressEvent(QMouseEvent * event){
  switch(event->button()){
    case Qt::LeftButton:
      if(editMode == SetupNewControlLine){
        if(control_points.size()>INT_MAX){
          // Максимумальное кол-во точек. Выходим из режима.
            EndCurve();
            break;
        }

        // добавляем новую точку
        control_points.push_back(event->pos());

        emit updatePoint(changing_point_num);
        repaint();
      }else{
        Vector2 clicked(event->pos());

        bool flag=true;

        // Захват концов касательных векторов
        if(editDerivatives&&(curve_type==HermitCurve||curve_type==CubicCurve||curve_type==RationalBezierCurve)){
            size_t n;
            if(curve_type==CubicCurve) n=2;
            else n=tangent_ends.size();

            for(size_t q=0; q < n; ++q)
                if(checkPtInRadius(tangent_ends[q],clicked)){
                    // Захват точки в радиусе клика
                    changing_point_num = q;
                    editMode = EditDerrivative;
                    setCursor(cursor_target);
                    flag=false;
                    break;
            }
        }

        if(flag)
        // Захват опорных точек
        for(size_t q=0,n=control_points.size(); q < n; ++q)
            if(checkPtInRadius(control_points[q],clicked)){
                // Захват точки в радиусе клика
                changing_point_num = q;
                editMode = Edit;
                setCursor(cursor_target);
                break;
            }
      }
      break;

    case Qt::RightButton:
      if(editMode == SetupNewControlLine)
        EndCurve();
      else if(curve_type==DelaunayTriangulation){
          Vector2 clicked(event->pos());
          // В какой треугольник попали?

          if( clicked.x>triangulation.minX&&
              clicked.x<triangulation.maxX&&
              clicked.y>triangulation.minY&&
              clicked.y<triangulation.maxY){

              std::vector<Triangle> &triangles = triangulation.getTriangles();
              for(auto &triangle : triangles){

                  // Классификация точки относительно треугольника ABC
                  const Vector2 &A = triangle.p1;
                  const Vector2 &B = triangle.p2;
                  const Vector2 &C = triangle.p3;

                  double det = (B - A).cross(clicked - A);
                  double det1 = (C - B).cross(clicked - B);

                  bool flag = det*det1>0;
                  if(flag){
                      double det2 = (A - C).cross(clicked - C);
                      if(flag && det2*det>0){
                          // Точка внутри. Меняем значение треугольника
                          triangle.colored^=true;
                          repaint();
                        break;
                      }
                  }
                  // Точка снаружи
              }
          }
      }
      break;
    default:;
  }
}

void SGraph2dWidget::mouseReleaseEvent(QMouseEvent*){
  if(editMode == Edit || editMode == EditDerrivative){
    editMode = Still;
    setCursor(Qt::ArrowCursor);
    emit ChangedPoints(-2);
  }
}

void SGraph2dWidget::mouseMoveEvent(QMouseEvent *event){
 current_pointer = event->pos();
 switch(editMode){
   case Edit:
     control_points[changing_point_num] = current_pointer;

     // Тащим концы касательных векторов за основной точкой
     if(curve_type == RationalBezierCurve){
         tangent_ends[changing_point_num]=tangent_vectors[changing_point_num];
         tangent_ends[changing_point_num]+=current_pointer;

     }else if(curve_type == HermitCurve){
         tangent_ends[changing_point_num]=tangent_vectors[changing_point_num]*0.4;
         tangent_ends[changing_point_num]+=current_pointer;

     }else if(curve_type == CubicCurve){
         if(changing_point_num==control_points.size()-1)
             tangent_ends[1]=current_pointer+tangent_vectors[changing_point_num]*0.4;

         else if(changing_point_num==0)
             tangent_ends[0]=current_pointer+tangent_vectors[0]*0.4;
     }

     emit updatePoint(changing_point_num);
     repaint();
     break;

   case EditDerrivative:

     if(curve_type == RationalBezierCurve){
         QPoint delta = event->pos()-control_points[changing_point_num];
         int squarelen = delta.x()*delta.x()+delta.y()*delta.y();

         // Ограничение на радиус окружности весов в рациональной кривой Безье

         if(squarelen>=radiusBezierMAX*radiusBezierMAX){
             delta*=radiusBezierMAX/sqrt(squarelen);
             tangent_ends[changing_point_num]=control_points[changing_point_num];
             tangent_ends[changing_point_num]+=delta;
         }else if(squarelen<=radiusBezierMIN*radiusBezierMIN){
             delta*=radiusBezierMIN/sqrt(squarelen);
             tangent_ends[changing_point_num]=control_points[changing_point_num];
             tangent_ends[changing_point_num]+=delta;
         }else{
             tangent_ends[changing_point_num] = current_pointer;
         }


     }else{
        tangent_ends[changing_point_num] = current_pointer;
     }

     emit updateDerivEnd(changing_point_num);
     repaint();
     break;
   case SetupNewControlLine:
     repaint();
     break;
   default:;
 }
}

void SGraph2dWidget::leaveEvent( QEvent * event ){
  if(editMode == Edit || editMode == EditDerrivative){
    editMode = Still;
    setCursor(Qt::ArrowCursor);
  }
  QWidget::leaveEvent(event);
}
