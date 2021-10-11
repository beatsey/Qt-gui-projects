#include "graphicsWidget.h"

GraphicsWidget::GraphicsWidget(QWidget *parent) : QWidget(parent),
    leftMouseDown(false),
    selection(-1),
    menu(this),
    remove("Удалить", this),
    edit("Изменить", this)
{
    connect(&remove, SIGNAL(triggered()), this, SLOT(removeSelection()));
    connect(&edit, SIGNAL(triggered()), this, SLOT(editSelection()));
    menu.addAction(&remove);
    menu.addAction(&edit);
}

void GraphicsWidget::addFigure(int type){
    figure fig(type);
    fig.setCenter(width()/2,height()/2,width(),height());
    figures.push_back(fig);
}

void GraphicsWidget::clearFigures(){
    figures.clear();
    if (selection!=-1){
        selection=-1;
        emit updateSelection(-1);
    }

    repaint();
}

void GraphicsWidget::removeSelection(){
    if (selection!=-1){
        figures.erase(figures.begin()+selection);

        selection=-1;
        emit updateSelection(-1);

        repaint();
    }
}

void GraphicsWidget::editSelection(){
    // Открыть диалоговое окно editdialog.h для редактирования параметров selection

    EditDialog editDialog(this);
    // Передали указатель на выделенную фигуру
    editDialog.init(&figures[selection]);
    editDialog.exec();
}

void GraphicsWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.fillRect(0,0,width(),height(),Qt::white);

    for (int i=0;i<figures.size();i++) {
        figures[i].paintFigure(painter);
    }

    QWidget::paintEvent(event);
}

void GraphicsWidget::mousePressEvent(QMouseEvent * event){

  switch(event->button()) {
    case Qt::LeftButton:
      leftMouseDown=true;

      // Запомнили позицию клика
      startPoint=event->pos();

      // В любом случае сбрасываем выделение. Если кликнули на пустую область, то никто не будет выделен.
      if(selection!=-1){
          figures[selection].setSelected(false);
          selection=-1;
      }

      for (int i=figures.size()-1;i>=0;i--)
          // Если нашли пересечение, то выделяем
          if (figures[i].containsPoint(event->pos())) {
              figures[i].setSelected(true);
              selection=i;

              // Запомнили начальный offset выделенной фигуры
              startOffset=figures[i].getCenter();
          break;
        }

      emit updateSelection(selection);
      repaint();

      break;

    case Qt::RightButton:
      // Запомнили позицию клика
      startPoint=event->pos();

      // В любом случае сбрасываем выделение. Если кликнули на пустую область, то никто не будет выделен.
      if(selection!=-1){
          figures[selection].setSelected(false);
          selection=-1;
      }

      for (int i=((int)figures.size())-1;i>=0;i--){
          // Если нашли пересечение, то выделяем
          if (figures[i].containsPoint(event->pos())) {
              figures[i].setSelected(true);
              selection=i;

              emit updateSelection(selection);
              repaint();

              // Показываем меню. MapToGlobal нужен для отображения локальной системы координат в СК окна
              menu.popup(mapToGlobal(event->pos()));

              break;
          }
      }


      break;
    default:
      break;
  }
}

void GraphicsWidget::removeIntersected() {
    if(figures.empty())
        return;

    for(int i=0;i<figures.size();i++){
        figures[i].marker=false;
    }

    for(int i=0;i<figures.size()-1;i++){
        for(int j=i+1;j<figures.size();j++){
            if (figures[i].intersects(figures[j])){
                figures[i].marker=true;
                figures[j].marker=true;
            }
        }
    }

    for(int i=figures.size()-1;i>=0;i--){
        if(figures[i].marker) {
            figures.erase(figures.begin()+i);

            // Сдвигаем selection
            if(i==selection){
                selection=-1;
                emit updateSelection(-1);
            }else if(i<selection){
                selection--;
            }
        }
    }

    repaint();
}

void GraphicsWidget::updateSelectionOffset(QPoint newCenter){
    if(selection!=-1){
        figures[selection].setCenter(newCenter.x(),newCenter.y(),width(),height());
    }
}

void GraphicsWidget::mouseMoveEvent(QMouseEvent *event) {
   if(leftMouseDown) {
       updateSelectionOffset(startOffset+event->pos()-startPoint);
       update();
   }
}

void GraphicsWidget::mouseReleaseEvent(QMouseEvent* event){
    // Если разжали левую кнопку мыши
    if (event->button()==Qt::LeftButton){
        leftMouseDown=false;

        // Зафиксировали выделенную фигуру на месте
        updateSelectionOffset(startOffset+event->pos()-startPoint);
        repaint();
    }
}


// Случайное перемещение выделенной фигуры
void GraphicsWidget::relocateSelection(){
    if (selection!=-1) {
        srand (time(NULL));
        figures[selection].setCenter((rand() % (width()-figure::w))+figure::w/2,(rand() % (height()-figure::h))+figure::h/2,width(),height());
    }
    repaint();
}
