#include "qpointtablewidget.h"

void QPointTableWidget::clearTable(){
    setRowCount(0);
}

void QPointTableWidget::updateTable(size_t pts){
  if(editMode == SetupNewControlLine){
      int size = static_cast<int>(control_points.size());
      setRowCount(size);

      for(int q=0; q<size; ++q){
        const Vector2& pt(control_points[static_cast<size_t>(q)]);
        setItem(q, 0,  new QTableWidgetItem(QString::number(pt.x)));
        setItem(q, 1,  new QTableWidgetItem(QString::number(pt.y)));
      }
  }else{
    const Vector2& pt(control_points[static_cast<size_t>(pts)]);
    setItem(static_cast<int>(pts), 0,  new QTableWidgetItem(QString::number(pt.x)));
    setItem(static_cast<int>(pts), 1,  new QTableWidgetItem(QString::number(pt.y)));
  }
}
