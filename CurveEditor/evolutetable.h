#ifndef EVOLUTETABLE_H
#define EVOLUTETABLE_H

#include <QTableWidget>
#include "vec.h"
#include "variables.h"

class EvoluteTable : public QTableWidget
{
    Q_OBJECT

public:
    explicit EvoluteTable(QWidget *parent = nullptr) : QTableWidget (parent){}

signals:
public slots:
};

#endif // EVOLUTETABLE_H
