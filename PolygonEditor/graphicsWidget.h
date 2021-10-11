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
#include <QMenu>
#include "figure.h"
#include "editdialog.h"

class GraphicsWidget : public QWidget
{
    Q_OBJECT
    bool leftMouseDown;
    int selection;
    QPoint startPoint;
    QPoint startOffset;

    std::vector<figure> figures;

    QMenu menu;
    QAction remove, edit;

    void updateSelectionOffset(QPoint newOffset);

signals:
    void updateSelection(int); // Сигнал обновления индекса выделенной фигуры
public:

    void addFigure(int type); // 0 - первая, 1 - вторая
    void clearFigures();

    explicit GraphicsWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;

public slots:
    void removeSelection();   // Удаление выделенной фигуры
    void editSelection();     // Диалоговое окно для изменения выделенной фигуры
    void removeIntersected(); // Удаление пересекающихся фигур
    void relocateSelection(); // Случайное перемещение выделенной фигуры

};

#endif // GRAPHICSWIDGET_H
