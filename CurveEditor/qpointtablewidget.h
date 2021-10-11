#ifndef QPOINTTABLEWIDGET_H
#define QPOINTTABLEWIDGET_H

#include <QTableWidget>
#include "vec.h"
#include "variables.h"

class QPointTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    explicit QPointTableWidget(QWidget *parent = nullptr) : QTableWidget (parent){}

signals:

public slots:
    void clearTable();
    void updateTable(size_t pts);

};

#endif // QPOINTTABLEWIDGET_H
